#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printf("Usage: shell [pid]\n");
		return 0;
	}

	char command[100];
	char pid[10];
	strcpy(pid, argv[1]);

	int op;
	do{
		printf("person >> ");
		scanf("%d", &op);

		if(op == 1) {
			strcpy(command, "kill -USR1 ");
			strcat(command, pid);
			system(command);
			//printf("%s\n", command);
		} else if (op == 2) {
			strcpy(command, "kill -USR2 ");
			strcat(command, pid);
			system(command);
			//printf("%s\n", command);
		} else if (op == 3) {
			strcpy(command, "kill -TERM ");
			strcat(command, pid);
			system(command);
			//printf("%s\n", command);
		}
		else {
			printf("Put number between 1 and 3\n");
		}
	} while(op != 3);

	return 0;
}
