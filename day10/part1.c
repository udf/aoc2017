#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_LEN 256

void reverse_section(
    int list[], const size_t list_length,
    const size_t start, const size_t section_length) {

    const size_t half_section = section_length / 2;

    for (size_t i = 0; i < half_section; ++i) {
        const size_t first_i = (i + start) % list_length;
        const size_t second_i = (section_length - i - 1 + start) % list_length;

        int temp = list[first_i];
        list[first_i] = list[second_i];
        list[second_i] = temp;
    }
}

int main() {
    int list[LIST_LEN];
    for (size_t i = 0; i < LIST_LEN; i++)
        list[i] = i;

    size_t length;
    size_t position = 0;
    size_t skip = 0;
    while (scanf("%lu", &length) != EOF) {
        getchar(); // consume delimiter
        reverse_section(list, LIST_LEN, position, length);
        position += length + skip;
        skip++;
    }

    printf("%d\n", list[0] * list[1]);
    return 0;
}