#include <iostream>
#include <sstream>
#include <unordered_map>
#include <math.h>
#include "common.h"

/*
  \ n  /
nw +--+ ne
  /    \
-+      +-
  \    /
sw +--+ se
  / s  \

checkerboard:
   n
nw   ne
   0
sw   se
   s
*/
int main() {
    std::unordered_map <std::string, std::pair<int, int>> directions;
    directions["n"] = {0, 2};
    directions["s"] = {0, -2};
    directions["ne"] = {1, 1};
    directions["se"] = {1, -1};
    directions["nw"] = {-1, 1};
    directions["sw"] = {-1, -1};

    std::string direction;
    std::pair<int, int> position = {0, 0};

    while(std::getline(std::cin, direction, ',')) {
        trim(direction);

        if (!has_key(directions, direction)) {
            std::cout << "?" << direction << "?" << std::endl;
            continue;
        }
        position += directions[direction];
    }

    std::cout << (abs(position.first) + abs(position.second)) / 2 << " steps" << std::endl;

    return 0;
}