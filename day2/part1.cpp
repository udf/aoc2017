#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    string line;
    uint sum = 0;
    while (getline(cin, line)) {
        istringstream row_stream(line);
        uint n;
        row_stream >> n;
        uint max = n, min = n;
        while (row_stream >> n) {
            max = std::max(max, n);
            min = std::min(min, n);
        }
        sum += max - min;
    }

    cout << sum;

    return 0;
}