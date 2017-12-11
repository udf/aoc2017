#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

uint div_first_two_divisible(std::vector<uint> &row) {
    std::sort(row.begin(), row.end());

    do {
        if (row[0] % row[1] == 0) {
            return row[0] / row[1];
        } else if (row[1] % row[0] == 0) {
            return row[1] / row[0];
        }
        std::reverse(row.begin() + 2, row.end());
    } while (std::next_permutation(row.begin(), row.end()));

    return 0;
}

int main() {
    std::string line;
    uint sum = 0;
    
    while (getline(std::cin, line)) {
        std::istringstream row_stream(line);
        std::vector<uint> row(
            (std::istream_iterator<uint>(row_stream)),
            std::istream_iterator<uint>()
        );
        sum += div_first_two_divisible(row);
    }

    std::cout << sum << std::endl;

    return 0;
}