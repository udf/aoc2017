#include <stdio.h>
#include <stdlib.h>

#include "knot.h"

int main() {
    char *in_data = NULL;
    size_t length;
    size_t n_read = getline(&in_data, &length, stdin);
    in_data[n_read - 1] = '\0';

    char hash[32];
    knot_hash_64(in_data, hash);
    printf("%s\n", hash);

    free(in_data);

    return 0;
}