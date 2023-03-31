#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

uint32_t hexToUint32(char* hex);
void uint32ToHex(uint32_t num, char* hex);

uint32_t hexToUint32(char* hex) {
    uint32_t result = 0;
    int len = strlen(hex);
    for (int i = 0; i < len; i++) {
        result = result << 4;
        if (hex[i] >= '0' && hex[i] <= '9') {
            result += hex[i] - '0';
        } else {
            result += hex[i] - 'A' + 10;
        }
    }
    return result;
}

void uint32ToHex(uint32_t num, char* hex) {
    for (int i = 7; i >= 0; i--) {
        uint8_t digit = num & 0xF;
        if (digit < 10) {
            hex[i] = digit + '0';
        } else {
            hex[i] = digit - 10 + 'A';
        }
        num = num >> 4;
    }
}