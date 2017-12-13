#include <iostream>
#include <regex>
#include <vector>
#include <unordered_map>
#include <set>

template <typename key_t>
bool has_key(const std::set<key_t> &set, const key_t key) {
    return set.find(key) != set.end();
}

template <typename T>
void visit_from(const T start, const std::unordered_map<T, std::vector<T>> &links, std::set<T> &visited) {
    visited.insert(start);

    for (auto node : links.at(start)) {
        if (!has_key(visited, node)) {
            visit_from(node, links, visited);
        }
    }
}

int main() {
    using std::cout;
    using std::endl;

    std::string line;

    std::unordered_map<uint, std::vector<uint>> links;
    std::regex digit_capture("(\\d+)");

    while(std::getline(std::cin, line)) {
        std::vector<std::smatch> matches(
            std::sregex_iterator(line.begin(), line.end(), digit_capture),
            std::sregex_iterator()
        );
        if (matches.size() < 2)
            continue;

        uint parent_id = std::stoi(matches[0].str());
        for (size_t i = 1; i < matches.size(); i++) {
            links[parent_id].push_back(std::stoi(matches[i].str()));
        }
    }

    size_t num_groups = 0;
    while (links.size() > 0) {
        std::set<uint> visited;
        visit_from(links.begin()->first, links, visited);

        if (visited.size() > 0) {
            num_groups++;
        }

        for (auto program_id : visited) {
            links.erase(program_id);
        }
    }

    cout << num_groups << endl;

    return 0;
}