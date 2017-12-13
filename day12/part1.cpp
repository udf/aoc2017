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
        std::vector<uint> program_ids;
        for (auto match : matches) {
            program_ids.push_back(std::stoi(match.str()));
        }

        for (size_t i = 1; i < program_ids.size(); i++) {
            links[program_ids[0]].push_back(program_ids[i]);
        }
    }

    std::set<uint> visited;
    visit_from(0, links, visited);

    cout << visited.size() << endl;

    return 0;
}