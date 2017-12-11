#include <iostream>
#include <map>
#include <utility> 
#include "common.h"

using std::cout, std::endl;

int main() {
    uint input = 265149;

    std::map<std::pair<const int, const int>, uint> board;

    uint i = 1;
    board[spiral_coord(i)] = 1;
    while(true) {
        i++;
        auto coord = spiral_coord(i);
        auto[x, y] = coord;
        board[coord] = 
            + board[{x + 1, y + 0}]
            + board[{x + 1, y + 1}]
            + board[{x + 0, y + 1}]
            + board[{x - 1, y + 1}]
            + board[{x - 1, y + 0}]
            + board[{x - 1, y - 1}]
            + board[{x + 0, y - 1}]
            + board[{x + 1, y - 1}];

        if (board[coord] > input) {
            cout << board[coord] << endl;
            break;
        }
    }
    return 0;
}