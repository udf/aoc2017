#include <iostream>
#include <string>
#include <vector>
#include <valarray>
#include <ctype.h>

bool is_walkable(const std::valarray<int> &pos, const std::vector<std::string> &matrix) {
    if (pos[0] < 0 || pos[0] >= (int)matrix.size())
        return false;
    if (pos[1] < 0 || pos[1] >= (int)matrix[pos[0]].size())
        return false;

    return matrix[pos[0]][pos[1]] != ' ';
}

template<typename T>
inline T mod(const T a, const T b) {
    return (b + (a % b)) % b;
}

int main() {
    using std::cout;
    using std::endl;

    // {y (line), x (character)}
    const std::valarray<int> directions[4] = {
        {0, 1}, // right
        {1, 0}, // down
        {0, -1}, // left
        {-1, 0} // up
    };
    int direction = 1; // down
    std::valarray<int> pos = {0, 0};

    // load input
    std::vector<std::string> matrix;
    std::string line;
    while(std::getline(std::cin, line)) {
        matrix.push_back(line);
    }

    // find entry point
    for (size_t i = 0; i < matrix[0].size(); i++) {
        if (matrix[0][i] != ' ') {
            pos[1] = i;
            break;
        }
    }

    // walk
    int steps = 0;
    std::string visited = "";
    while (true) {
        steps++;
        const char current = matrix[pos[0]][pos[1]];
        if (isalpha(current))
            visited += current;

        // try to go in our current direction
        if (is_walkable(pos + directions[direction], matrix)) {
            pos += directions[direction];
            continue;
        }

        // try to turn 90° clockwise
        direction = (direction + 1) % 4;
        if (is_walkable(pos + directions[direction], matrix)) {
            pos += directions[direction];
            continue;
        }

        // try to turn 180° (which is 90° anti-clockwise from the original direction)
        direction = mod(direction - 2, 4);
        if (is_walkable(pos + directions[direction], matrix)) {
            pos += directions[direction];
            continue;
        }

        break;
    }

    std::cout << visited << std::endl;
    std::cout << steps << " steps" << std::endl;

    return 0;
}