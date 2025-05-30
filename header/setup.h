#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <string>

//piece Data
enum Color { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN };
char CurPiece[4][4];
int x, y;
Color CurColor;

//game data
const int width = 10;
const int height = 24;
char grid[height][width];
int GameOver = false;
int PlayerScore = 0;
enum KeyPressed {A, W, S, D};
KeyPressed CurKey;
double SleepTime = 50; //fps = 1000/50 fyi
bool MovingPiece = false;

//player data
std::string PlayerName;
int PlayerScore = 0;
int HighScore = 0;

//init the game
void GameInit();

#endif