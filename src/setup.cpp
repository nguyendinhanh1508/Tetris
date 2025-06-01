#include "../header/setup.h"

char CurPiece[4][4];
int x, y;
Color CurColor;
char grid[height][width];
bool GameOver = false;
KeyPressed CurKey = NONE;
int SleepTime = 50;
bool MovingPiece = false;
int counter = 0;
std::string PlayerName;
int PlayerScore = 0;
int HighScore = 0;
int GameTime = 0;

void GameInit() {
    //start the game
    GameOver = false;
    //reset player score
    PlayerScore = 0;
    //reset the key pressed
    CurKey = NONE;
    //reset the game clock
    GameTime = 0;
    //every piece's upper left corner starts here
    x = 0;
    y = 3;
    //initialize the grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = '.'; //blank
        }
    }
    //hide the cursor
    std::cout << "\x1b[?25l";
    //set the counter to 0
    counter = 0;
}