#ifndef SETUP_H
#define SETUP_H
#include <iostream>
#include <string>

//piece Data
enum Color { RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN };
extern char CurPiece[4][4];
extern int x, y;
extern Color CurColor;

//game data
const int width = 10;
const int height = 24;
extern char grid[height][width];
extern bool GameOver;
enum KeyPressed {A, W, S, D, NONE};
extern KeyPressed CurKey;
extern int SleepTime;
extern bool MovingPiece;
extern int counter;
extern int GameTime;

//player data
extern std::string PlayerName;
extern int PlayerScore;
extern int HighScore;

//init the game
void GameInit();

#endif