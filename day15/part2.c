#include <stdio.h>

size_t next(const size_t prev, const size_t fact) {
    return (prev * fact) % 2147483647;
}

size_t next_mul(const size_t prev, const size_t fact, const size_t mul) {
    size_t new = prev;
    do {
        new = next(new, fact);
    } while (new % mul != 0);
    return new;
}

int main() {
    const size_t gen_A_fact = 16807;
    const size_t gen_B_fact = 48271;

    // input
    size_t gen_A = 512;
    size_t gen_B = 191;

    unsigned match_count = 0;

    for (size_t i = 0; i < 5000000; ++i) {
        gen_A = next_mul(gen_A, gen_A_fact, 4);
        gen_B = next_mul(gen_B, gen_B_fact, 8);

        if ((gen_A & 0xFFFF) == (gen_B & 0xFFFF)) {
            match_count++;
        }
    }

    printf("%u\n", match_count);

    return 0;
}