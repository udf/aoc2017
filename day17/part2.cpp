#include <iostream>

int main() {
    using std::cout;
    using std::endl;
    const uint step = 359; // input

    uint pos = 0;
    uint after_0 = 0;
    for (uint i = 1; i <= 50000000; i++) {
        pos = (pos + step) % i;

        if (pos == 0) {
            after_0 = i;
        }
        pos++;
    }

    cout << after_0 << endl;

    return 0;
}