#include <iostream>
#include <list>

int main() {
    using std::cout;
    using std::endl;

    const uint step = 359; // input

    std::list<uint> state = {0};
    auto it = state.begin();

    for (uint i = 1; i <= 2017; i++) {
        for (uint j = 0; j < step % state.size(); j++) {
            it++;
            if (it == state.end())
                it = state.begin();
        }

        it = state.insert(++it, i);
    }

    it = state.begin();
    while (it != state.end()) {
        if (*(it++) == 2017)
            break;
    }
    if (it == state.end())
        it = state.begin();

    cout << *it << endl;

    return 0;
}