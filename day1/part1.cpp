#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;

int main() {
    string data;
    cin >> data;
    
    size_t length = data.length();
    int sum = 0;
    for (size_t i = 0; i < length; ++i) {
        int digit = data[i % length] - '0';
        int next_digit = data[(i + 1) % length] - '0';
        
        if (digit == next_digit) {
            sum += digit;
        }
    }

    cout << sum;

    return 0;
}