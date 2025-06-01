#include "../header/render.h"

bool isPiece(int i, int j) {
    if (i >= x && i < x + 4 && j >= y && j < y + 4) {
        return CurPiece[i-x][j-y] == 'x';
    }
    return false;
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
    std::cout << "    TERMINAL \033[31mT\033[38;5;202mE\033[33mT\033[32mR\033[36mI\033[35mS\033[0m\n";
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
            else {
                if (grid[i][j] == 'x') {
                    std::cout << "\033[100m  \033[0m";
                }
                else {
                    std::cout << "  ";
                }
            }
        }
        std::cout << "\033[47m  \033[0m";
        std::cout << std::endl;
    }
    std::cout << PlayerName << "'s Score: " << PlayerScore << '\n';
    std::cout << "High Score: " << HighScore;
}