#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
}

int main() {
    FILE *file = fopen("tests.txt", "r");
    if (!file) { printf("Cannot open tests.txt\n"); return 1; }

    char line[256];
    FILE *output = fopen("output.txt", "w");
    int total = 0, passed = 0;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (line[0] == '#' || strlen(line) == 0) continue;

        char func[50], expected[65];
        uint32_t input1;
        int input2;
        int items = sscanf(line, "%s %u %d %s", func, &input1, &input2, expected);

        char result[65];

        if (strncmp(func, "div_convert", 11) == 0) {
            div_convert(input1, input2, result);
            if (items != 4) { fprintf(output, "Invalid line: %s\n", line); continue; }
        } else if (strncmp(func, "sub_convert", 11) == 0) {
            sub_convert(input1, input2, result);
            if (items != 4) { fprintf(output, "Invalid line: %s\n", line); continue; }
        } else if (strncmp(func, "print_tables", 12) == 0) {
            fprintf(output, "Print tables for %u:\n", input1);
            print_tables(input1);
            continue;
        } else continue;

        total++;
        if (strcmp(result, expected) == 0) {
            passed++;
            fprintf(output, "PASS: %s %u %d → %s\n", func, input1, input2, result);
        } else {
            fprintf(output, "FAIL: %s %u %d → got %s, expected %s\n", func, input1, input2, result, expected);
        }
    }

    fprintf(output, "\nTest results: %d/%d passed\n", passed, total);

    fclose(file);
    fclose(output);
    return 0;
}
