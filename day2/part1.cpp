#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    string line;
    uint sum = 0;
    
    while (getline(cin, line)) {
        istringstream row_stream(line);
        auto result = minmax_element(
            istream_iterator<uint>(row_stream),
            istream_iterator<uint>()
        );
        sum += *result.second - *result.first;
    }

    cout << sum << endl;;

    return 0;
}