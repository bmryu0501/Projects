#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

void write(int address, char* value) {
    FILE* fp = fopen("nand.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fseek(fp, address * 4, SEEK_SET);
    fprintf(fp, "%d", value);
    fclose(fp);
}