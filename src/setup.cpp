#include "../header/setup.h"

void GameInit() {
    //start the game
    GameOver = false;
    //reset player score
    PlayerScore = 0;
    //every piece's upper left corner starts here
    x = 0;
    y = 3;
    //initialize the grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][i] = '.'; //blank
        }
    }
    //hide the cursor
    std::cout << "\x1b[?25l";
}