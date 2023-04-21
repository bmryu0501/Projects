#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

struct Node{
	int age;
	char name[100];
}user;

int main() {
	int fd = open("/dev/nobrand", O_RDWR);
	if (fd < 0) {
		printf("ERROR, no device\n");
		exit(1);
	}

	//read
	/*
	char buff[100];
	read(fd, buff, 100);
	printf("%s\n", buff);
	*/

	//write
	/*
	char buff[100] = "hello";
	write(fd, buff, 100);
	*/
	
	printf("Welcome to SSAFY!\n");

	printf("What's your name? : ");
	scanf("%s", user.name);
	printf("how old are u? : ");
	scanf("%d", &user.age);

	printf("SSAFY studying ...\n");
	ioctl(fd, _IO(0, 3), 0);
	printf("SSAFY graduate ...\n");
	ioctl(fd, _IO(0, 4), &user);

	printf("%s (%d)\n", user.name, user.age);
	printf("Bye!\n");

	close(fd);
	return 0;
}
