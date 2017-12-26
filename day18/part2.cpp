#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <memory>

struct Arg {
    char reg_name = '\0';
    long value = 0;

    long get(std::unordered_map<char, long> &registers) const {
        if (reg_name)
            return registers[reg_name];
        return value;
    }
};

struct State {
    std::unordered_map<char, long> registers;
    std::queue<long> data;
    bool receiving = false;
    bool running = true;
    int instr_i = 0;
    size_t send_count = 0;
    long pid;

    State(long id) {
        registers['p'] = id;
        pid = id;
    }

    void run(std::vector<std::function<void(State*, State*)>> &instructions, State *other) {
        if (!running)
            return;

        instructions[instr_i](this, other);
        instr_i++;
        if (instr_i < 0 || instr_i >= instructions.size())
            running = false;
    }

    bool waiting() {
        return receiving && data.empty();
    }
};

void read_arg(const std::string &str, Arg &arg) {
    std::stringstream ss(str);
    if (ss >> arg.value) {
        return;
    }
    arg.reg_name = str[0];
}

int main() {
    using std::cout;
    using std::endl;

    std::unique_ptr<State> current = std::make_unique<State>(0);
    std::unique_ptr<State> other = std::make_unique<State>(1);

    std::vector<std::function<void(State*, State*)>> instructions;

    // load instructions into vector of functions
    std::string line;
    while(std::getline(std::cin, line)) {
        std::stringstream ss(line);

        std::string instr;
        ss >> instr;

        Arg arg1, arg2;
        std::string argstr;
        ss >> argstr;
        read_arg(argstr, arg1);
        if (ss >> argstr)
            read_arg(argstr, arg2);

        if (instr == "snd") {
            instructions.push_back(
                [arg1](State *current, State *other) {
                    other->data.push(arg1.get(current->registers));
                    current->send_count++;
                }
            );
        } else if (instr == "set") {
            instructions.push_back(
                [arg1, arg2](State *current, State *other) {
                    current->registers[arg1.reg_name] = arg2.get(current->registers);
                }
            );
        } else if (instr == "add") {
            instructions.push_back(
                [arg1, arg2](State *current, State *other) {
                    current->registers[arg1.reg_name] += arg2.get(current->registers);
                }
            );
        } else if (instr == "mul") {
            instructions.push_back(
                [arg1, arg2](State *current, State *other) {
                    current->registers[arg1.reg_name] *= arg2.get(current->registers);
                }
            );
        } else if (instr == "mod") {
            instructions.push_back(
                [arg1, arg2](State *current, State *other) {
                    current->registers[arg1.reg_name] %= arg2.get(current->registers);
                }
            );
        } else if (instr == "rcv") {
            instructions.push_back(
                [arg1](State *current, State *other) {
                    if (current->data.empty()) {
                        current->receiving = true;
                        current->instr_i--;
                        return;
                    }
                    current->registers[arg1.reg_name] = current->data.front();
                    current->data.pop();
                    current->receiving = false;
                }
            );
        } else if (instr == "jgz") {
            instructions.push_back(
                [arg1, arg2](State *current, State *other) {
                    if (arg1.get(current->registers) <= 0)
                        return;
                    current->instr_i += arg2.get(current->registers) - 1;
                }
            );
        }
    }

    // run until both halt or both are waiting for data
    while (current->running && other->running) {
        current->run(instructions, other.get());
        if (current->receiving) {
            current.swap(other);
        }

        if (current->waiting() && other->waiting()) {
            break;
        }
    }

    if (current->pid == 0)
        current.swap(other);

    cout << current->send_count << endl;

    return 0;
}