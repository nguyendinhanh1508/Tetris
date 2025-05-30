#include "../header/pieces.h"

void rotate(char grid[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            std::swap(grid[i][j], grid[j][i]);
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::swap(grid[i][j], grid[i][3 - j]);
        }
    }
}