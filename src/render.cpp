#include "../header/render.h"

bool isPiece(int i, int j) {
    int left = y;
    int right = y + 3;
    int top = x;
    int bottom = x + 3;
    if (j >= left && j <= right && i >= top && i <= bottom) {//check if it's inside
        return true;
    }
    else {
        return false;
    }
}

void PrintColor(Color color) {
    switch (color){
        case RED:
            std::cout << "\033[41m  \033[0m";
            break;
        case GREEN:
            std::cout << "\033[42m  \033[0m";
            break;
        case YELLOW:
            std::cout << "\033[43m  \033[0m";
            break;
        case BLUE:
            std::cout << "\033[44m  \033[0m";
            break;
        case MAGENTA:
            std::cout << "\033[45m  \033[0m";
            break;
        case CYAN:
            std::cout << "\033[46m  \033[0m";
            break; 
    }
}

void Render() {
    std::cout << "\033[H"; //clear the entire screen(not really)
    //this is better than system("cls")
    //because it moves the pointer to the top left and print over what's rendered
    //hence it will stop the flickering
    //there will be some delay at the bottom part of the screen but this one's a small grid so it's not noticeable
    for (int i = 0; i < height; i++) {
        std::cout << "\033[47m  \033[0m";
        for (int j = 0; j < width; j++) {
            if (isPiece(i, j)) {
                int piece_x = i - x;
                int piece_y = j - y;
                if(CurPiece[piece_x][piece_y] == '.') {
                    std::cout << "  ";
                }
                else {
                    PrintColor(CurColor);
                }
            }
        }
        std::cout << "\033[47m  \033[0m";
    }
    std::cout << PlayerName << "'s Score: " << PlayerScore << '\n';
    std::cout << "High Score: " << HighScore;
}