#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SSDINFO_H
#define SSDINFO_H
#include "ssdinfo.h"
#endif


int main() {
    char buf[100];
    char *cmd, *arg1, *arg2;

    /* Commands
    write
    read
    exit
    help
    fullwrite
    fullread
    */

    while(1) {
        printf("ssd>> ");
        fgets(buf, 100, stdin);
        buf[strlen(buf)-1] = '\0';

        cmd = strtok(buf, " ");
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        char execute[100] = "ssd ";
        
        if (strcmp(cmd, "write") == 0) {
            strcat(execute, "W ");
            strcat(execute, arg1);
            strcat(execute, " ");
            strcat(execute, arg2);
            system(execute);
        } else if (strcmp(cmd, "read") == 0) {
            strcat(execute, "R ");
            strcat(execute, arg1);
            system(execute);
            FILE *fp = fopen("result.txt", "r");
            printf("result: %s\n", fgets(execute, 100, fp));
        } else if (strcmp(cmd, "exit") == 0) {
            printf("exit\n");
            break;
        } else if (strcmp(cmd, "help") == 0) {
            strcat(execute, "-h");
            system(execute);
        // } else if (strcmp(cmd, "fullwrite") == 0) {
        //     for(int i=0;i<100;i++) {
        //         strcat(execute, "W ");
        //         char arg[3];
        //         arg[0] = '0' + i/10;
        //         arg[1] = '0' + i%10;
        //         arg[2] = '\0';
        //         strcat(execute, arg);
        //         strcat(execute, " ");
        //         strcat(execute, arg2);
        //         system(execute);
        //     }
        // } else if (strcmp(cmd, "fullread") == 0) {
        //     for(int i=0;i<100;i++) {
        //         strcat(execute, "R ");
        //         char arg[3];
        //         arg[0] = '0' + i/10;
        //         arg[1] = '0' + i%10;
        //         arg[2] = '\0';
        //         strcat(execute, arg);
        //         system(execute);
        //         FILE *fp = fopen("result.txt", "r");
        //         printf("%s\n", fgets(execute, 100, fp));
        //         fclose(fp);
        //     }
        } else {
            printf("INVALID COMMAND\n");
        }
    }

    return 0;
}