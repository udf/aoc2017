#include <iostream>
#include <regex>
#include <vector>
#include <math.h>
#include <set>

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

    int time = 0;
    bool success = false;
    int delay;
    std::set<int> packets;

    do {
        // fire packet if we can
        if (scanners[0].position > 0)
            packets.insert(time);

        for (auto it = packets.begin(); it != packets.end(); ) {
            int position = time - *it;

            // if packet has made it to the end then stop
            if (position >= (int)scanners.size()) {
                delay = *it;
                success = true;
                break;
            }

            // remove packets that have moved into a scanner
            if (scanners[position].position == 0) {
                it = packets.erase(it);
                continue;
            }

            it++;
        }

        // move all scanners
        for (size_t i = 0; i < scanners.size(); ++i) {
            if (scanners[i].depth > 0)
                scanners[i].position = triangle_wave(time + 1, scanners[i].depth-1);
        }

        time++;
    } while(!success);

    cout << delay << endl;

    return 0;
}