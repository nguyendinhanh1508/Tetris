#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "render.h";
#include "../header/setup.h";
#include "../header/pieces.h";
#include <unordered_set>

void SetDifficulty();
void PlayerInput();
bool HittingGround();
bool DetectCollision(char NewPiece[4][4], int nx, int ny);
bool CanRotate();
bool CanMove(int change_x, int change_y);
void CreateNew();
void Imprint();
void UpdateGame();
void Game();

#endif