#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

struct Node {
    Node *parent;
    std::vector<Node*> children;
    std::vector<std::string> children_names;
    uint weight;
    uint tower_weight;
    bool is_balanced;
    std::string name;

    Node(std::string in_name) : name(in_name) {
        weight = 0;
        tower_weight = 0;
        is_balanced = true;
    }

    void add_child(Node *child) {
        this->children.push_back(child);
        child->parent = this;
    }

    void weigh_tower() {
        this->tower_weight = this->weight;
        // recursively ask children to calculate their weights, and add it to ours
        for (auto child : this->children) {
            child->weigh_tower();
            this->tower_weight += child->tower_weight;
        }

        this->is_balanced = true;
        // check if we are balanced
        if (this->children.size() > 0) {
            uint first_weight = this->children[0]->tower_weight;
            for (size_t i = 1; i < this->children.size(); ++i) {
                if (first_weight != this->children[i]->tower_weight) {
                    this->is_balanced = false;
                    break;
                }
            }
        }
    }

    bool has_parent() {
        return this->parent != nullptr;
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
        Node *node = new Node(token);
        nodes[token] = node;

        // read weight (in brackets)
        line_stream >> token;
        node->weight = std::stoi(token.substr(1));

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
    Node *root;
    for (auto it : nodes) {
        Node *node = it.second;
        if (!node->parent) {
            root = node;
            break;
        }
    }
    if (!root) {
        cerr << "could not find root node" << endl;
        return 1;
    }

    // recursively weigh towers from the root
    root->weigh_tower();

    // move root down the tree until we find a node whose children are all balanced
    while (true) {
        bool all_balanced = true;
        for (auto child : root->children) {
            if (!child->is_balanced){
                root = child;
                all_balanced = false;
                break;
            }
        }
        if (all_balanced) 
            break;
    }

    // TODO: figure out how to find the offending node instead of doing it manually
    for (auto child : root->children) {
        cout << child->name << " w:" << child->weight << " tw:" << child->tower_weight << endl;
    }

    // clean up nodes
    for (auto it : nodes) {
        delete it.second;
    }
    return 0;
}