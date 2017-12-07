#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <algorithm>

template <typename T>
bool has_duplicates(std::vector<T> const& list) {
    std::unordered_map<T, bool> used_items;

    for (auto item : list) {
        if (used_items[item])
            return true;
        used_items[item] = true;
    }

    return false;
}

int main() {
    using namespace std;
    
    string line;
    uint total_valid = 0;

    while (getline(cin, line)) {
        istringstream line_stream(line);

        vector<string> words(
            (std::istream_iterator<string>(line_stream)),
            std::istream_iterator<string>()
        );
        for (size_t i = 0; i < words.size(); ++i)
            std::sort(words[i].begin(), words[i].end());

        total_valid += has_duplicates(words) ? 0 : 1;
    }

    cout << total_valid << endl;

    return 0;
}