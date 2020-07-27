// > gcc -Wall -Wextra -std=c99 read1.c -o read1
// > read1
// Low-level reading of the entire file into memory and its processing.
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("example.bin", "rb");
    if (f == NULL) {
        return 1;
    }
    // Determine the file size (alternatively, you could use fstat, for example).
    fseek(f, 0, SEEK_END); // Move the cursor to the end of the file.
    size_t file_size = ftell(f); // Read the cursor position.
    fseek(f, 0, SEEK_SET) // Move the cursor back to the beginning of the file.

    // Allocate a buffer of sufficient size and load the contents of the file.
    uint8_t *buffer = malloc(file_size);
    fread(buffer, 1, file_size, f);
    fclose(f);

    // Process the file by listing the information obtained.
    // Note: the code below does not contain any verification of correctness
    // and availability of the declared amount of data in relation to the
    // actual file size.

    // Load number of datasets.
    uint8_t *p = buffer;
    uint16_t n = *(uint16_t *)p;
    p += sizeof(uint16_t); // 2

    printf("Data set count: %u\n", n);

    // Load sets.
    for (size_t i = 0; i < n; i++) {
        uint8_t m = *p++;
        printf("Set %u (size: %u): ", i, m);

        for (size_t j = 0; j < m; j++) {
            // Read mismatched 32-bit values from memory - this code is not
            // portable but will work fine on the selected platform
            // (x86, Windows 7, and Ubuntu).
            printf("%u ", *(uint32_t *)p);
            p += sizeof(uint32_t); // 4
        }

        putchar('\n');
    }

    free(buffer);
    return 0;
}