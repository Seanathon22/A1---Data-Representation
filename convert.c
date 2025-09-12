#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Division/remainder method
void div_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF";
    char buffer[65];
    int i = 0;

    if (base < 2 || base > 16) { strcpy(out, "Error"); return; }
    if (n == 0) { strcpy(out, "0"); return; }

    while (n > 0) {
        buffer[i++] = digits[n % base];
        n /= base;
    }
    for (int j = 0; j < i; j++) out[j] = buffer[i - j - 1];
    out[i] = '\0';
}

// Subtraction method
void sub_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF";
    char buffer[65];
    int i = 0;
    uint32_t power = 1;

    if (base < 2 || base > 16) { strcpy(out, "Error"); return; }
    if (n == 0) { strcpy(out, "0"); return; }

    // Find highest power
    while (power <= n / base) power *= base;

    while (power > 0) {
        int digit = n / power;
        buffer[i++] = digits[digit];
        n -= digit * power;
        power /= base;
    }
    buffer[i] = '\0';
    strcpy(out, buffer);
}

// Print tables for bit operations
void print_tables(uint32_t n) {
    char bin[65], oct[65], dec[65], hex[65];
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    sprintf(dec, "%u", n);
    div_convert(n, 16, hex);

    uint32_t left3 = n << 3;
    char bin3[65], oct3[65], dec3[65], hex3[65];
    div_convert(left3, 2, bin3);
    div_convert(left3, 8, oct3);
    sprintf(dec3, "%u", left3);
    div_convert(left3, 16, hex3);

    uint32_t andFF = n & 0xFF;
    char binFF[65], octFF[65], decFF[65], hexFF[65];
    div_convert(andFF, 2, binFF);
    div_convert(andFF, 8, octFF);
    sprintf(decFF, "%u", andFF);
    div_convert(andFF, 16, hexFF);

    printf("Original: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin, oct, dec, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin3, oct3, dec3, hex3);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%s Hex=%s\n", binFF, octFF, decFF, hexFF);
}
