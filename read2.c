// > gcc -Wall _wextra -std=c99 read2.c -o read2
// > read2

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("example.bin", "rb");
    if (f == NULL) {
        return 1;
    }

    // Process the file by listing the information obtained.
    // Note: the code below does not contain any
    // verification of correctness and availability of the
    // declared amount of data in relation to the actual
    // file size.

    // Load number of datasets.
    uint16_t n;
    fread(&n, sizeof(n), 1, f);
    printf("Data set count: %u\n", n);

    // Load sets.
    for (size_t i = 0; i < n; i++) {
        uint8_t m;
        fread(&m, sizeof(m), 1, f);

        printf("Set %u (size: %u): ", (unsigned int)i, m);

        uint32_t *data = malloc(m * sizeof(uint32_t));
        fread(data, sizeof(uint32_t), m, f);

        for (size_t j = 0; j < m; j++) {
            printf("%u ", data[j]);
        }
        putchar('\n')
        free(data);
    }

    fclose(f);
    return 0;
}