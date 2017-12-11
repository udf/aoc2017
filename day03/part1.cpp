#include <iostream>
#include "common.h"

uint spiral_dist(const uint num) {
    auto[x, y] = spiral_coord(num);
    return abs(x) + abs(y);
}

int main() {
    std::cout << spiral_dist(265149) << std::endl;
    return 0;
}