#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef SSDINFO_H
#define SSDINFO_H
#include "ssdinfo.h"
#endif

#ifndef HEX_H
#define HEX_H
#include "hex.h"
#endif

void writeSSD(int address, char* hex);
void readSSD(int address);

union LBA {
    uint32_t value;
    uint8_t bytes[4];
};

void writeSSD(int address, char* hex) {
    FILE *fp = fopen("nand.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fseek(fp, address * SIZE_OF_LBA, SEEK_SET);
    hex += 2;

    union LBA d;
    d.value = hexToUint32(hex);

    for(int i = 0; i < SIZE_OF_LBA; i++) {
        fputc(d.bytes[i], fp);
    }

    fclose(fp);
}

void readSSD(int address) {
    FILE *fp = fopen("nand.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fseek(fp, address * SIZE_OF_LBA, SEEK_SET);
    
    union LBA d;
    for(int i = 0; i < SIZE_OF_LBA; i++) {
        d.bytes[i] = fgetc(fp);
    }

    char hex[11];
    hex[0] = '0';
    hex[1] = 'x';
    hex[10] = '\0';
    uint32ToHex(d.value, hex+2);

    FILE *fresult = fopen("result.txt", "w");

    fprintf(fresult, "%s", hex);
}