#include <stdio.h>
#include <stdlib.h>

#include "../day10/knot.h"

void remove_region(unsigned char grid[128][128], const int x, const int y) {
    if (x < 0 || x > 127 || y < 0 || y > 127)
        return;

    if (grid[x][y] == 0)
        return;

    grid[x][y] = 0;
    remove_region(grid, x + 1, y + 0);
    remove_region(grid, x + 0, y + 1);
    remove_region(grid, x - 1, y + 0);
    remove_region(grid, x + 0, y - 1);
}

int main() {
    char *input = "jxqlasbh";
    char in_data[12];
    char hash[32];

    unsigned char grid[128][128];
    // calculate hashes and put them in the grid
    for (unsigned char x = 0; x < 128; ++x) {
        sprintf(in_data, "%s-%d", input, x);
        knot_hash_64(in_data, hash);

        char hex_char[2];
        hex_char[1] = '\0';

        // loop through characters
        for (size_t j = 0; j < 32; ++j) {
            hex_char[0] = hash[j];
            unsigned char half_byte = strtol(hex_char, NULL, 16);

            // loop through bits
            for (size_t k = 0; k < 4; ++k) {
                grid[x][(j << 2) + k] = (half_byte >> (3 - k)) & 0x1;    
            }
        }
    }

    // count regions by recursively removing them
    int regions = 0;
    for (int x = 0; x < 128; ++x) {
        for (int y = 0; y < 128; ++y) {
            if (grid[x][y]) {
                remove_region(grid, x, y);
                regions++;
            }
        }
    }
    printf("%d\n", regions);

    return 0;
}