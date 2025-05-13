#ifndef BOARD_H
#define BOARD_H
#include "Pieces.h"
const int BOARD_LINE_WIDTH = 6;
const int BLOCK_SIZE = 16;
const int BOARD_POSITION = 320;
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int MIN_VERTICAL_MARGIN = 20;
const int MIN_HORIZONTAL_MARGIN = 20;
const int PIECE_BLOCKS = 5;

class Board {
public:
    Board(Pieces* pPieces, int pScreenHeight);
    int GetXPosInPixels(int pPos);
    int GetYPosInPixels(int pPos);
    bool IsFreeBlock(int pX, int pY);
    bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation);
    void StorePiece(int pX, int pY, int pPiece, int pRotation);
    void DeletePossibleLines();
    bool IsGameOver();
private:
    enum { POS_FREE, POS_FILLED };
    int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
    Pieces* mPieces;
    int mScreenHeight;
    void InitBoard();
    void DeleteLine(int pY);
};
#endif