#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int flag = 1;

void sig1() {
	printf("[SIGUSR1]\n");
}

void sig2() {
	system("clear");
	setbuf(stdout, NULL);
	printf("CLEAR!\n");
}

void sigterm() {
	flag = 0;
}

int main() {
	signal(SIGUSR1, sig1);
	signal(SIGUSR2, sig2);
	signal(SIGTERM, sigterm);
	
	char c = 'A';
	int dir = -1;

	while(flag) {
		printf("%c\n", c);
		if(c == 'Z' || c == 'A') dir *= -1;
		c += dir;
		usleep(500*1000);
	}
	printf("BYE\n");

	return 0;
}
