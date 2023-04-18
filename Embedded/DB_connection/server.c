#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

//접속한 클라이언트 수
#define MAX_CLIENT_CNT 500

char PORT[5] = "0000";
int server_sock;

//창구 직원 500명

int client_sock;
struct sockaddr_in client_addr;

//서버 종료 -> 창구 직원 500명 퇴근 -> 창구 직원 1명 1명당 쓰레드
void interrupt(int arg)
{
	printf("\nYou typed Ctrl + C\n");
	printf("Bye\n");

	close(client_sock);
	close(server_sock);

	exit(1);
}

void removeEnterChar(char *buf)
{
	int len = strlen(buf);
	for (int i = len - 1; i >= 0; i--)
	{
		if (buf[i] == '\n') {
			buf[i] = '\0';
			break;
		}
	}
}

void toUpperCase(char *buf) {
	int len = strlen(buf);
	for(int i = 0; i < len; i++)
		if(buf[i] >= 'a' && buf[i] <= 'z') buf[i] += 'A' - 'a';
}

void write_file(const char* key, const char* value) {
	FILE* fp = fopen("data", "r+");

	char line[100];
	char cur_key[20];
	char cur_value[20];
	int key_found = 0;

	while(fgets(line, 100, fp) != NULL) {
		sscanf(line, "%s %s", cur_key, cur_value);
		if(strcmp(cur_key, key) == 0) {
			fseek(fp, -strlen(line), SEEK_CUR);
			fprintf(fp, "%s %s\n", key, value);
			key_found = 1;
			break;
		}
	}

	if(!key_found) {
		fprintf(fp, "%s %s\n", key, value);
	}

	fclose(fp);
}

int read_file(const char *key, char *value) {
	FILE *fp;
	char line[100];
	char cur_key[20];
	char cur_value[20];

	fp = fopen("data", "r");
	if(fp == NULL) {
		printf("Open failed\n");
		return 0;
	}

	while(fgets(line, 100, fp) != NULL) {
		sscanf(line, "%s %s", cur_key, cur_value);
		printf("%s %s\n", cur_key, cur_value);
		if(strcmp(cur_key, key) == 0) {
			printf("Found %s", line);
			strcpy(value, cur_value);
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);

	return 0;
}

void client_handler()
{
	char name[100];
	// inet_ntoa 는,빅 엔디안  long int ip 를 문자열로 바꿈
	printf("INFO :: Connect new Client (%s)\n", inet_ntoa(client_addr.sin_addr));

	// wait & write
	char buf[100];
	while (1)	{

		//초기화
		memset(buf, 0, 100);

		//메시지 읽어
		int len = read(client_sock, buf, 99);

		//종료 옵션 (Disconnected)
		if (len == 0){
			printf("INFO :: Disconnect with client.. BYE\n");
			break;
		}

		//종료 옵션 (Input q or Q)
		if (strcmp("Q", buf) == 0 || strcmp("q", buf) == 0) {
			printf("INFO :: Client want close.. BYE\n");
			break;
		}

		// remove '\n'
		removeEnterChar(buf);
		toUpperCase(buf);

		// Classify operation
		char op[20], key[20], value[20];
		memset(op, 0, sizeof(op));
		memset(key, 0, sizeof(key));
		memset(value, 0, sizeof(value));
		sscanf(buf, "%s %19[^:]:%19s", op, key, value);
		printf("Recieved: %s %s:%s\n", op, key, value);

		if (!strcmp(op, "SAVE")) {
			write_file(key, value);
		} else if (!strcmp(op, "READ")) {
			if(!read_file(key, value)) {
				strcpy(buf, "NOT FOUND");
				write(client_sock, buf, strlen(buf));
			} else {
				write(client_sock, value, strlen(value));
			}
		} else if (!strcmp(op, "CLOSE")) {
			printf("INFO :: Client want to close...\n");
			break;
		} else {
			strcpy(buf, "ERROR :: Invalid operation!");
			write(client_sock, buf, strlen(buf));
		}

		// send new message
		usleep(10 * 1000);
		strcpy(buf, "DONE!");
		write(client_sock, buf, strlen(buf));

	}
	//[exit] or [ctrl + C] 로 클라이언트 소켓이 종료되면, 서버 내 클라이언트 소켓을 종료시킨다.
	close(client_sock);
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Usage: server <PORT>\n");
		exit(1);
	}

	strcpy(PORT, argv[1]);
	printf("PORT %s opened\n", PORT);

	// Ctrl + C 누를 경우 안전종료
	signal(SIGINT, interrupt);

	// socket create
	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (server_sock == -1)
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

	// option setting
	// 종료 시 3분 정도 동일한 포트 배정 불가 에러 해결
	int optval = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

	// 주소 설정
	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(PORT));

	// bind
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		printf("ERROR :: 2_bind Error\n");
		exit(1);
	}

	// listen
	if (listen(server_sock, 5) == -1)
	{
		printf("ERROR :: 3_listen Error");
		exit(1);
	}

	socklen_t client_addr_len = sizeof(struct sockaddr_in);

	// pthread argument bug fix
	printf("Wait for next client...\n");

	// Main Loop
	while (1)
	{
		// 새로운 클라이언트를 위해 초기화 똑같다.
		memset(&client_addr, 0, sizeof(struct sockaddr_in));

		// accpet
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_sock == -1)
		{
			printf("ERROR :: 4_accept Error\n");
			break;
		}

		client_handler();
	}
	// server socket close
	close(server_sock);
	return 0;
}
