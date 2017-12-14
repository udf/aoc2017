#include <stdio.h>
#include <stdlib.h>

#include "../day10/knot.h"

int main() {
    //char *input = "flqrgnkx";
    char *input = "jxqlasbh"; //real
    char in_data[12];
    char hash[32];

    size_t used = 0;

    for (unsigned char i = 0; i < 128; ++i) {
        sprintf(in_data, "%s-%d", input, i);
        knot_hash_64(in_data, hash);

        char hex_char[2];
        hex_char[1] = '\0';

        // loop through characters
        for (size_t j = 0; j < 32; ++j) {
            hex_char[0] = hash[j];
            unsigned char half_byte = strtol(hex_char, NULL, 16);

            // loop through bits
            for (int k = 3; k >= 0; --k) {
                if ((half_byte >> k) & 0x1) {
                    used++;
                }
            }
        }
    }

    printf("%d\n", used);
    return 0;
}