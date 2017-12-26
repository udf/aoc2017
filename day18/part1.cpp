#include <iostream>
#include <sstream> 
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

struct Arg {
    char reg_name = '\0';
    long value = 0;

    long get(std::unordered_map<char, long> &registers) const {
        if (reg_name)
            return registers[reg_name];
        return value;
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

    std::unordered_map<char, long> registers;
    std::vector<std::function<void()>> instructions;
    int last_sound = 0;
    int instr_i = 0;
    bool halt = false;

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
                [&registers, &last_sound, arg1]() {
                    last_sound = arg1.get(registers);
                }
            );
        } else if (instr == "set") {
            instructions.push_back(
                [&registers, arg1, arg2]() {
                    registers[arg1.reg_name] = arg2.get(registers);
                }
            );
        } else if (instr == "add") {
            instructions.push_back(
                [&registers, arg1, arg2]() {
                    registers[arg1.reg_name] += arg2.get(registers);
                }
            );
        } else if (instr == "mul") {
            instructions.push_back(
                [&registers, arg1, arg2]() {
                    registers[arg1.reg_name] *= arg2.get(registers);
                }
            );
        } else if (instr == "mod") {
            instructions.push_back(
                [&registers, arg1, arg2]() {
                    registers[arg1.reg_name] %= arg2.get(registers);
                }
            );
        } else if (instr == "rcv") {
            instructions.push_back(
                [&registers, &last_sound, &halt, arg1]() {
                    if (arg1.get(registers) != 0) {
                        std::cout << "recovered snd: " << last_sound << std::endl;
                        halt = true;
                    }
                }
            );
        } else if (instr == "jgz") {
            instructions.push_back(
                [&registers, &instr_i, arg1, arg2]() {
                    if (arg1.get(registers) > 0)
                        instr_i += arg2.get(registers) - 1;
                }
            );
        }
    }

    while (instr_i >= 0 && instr_i < instructions.size()) {
        instructions[instr_i]();
        instr_i++;
        if (halt)
            break;
    }

    return 0;
}