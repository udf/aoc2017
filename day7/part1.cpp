#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

struct Node {
    bool has_parent;
    uint weight;

    Node() {
        has_parent = false;
        weight = 0;
    }
};

int main() {
    using namespace std;
    
    string line;
    unordered_map<string, Node> nodes;

    while (getline(cin, line)) {
        istringstream line_stream(line);
        string name;
        line_stream >> name;

        // weight in brackets
        string token;
        line_stream >> token;
        nodes[name].weight = std::stoi(token.substr(1));

        // consume arrow
        line_stream >> token;

        // other node names
        while (line_stream >> token) {
            if (token.back() == ',')
                token.pop_back();
            nodes[token].has_parent = true;
        }
    }

    cout << "Nodes without any parents:" << endl;
    for (auto it : nodes) {
        const string name = it.first;
        Node node = it.second;
        if (!node.has_parent) {
            cout << name << endl;
        }
    }

    return 0;
}