#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

void knot_hash(const char *data, char* output, const size_t iter_count) {
    const char *PREFIX = "\x11\x1f\x49\x2f\x17";

    // set up data
    char sparse_hash[SPARSE_LEN];
    for (size_t i = 0; i < SPARSE_LEN; i++)
        sparse_hash[i] = i;

    // concat prefix to the end of the read data
    size_t lengths_count = strlen(data) + strlen(PREFIX);
    char *lengths = (char*)malloc(lengths_count + 1);
    strcat(lengths, data);
    strcat(lengths, PREFIX);

    // calculate sparse hash
    size_t position = 0;
    size_t skip = 0;
    for (size_t iters = 0; iters < iter_count; iters++) {
        for (size_t i = 0; i < lengths_count; i++) {
            reverse_section(sparse_hash, SPARSE_LEN, position, lengths[i]);
            position = (position + lengths[i] + skip) % SPARSE_LEN;
            skip++;
        }
    }
    free(lengths);

    // calculate and output dense hash
    for (size_t i = 0; i < DENSE_LEN; i++) {
        char dense_hash = sparse_hash[i * DENSE_BLOCK];
        for (size_t j = 1; j < DENSE_BLOCK; j++) {
            dense_hash ^= sparse_hash[i * DENSE_BLOCK + j];
        }
        sprintf(output + i*2, "%x", dense_hash & 0xff);
    }
}

void knot_hash_64(const char *data, char* output) {
    knot_hash(data, output, 64);
}