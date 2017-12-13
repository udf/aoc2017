#include <iostream>
#include <regex>
#include <vector>
#include <math.h>

int main() {
    std::string line;
    std::vector<int> scan_depths;
    std::regex digit_capture("(\\d+)");

    while(std::getline(std::cin, line)) {
        std::vector<std::smatch> matches(
            std::sregex_iterator(line.begin(), line.end(), digit_capture),
            std::sregex_iterator()
        );
        if (matches.size() < 2)
            continue;

        size_t layer = std::stoi(matches[0].str());
        if (layer >= scan_depths.size()) {
            scan_depths.resize(layer + 1);
        }
        scan_depths[layer] = std::stoi(matches[1].str());
    }

    int delay = 0;
    bool success;
    do {
        success = true;
        delay++;
        for (size_t i = 0; i < scan_depths.size(); i++) {
            if (scan_depths[i] <= 0)
                continue;

            if ((i + delay) % ((scan_depths[i] - 1) * 2) == 0) {
                success = false;
                break;
            }
        }
    } while (!success);

    std::cout << delay << std::endl;

    return 0;
}