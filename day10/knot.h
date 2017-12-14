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
    const unsigned char *PREFIX = "\x11\x1f\x49\x2f\x17";
    const size_t PREFIX_LEN = 5;

    // set up data
    char sparse_hash[SPARSE_LEN];
    for (size_t i = 0; i < SPARSE_LEN; i++)
        sparse_hash[i] = i;

    const size_t data_len = strlen(data);

    // calculate sparse hash
    size_t position = 0;
    size_t skip = 0;
    for (size_t iters = 0; iters < iter_count; iters++) {
        for (size_t i = 0; i < data_len + PREFIX_LEN; i++) {
            unsigned char length = i < data_len ? data[i] : PREFIX[i - data_len];
            
            reverse_section(sparse_hash, SPARSE_LEN, position, length);
            position = (position + length + skip) % SPARSE_LEN;
            skip++;
        }
    }

    // calculate and output dense hash
    for (size_t i = 0; i < DENSE_LEN; i++) {
        char dense_hash = sparse_hash[i * DENSE_BLOCK];
        for (size_t j = 1; j < DENSE_BLOCK; j++) {
            dense_hash ^= sparse_hash[i * DENSE_BLOCK + j];
        }
        sprintf(output + i*2, "%02x", dense_hash & 0xff);
    }
}

void knot_hash_64(const char *data, char* output) {
    knot_hash(data, output, 64);
}