#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define NAME_SIZE 20
#define MSG_SIZE 100

const char *IP = "127.0.0.1";
const char *PORT = "12345";

pthread_t send_tid;
pthread_t receive_tid;
int exitFlag;
int sock;

char name[NAME_SIZE] = "[DEFAULT]";
char msg[MSG_SIZE];

void *sendMsg()
{
	char buf[NAME_SIZE + MSG_SIZE];

	while (!exitFlag)
	{
		memset(buf, 0, NAME_SIZE + MSG_SIZE);
		fgets(msg, MSG_SIZE, stdin);
		if (!strcmp(msg, "exit\n"))
		{
			exitFlag = 1;
			write(sock, msg, strlen(msg));
			break;
		}
		if (exitFlag)
			break;
		sprintf(buf, "%s %s", name, msg);
		write(sock, buf, strlen(buf));
	}
}

void *receiveMsg()
{
	char buf[NAME_SIZE + MSG_SIZE];
	while (!exitFlag)
	{
		memset(buf, 0, MSG_SIZE);
		int len = read(sock, buf, NAME_SIZE + MSG_SIZE - 1);
		if (len == 0)
		{
			printf("INFO :: Server Disconnected\n");
			kill(0, SIGINT);
			exitFlag = 1;
			break;
		}
		printf("%s\n", buf);
	}
}

void interrupt(int arg)
{
	printf("\nYou typped Ctrl + C\n");
	printf("Bye\n");

	pthread_cancel(send_tid);
	pthread_cancel(receive_tid);
	pthread_join(send_tid, 0);
	pthread_join(receive_tid, 0);

	close(sock);
	exit(1);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, interrupt);

	if (argc != 2)
	{
		printf("Usage : %s <name>\n", argv[0]);
		exit(1);
	}

	sprintf(name, "[%s]", argv[1]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = htons(atoi(PORT));

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		printf("ERROR :: 2_Connect Error\n");
		exit(1);
	}

	pthread_create(&send_tid, NULL, sendMsg, NULL);
	pthread_create(&receive_tid, NULL, receiveMsg, NULL);

	pthread_join(send_tid, 0);
	pthread_join(receive_tid, 0);

	close(sock);
	return 0;
}
