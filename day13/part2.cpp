#include <iostream>
#include <regex>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

int triangle_wave(int t, int f) {
    return abs(((t+f) % (f*2)) - f);
}

int main() {
    using std::cout;
    using std::endl;

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
        size_t depth = std::stoi(matches[1].str());

        if (layer >= scan_depths.size()) {
            scan_depths.resize(layer + 1);
        }
        scan_depths[layer] = depth;
    }

    int time = 0;
    std::set<int> packets;

    while (true) {
        packets.insert(time);

        for (size_t i = 0; i < scan_depths.size(); ++i) {
            if (scan_depths[i] == 0) {
                continue;
            }

            const int position = triangle_wave(time + 1, scan_depths[i] - 1);

            // if we are at position 0, remove the packet if there is one
            if (time >= (int)i && position == 0) {
                packets.erase(time - i);
            }
        }

        // if packet with the lowest delay has made it to the end then stop
        if (packets.size() > 0) {
            const auto lowest_it = std::min_element(packets.begin(), packets.end());
            const int position = time - *lowest_it;
            if (position >= (int)scan_depths.size()) {
                cout << "packet #" << ((*lowest_it) + 1) << " has made it through " << endl;
                break;
            }
        }
        time++;
    }


    return 0;
}