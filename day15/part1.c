#include <stdio.h>

size_t next(const size_t prev, const size_t fact) {
    return (prev * fact) % 2147483647;
}

int main() {
    const size_t gen_A_fact = 16807;
    const size_t gen_B_fact = 48271;

    // input
    size_t gen_A = 512;
    size_t gen_B = 191;

    unsigned match_count = 0;

    for (size_t i = 0; i < 40000000; ++i) {
        gen_A = next(gen_A, gen_A_fact);
        gen_B = next(gen_B, gen_B_fact);

        if ((gen_A & 0xFFFF) == (gen_B & 0xFFFF)) {
            match_count++;
        }
    }

    printf("%u\n", match_count);

    return 0;
}