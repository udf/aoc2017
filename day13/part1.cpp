#include <iostream>
#include <regex>
#include <vector>
#include <math.h>

struct Scanner
{
    int position = -1;
    size_t depth = 0;
};

int triangle_wave(int t, int f) {
    return abs(((t+f) % (f*2)) - f);
}

int main() {
    using std::cout;
    using std::endl;

    std::string line;
    std::vector<Scanner> scanners;
    std::regex digit_capture("(\\d+)");

    while(std::getline(std::cin, line)) {
        std::vector<std::smatch> matches(
            std::sregex_iterator(line.begin(), line.end(), digit_capture),
            std::sregex_iterator()
        );
        if (matches.size() < 2)
            continue;

        size_t layer = std::stoi(matches[0].str());
        size_t depth = std::stoi(matches[1].str());

        if (layer >= scanners.size()) {
            scanners.resize(layer + 1);
        }
        scanners[layer].depth = depth;
        scanners[layer].position = 0;
    }

    size_t severity = 0;
    for (size_t i = 0; i < scanners.size(); ++i) {
        // check if we moved into a scanner
        if (scanners[i].position == 0) {
            cout << "caught at layer " << i << endl;
            severity += i * scanners[i].depth;
        }

        // move all scanners
        for (size_t j = 0; j < scanners.size(); ++j) {
            cout << scanners[j].position << " ";

            if (scanners[j].depth > 0)
                scanners[j].position = triangle_wave(i + 1, scanners[j].depth-1);
        }
        cout << endl;
    }

    cout << severity << endl;

    return 0;
}