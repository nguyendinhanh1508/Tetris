#include "../header/game.h"

void PlayerInput() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a':
                CurKey = A;
                break;
            case 'w':
                CurKey = W;
                break;
            case 's':
                CurKey = S;
                break;
            case 'D':
                CurKey = D;
                break;
        }
    }
}

void UpdateGame() {
    if (MovingPiece) {
        x++;
        switch(CurKey) {
            case A:
                rotate(CurPiece);
                break;
            case W:
                if (y != 0) {
                    y--;
                }
                break;
            case S:
                x++;
                break;
            case D:
                if (y != width - 1) {
                    y++;
                }
                break;
        }
    }
}

void Game() {
    Render();
    PlayerInput();
    UpdateGame();
    Sleep(SleepTime);
    
}