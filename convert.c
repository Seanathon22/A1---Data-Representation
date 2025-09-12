---

### **convert.c**
```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Converts an unsigned integer n to the given base (2-16)
// Stores the result as a null-terminated string in 'out'
void div_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF"; 
    char buffer[65]; // enough for 64-bit binary + null terminator
    int i = 0;

    if (base < 2 || base > 16) {
        sprintf(out, "Error: base must be between 2 and 16");
        return;
    }

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    while (n > 0) {
        int remainder = n % base;
        buffer[i++] = digits[remainder];
        n /= base;
    }

    for (int j = 0; j < i; j++) {
        out[j] = buffer[i - j - 1];
    }
    out[i] = '\0';
}
