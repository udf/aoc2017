#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

struct Node {
    Node *parent;
    std::vector<std::string> children_names;

    void add_child(Node *child) {
        child->parent = this;
    }
};

template <typename key_t, typename value_t>
bool has_key(const std::unordered_map<key_t, value_t> &map, const key_t key) {
    return map.find(key) != map.end();
}

int main() {
    using namespace std;
    
    string line;
    unordered_map<string, Node*> nodes;

    while (getline(cin, line)) {
        istringstream line_stream(line);
        string token;

        // read name
        line_stream >> token;
        Node *node = new Node();
        nodes[token] = node;

        // consume weight
        line_stream >> token;

        // consume arrow
        line_stream >> token;

        // read other node names, store them as strings for now
        while (line_stream >> token) {
            if (token.back() == ',')
                token.pop_back();
            node->children_names.push_back(token);
        }
    }

    // resolve names of children from strings to pointers
    for (auto it : nodes) {
        Node *node = it.second;
        for (auto child_name : node->children_names) {
            if (has_key(nodes, child_name))
                node->add_child(nodes[child_name]);
            // note: we would probably warn if we can't find the node by name
        }
    }

    // find root node (first one with no parents)
    for (auto it : nodes) {
        Node *node = it.second;
        if (!node->parent) {
            cout << it.first << endl;
            break;
        }
    }

    // clean up nodes
    for (auto it : nodes) {
        delete it.second;
    }
    return 0;
}