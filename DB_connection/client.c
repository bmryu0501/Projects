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

#define NAME_SIZE MSG_SIZE
#define MSG_SIZE 100

// AWS IP
char IP[MSG_SIZE];
char PORT[10];

//송신용 , 수신용 쓰레드
//왜 2개? 다른 사람이 보낸 채팅 메시지를 보기 위해서!
pthread_t send_t;
pthread_t get_t;
//종료 조건
int exitFlag;

//소켓
int sock;

// 채팅창에 보여질 이름과 메시지
char name[NAME_SIZE] = "[DEFAULT]";
char msg[MSG_SIZE];
// 커멘드 아규먼트 필요로 함: 사용할 닉네임
void connectEffect(){
	int i=0;
	while(i<50){
		usleep(20*1000);
		printf(".");
		i++;
	}
	printf("\n");
}

void *receiveMsg()
{
	char buf[NAME_SIZE + MSG_SIZE];
	while (!exitFlag)
	{
		memset(buf, 0, MSG_SIZE);
		int len = read(sock, buf, 100-1);
		//서버가 종료되었어?
		if(!strcmp(buf,"Q")){
			printf("INFO :: Server Disconnected\n");
			kill(0, SIGINT);
			exitFlag = 1;
			break;
		}
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


void *shall()
{
	char buf[MSG_SIZE]="connect";
	int conn=0;
	struct sockaddr_in addr={0};
	
	while(1){
		memset(buf,0,sizeof(buf));
		usleep(100*1000);
		printf(">>");
		scanf("%s",buf);
		if(!strcmp(buf,"Q")){
		   	write(sock,buf,strlen(buf));
			break;
		}

		if(!strcmp(buf,"connect")){ //connect
			if(conn){
			   	printf("already connected!\n");
				continue;
			}
			scanf("%s",buf);
			strcpy(IP,buf);
			scanf("%s",buf);
			strcpy(PORT,buf);
			printf("Connecting to IP:%s PORT:%s\n",IP,PORT);
			connectEffect();
			
			addr.sin_family=AF_INET;
			addr.sin_addr.s_addr=inet_addr(IP);
			addr.sin_port=htons(atoi(PORT));
			
			if(connect(sock,(struct sockaddr *)&addr,sizeof(addr))==-1){
				printf("connect error\n");
				break;
			}
			printf("Connected Successfully!\n");	
			conn=1;
			pthread_create(&get_t,NULL,receiveMsg,NULL);
		}else if(!strcmp(buf,"save")){ //save
			if(!conn){
				printf("connect to server first!\n");
				continue;	
			}
			char msg[100];
			scanf("%s",buf);
			sprintf(msg,"%s %s","save",buf);
			printf("%s\n",msg);
			write(sock,msg,strlen(msg));
		}else if(!strcmp(buf,"read")){ //read
			if(!conn){
				printf("connect to server first!\n");
				continue;	
			}
			char msg[100];
			scanf("%s",buf);
			sprintf(msg,"%s %s","read",buf);
			write(sock,msg,strlen(msg));
		}else if(!strcmp(buf,"close")){ //close
			if(!conn){
				printf("connect to server first!\n");
				continue;	
			}
			write(sock,buf,strlen(buf));
		}
	}
}

//똑같다.
void interrupt(int arg)
{
	printf("\nYou typped Ctrl + C\n");
	printf("Bye\n");

	//쓰레드 2개 종료 -> 진행중이던걸 끔
	pthread_cancel(send_t);
	pthread_cancel(get_t);

	//쓰레드 2개 정리 -> 끝날때까지 기다렸다가 정리
	pthread_join(send_t, 0);
	pthread_join(get_t, 0);

	//소켓 종료
	close(sock);
	exit(1);
}

int main(int argc, char *argv[])
{
	signal(SIGINT,interrupt);
	sock=socket(PF_INET, SOCK_STREAM,0);
	if(sock==-1){
		printf("sock create error\n");
		exit(1);
	}
	pthread_create(&send_t,NULL,shall,NULL);

	pthread_join(send_t,NULL);
	pthread_join(get_t,NULL);

		
	
	// close sock
	close(sock);
	return 0;
}

