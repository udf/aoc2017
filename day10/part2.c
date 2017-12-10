#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPARSE_LEN 256
#define DENSE_BLOCK 16
#define DENSE_LEN SPARSE_LEN/DENSE_BLOCK

void reverse_section(
    char list[], const size_t list_length,
    const size_t start, const size_t section_length) {

    const size_t half_section = section_length / 2;

    for (size_t i = 0; i < half_section; ++i) {
        const size_t first_i = (i + start) % list_length;
        const size_t second_i = (section_length - i - 1 + start) % list_length;

        char temp = list[first_i];
        list[first_i] = list[second_i];
        list[second_i] = temp;
    }
}

int main() {
    const char *PREFIX = "\x11\x1f\x49\x2f\x17";

    // set up data
    char sparse_hash[SPARSE_LEN];
    char dense_hash[DENSE_LEN];
    for (size_t i = 0; i < SPARSE_LEN; i++)
        sparse_hash[i] = i;

    // read line and remove last character if newline
    char *in_data = NULL;
    size_t length;
    size_t n_read = getline(&in_data, &length, stdin);
    in_data[n_read - 1] = '\0';
    printf("%s\n", in_data);

    // concat prefix to the end of the read data
    size_t lengths_count = strlen(in_data) + strlen(PREFIX);
    char *lengths = malloc(lengths_count + 1);
    strcat(lengths, in_data);
    strcat(lengths, PREFIX);
    free(in_data);
    
    // calculate sparse hash
    size_t position = 0;
    size_t skip = 0;
    for (int iters = 0; iters < 64; iters++) {
        for (size_t i = 0; i < lengths_count; i++) {
            length = lengths[i];
            reverse_section(sparse_hash, SPARSE_LEN, position, length);
            position = (position + length + skip) % SPARSE_LEN;
            skip++;
        }
    }

    // calculate dense hash
    for (size_t i = 0; i < DENSE_LEN; ++i) {
        dense_hash[i] = sparse_hash[i * DENSE_BLOCK];
        for (size_t j = 1; j < DENSE_BLOCK; j++) {
            dense_hash[i] ^= sparse_hash[i * DENSE_BLOCK + j];
        }
    }

    // output dense hash
    for (size_t i = 0; i < DENSE_LEN; ++i) {
        printf("%x", dense_hash[i] & 0xff);
    }
    printf("\n");

    return 0;
}