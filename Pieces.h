#ifndef PIECES_H
#define PIECES_H

class Pieces {
public:
    int GetBlockType(int pPiece, int pRotation, int pX, int pY);
    int GetXInitialPosition(int pPiece, int pRotation);
    int GetYInitialPosition(int pPiece, int pRotation);
};
#endif