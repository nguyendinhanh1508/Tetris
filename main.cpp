#include <iostream>
#include <string>
#include "header/setup.h"
#include "header/game.h"

int main() {
    GameInit();
    SetDifficulty();
    while(!GameOver) {
        Game();
    }
    return 0;
}