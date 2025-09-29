// CS 3503 Assignment 2 - Test Driver
// Author: Sean Sprinkle
// Description: Reads test cases from A2_tests.txt, executes functions, writes results

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void oct_to_bin(uint32_t oct, char *out);
void oct_to_hex(uint32_t oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

// Helper to trim whitespace
void trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

int main() {
    FILE *file = fopen("A2_tests.txt", "r");
    FILE *out_file = fopen("output.txt", "w");
    if (!file) {
        printf("Error: could not open A2_tests.txt\n");
        return 1;
    }

    char line[256];
    int total = 0, passed = 0;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (line[0] == '#' || strlen(line) == 0) continue;

        char func[50], expected[65];
        char input1_str[50], input2_str[50];
        int items = sscanf(line, "%s %s %s %s", func, input1_str, input2_str, expected);

        // Skip lines that don't match expected format
        if (items < 3) {
            fprintf(out_file, "Invalid test line: %s\n", line);
            continue;
        }

        char result[65] = "";

        if (strcmp(func, "oct_to_bin") == 0) {
            uint32_t n = (uint32_t)strtoul(input1_str, NULL, 10);
            oct_to_bin(n, result);
        } else if (strcmp(func, "oct_to_hex") == 0) {
            uint32_t n = (uint32_t)strtoul(input1_str, NULL, 10);
            oct_to_hex(n, result);
        } else if (strcmp(func, "hex_to_bin") == 0) {
            hex_to_bin(input1_str, result);
        } else if (strcmp(func, "to_sign_magnitude") == 0) {
            int32_t n = atoi(input1_str);
            to_sign_magnitude(n, result);
        } else if (strcmp(func, "to_ones_complement") == 0) {
            int32_t n = atoi(input1_str);
            to_ones_complement(n, result);
        } else if (strcmp(func, "to_twos_complement") == 0) {
            int32_t n = atoi(input1_str);
            to_twos_complement(n, result);
        } else {
            fprintf(out_file, "Unknown function: %s\n", func);
            continue;
        }

        total++;
        if (strcmp(result, expected) == 0) {
            passed++;
            fprintf(out_file, "PASS: %s %s -> %s\n", func, input1_str, result);
        } else {
            fprintf(out_file, "FAIL: %s %s -> got %s, expected %s\n", func, input1_str, result, expected);
        }
    }

    fprintf(out_file, "\nTest results: %d/%d passed\n", passed, total);

    fclose(file);
    fclose(out_file);

    printf("Test execution complete. Results written to output.txt\n");
    return 0;
}
