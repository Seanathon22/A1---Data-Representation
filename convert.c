// CS 3503 Assignment 2 - Number Representation Conversion
// Author: Sean Sprinkle
// Description: Implements octal/hex mapping and signed integer representations

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ------------------------------
// Helper functions
// ------------------------------

// Pad binary string with leading zeros
void pad_binary(char *str, int width) {
    int len = strlen(str);
    if (len >= width) return;
    memmove(str + (width - len), str, len + 1);
    for (int i = 0; i < width - len; i++) str[i] = '0';
}

// Convert unsigned int to binary string
void uint_to_bin(uint32_t n, char *out, int bits) {
    out[bits] = '\0';
    for (int i = bits - 1; i >= 0; i--) {
        out[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
}

// ------------------------------
// Function: oct_to_bin
// Direct 3-bit mapping from octal to binary
// ------------------------------
void oct_to_bin(uint32_t oct, char *out) {
    char temp[65] = "";
    char buffer[4];
    int digits[22];  // max octal digits for 32-bit unsigned
    int i = 0;

    if (oct == 0) {
        strcpy(out, "000");
        return;
    }

    // Extract octal digits (least significant first)
    while (oct > 0) {
        digits[i++] = oct % 8;
        oct /= 8;
    }

    // Convert digits to binary (MSB first)
    for (int j = i - 1; j >= 0; j--) {
        for (int k = 2; k >= 0; k--) {
            buffer[2 - k] = ((digits[j] >> k) & 1) ? '1' : '0';
        }
        buffer[3] = '\0';
        strcat(temp, buffer);
    }
    strcpy(out, temp);
}

// ------------------------------
// Function: oct_to_hex
// Convert octal to hexadecimal via binary intermediate
// ------------------------------
void oct_to_hex(uint32_t oct, char *out) {
    char bin[65];
    oct_to_bin(oct, bin);
    int len = strlen(bin);
    int padded_len = ((len + 3) / 4) * 4;  // round up to multiple of 4
    char padded[65];
    strcpy(padded, bin);
    pad_binary(padded, padded_len);

    int hex_len = padded_len / 4;
    char result[17] = "";
    for (int i = 0; i < padded_len; i += 4) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = (val << 1) | (padded[i + j] - '0');
        }
        if (val < 10) result[i / 4] = '0' + val;
        else result[i / 4] = 'A' + (val - 10);
    }
    result[hex_len] = '\0';
    strcpy(out, result);
}

// ------------------------------
// Function: hex_to_bin
// Direct 4-bit mapping from hex to binary
// ------------------------------
void hex_to_bin(const char *hex, char *out) {
    char temp[65] = "";
    for (int i = 0; hex[i]; i++) {
        char c = toupper(hex[i]);
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else val = 0;

        for (int k = 3; k >= 0; k--) {
            temp[strlen(temp)] = ((val >> k) & 1) ? '1' : '0';
            temp[strlen(temp)] = '\0';
        }
    }
    strcpy(out, temp);
}

// ------------------------------
// Function: to_sign_magnitude
// 32-bit signed integer
// ------------------------------
void to_sign_magnitude(int32_t n, char *out) {
    uint32_t mag = (n < 0) ? -n : n;
    uint_to_bin(mag, out + 1, 31);
    out[0] = (n < 0) ? '1' : '0';
    out[32] = '\0';
}

// ------------------------------
// Function: to_ones_complement
// 32-bit signed integer
// ------------------------------
void to_ones_complement(int32_t n, char *out) {
    if (n >= 0) {
        to_sign_magnitude(n, out);
        out[0] = '0';
    } else {
        to_sign_magnitude(-n, out);
        for (int i = 0; i < 32; i++) out[i] = (out[i] == '0') ? '1' : '0';
    }
    out[32] = '\0';
}

// ------------------------------
// Function: to_twos_complement
// 32-bit signed integer
// ------------------------------
void to_twos_complement(int32_t n, char *out) {
    if (n >= 0) {
        uint_to_bin((uint32_t)n, out, 32);
    } else {
        uint32_t val = (uint32_t)(-n);
        val = ~val + 1;
        uint_to_bin(val, out, 32);
    }
}
