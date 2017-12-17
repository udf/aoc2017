#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <functional>

void spin(std::string &str) {
    const char last = str.back();
    for (size_t i = str.size() - 1; i-- > 0;) {
        str[i + 1] = str[i];
    }
    str.front() = last;
}

void swapi(std::string &str, const unsigned i1, const unsigned i2) {
    std::swap(str[i1], str[i2]);
}

void swapv(std::string &str, const char c1, const char c2) {
    const unsigned i1 = str.find(c1);
    const unsigned i2 = str.find(c2);
    swapi(str, i1, i2);
}

int main() {
    using std::cout;
    using std::endl;

    std::string programs = "abcdefghijklmnop";
    std::vector<std::function<void()>> instructions;

    // load instructions into vector of functions
    char instruction;
    while(std::cin >> instruction) {
        switch (instruction) {
        case 's': // spin
            int size;
            std::cin >> size;

            instructions.push_back(
                [&programs, size]() {
                    for (int i = 0; i < size; i++) {
                        spin(programs);
                    }
                }
            );
            break;
        case 'x': // swap by index
            unsigned i1, i2;
            std::cin >> i1;
            std::cin >> instruction; // consume delimiter
            std::cin >> i2;

            instructions.push_back(
                [&programs, i1, i2]() {
                    swapi(programs, i1, i2);
                }
            );
            break;
        case 'p': // swap by value
            char c1, c2;
            std::cin >> c1;
            std::cin >> instruction; // consume delimiter
            std::cin >> c2;

            instructions.push_back(
                [&programs, c1, c2]() {
                    swapv(programs, c1, c2);
                }
            );
            break;
        }
    }

    // find out how many iters it takes before we loop back to the starting position
    size_t loop_iters;
    for (loop_iters = 1; loop_iters < 1000000000; loop_iters++) {
        for (const auto instruction : instructions)
            instruction();
        if (programs == "abcdefghijklmnop") {
            break;
        }
    }

    // run as many instructions as we need to
    for (size_t i = 0; i < 1000000000 % loop_iters; i++) {
        for (const auto instruction : instructions)
            instruction();
    }

    cout << programs << endl;

    return 0;
}