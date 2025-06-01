#ifndef PIECES_H
#define PIECES_H
#include <iostream>
#include "../header/pieces.h"
#include <algorithm>
//we will take the top left corner as the current position of the piece

extern char pieces[7][4][4];
void rotate(char grid[4][4]);
#endif