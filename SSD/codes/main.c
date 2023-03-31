#define READ_TO_FILE
#include "ssdio.h"

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef SSDINFO_H
#define SSDINFO_H
#include "ssdinfo.h"
#endif

int main(int argc, char** argv) {
    /* Usage
    1. ssd W <int address> <hex value>
    2. ssd R <int address>
    hex value form: 0x00000000
    */

    // print help
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage:\n");
        printf("1. ssd W <int address> <hex value>\n");
        printf("2. ssd R <int address>\n");
        return 0;
    }

    if(argc != 3 && argc != 4) {
        printf("Invalid input!\n");
        printf("Try ssd -h for help\n");
        return 0;
    }
    
    char* mode = argv[1];
    int address = atoi(argv[2]);
    char* hex;
    if(argc == 4) {
        hex = argv[3];
    }

    /* 
    min address = 0
    max address = 99
    length of hex = 10 (0x00000000)
    */

    if (address < 0 || address >= SIZE_OF_SSD) {
        printf("Address must be between 0 and 99\n");
        return 0;
    }

    if (argc == 4 && strlen(hex) != 10) {
        printf("Hex value must be 10 characters long\n");
        return 0;
    }

    /*
    execute the command
    */

    if (strcmp(mode, "W") == 0) {
        writeSSD(address, hex);
    } else if (strcmp(mode, "R") == 0) {
        readSSD(address);
    } else {
        printf("Invalid input!\n");
    }
    
    return 0;
}