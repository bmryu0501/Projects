#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int coin = 0;
pthread_t queue[100];
int head = 0;
int tail = 0;
int del = -1;
int PRINT = 0;

void* miner() {
	while(1) {
		coin += 1;
		usleep(1000 * 1000);
		if(PRINT) printf("coin: %d\n", coin);
	}
}

void printMiners(){
	for(int i = head;i!=tail;i = (i+1)%100) {
		printf("[%d] 0x%02X\n", i, queue[i]);
	}
	printf("Total: %d\n", ((tail+100)-head)%100);
	printf("coins: %d\n", coin);
}

void addMiner() {
	pthread_create(&queue[tail], NULL, miner, NULL);
	tail = (tail+1)%100;
}

void delMiner() {
	pthread_cancel(queue[head]);
	head = (head+1)%100;
}

int main() {
	char buf[100];

	addMiner();

	while(1) {
		printf("TShell > ");
		scanf("%s", buf);
		if(strcmp(buf, "show") == 0) {
			printMiners();
		} else if (strcmp(buf, "add") == 0) {
			addMiner();
		} else if (strcmp(buf, "del") == 0) {
			if(head == tail) {
				printf("No miners!\n");
				continue;
			}
			delMiner();
		} else if (strcmp(buf, "toggle") == 0) {
			PRINT = PRINT ^ 1;
		} else if (strcmp(buf, "exit") == 0) {
			break;
		}
	}

	return 0;
}
