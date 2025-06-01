#include "../header/game.h"

void SetDifficulty() {
    std::cout << "Welcome to \033[31mT\033[38;5;202mE\033[33mT\033[32mR\033[36mI\033[35mS\033[0m in the terminal\n";
    std::cout << "Please input your name: " << std::endl;
    std::getline(std::cin, PlayerName);
    std::cout << "Please choose a difficulty from 1 to 15 (set to 1 by default): " << std::endl;
    std::string inpt;
    std::getline(std::cin, inpt);
    if (inpt == "1") {
        SleepTime = 20;
    }
    else if (inpt == "2") {
        SleepTime = 18;
    }
    else if (inpt == "3") {
        SleepTime = 16;
    }
    else if (inpt == "4") {
        SleepTime = 14;
    }
    else if (inpt == "5") {
        SleepTime = 12;
    }
    else if (inpt == "6") {
        SleepTime = 10;
    }
    else if (inpt == "7") {
        SleepTime = 9;
    }
    else if (inpt == "8") {
        SleepTime = 8;
    }
    else if (inpt == "9") {
        SleepTime = 7;
    }
    else if (inpt == "10") {
        SleepTime = 6;
    }
    else if (inpt == "11") {
        SleepTime = 5;
    }
    else if (inpt == "12") {
        SleepTime = 4;
    }
    else if (inpt == "13") {
        SleepTime = 3;
    }
    else if (inpt == "14") {
        SleepTime = 2;
    }
    else if (inpt == "15") {
        SleepTime = 1;
    }
    else {
        SleepTime = 20;
    }
    system("cls");
}

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
            case 'd':
                CurKey = D;
                break;
        }
    }
}

bool HittingGround() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (CurPiece[i][j] == 'x') {
                int pieceBottom = x + i;
                int pieceCol = y + j;
                if (pieceBottom == height - 1) {
                    return true;
                }
                if (pieceBottom >= 0 && pieceBottom + 1 < height - 1 && pieceCol >= 0 && pieceCol < width) {
                    if (grid[pieceBottom + 1][pieceCol] == 'x') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool DetectCollision(char NewPiece[4][4], int nx, int ny) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (NewPiece[i][j] == 'x') {
                int cx = nx + i;
                int cy = ny + j;
                if (cy < 0 || cy >= width) {
                    return true;
                }
                if (cx >= height) {
                    return true;
                }
                if (cx >= 0 && grid[cx][cy] == 'x') {
                    return true;
                }
            }
        }
    }
    return false;
}

bool CanRotate() {
    char NewPiece[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            NewPiece[i][j] = CurPiece[i][j];
        }
    }
    rotate(NewPiece);
    return !DetectCollision(NewPiece, x, y);
}

bool CanMove(int change_x, int change_y) {
    int nx = x + change_x;
    int ny = y + change_y;
    return !DetectCollision(CurPiece, nx, ny);
}

#include <random>
#include <chrono>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y) {
	return rng() % (y - x + 1) + x;
}

Color random_color() {
	int random_value = rnd(0, 5);
    switch (random_value) { 
        case 0:
            return RED;
        case 1:
            return GREEN;
        case 2:
            return YELLOW;
        case 3:
            return BLUE;
        case 4:
            return MAGENTA;
        case 5:
            return CYAN;
        default:
            return BLUE;
    }
}

void CreateNew() {
    CurColor = random_color();
    int NewPiece_idx = rnd(0, 6);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){ 
            CurPiece[i][j] = pieces[NewPiece_idx][i][j];
        }
    }
    x = 0;
    y = 3;
}

void Imprint() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int nx = x + i;
            int ny = y + j;
            if (CurPiece[i][j] == 'x' && nx >= 0 && nx < height && ny >= 0 && ny < width) {
                grid[nx][ny] = 'x';
            }
        }
    }
}

void DeleteFullRows() {
    std::unordered_set<int> full;
    for (int i = 0; i < height; i++) {
        int filled = 0;
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == 'x') filled++;
        }
        if (filled == width) full.insert(i);
    }
    char newgrid[height][width];
    int nx = height - 1;
    for (int i = height - 1; i >= 0; i--) {
        if (full.find(i) != full.end()) continue;
        for (int j = 0; j < width; j++) {
            newgrid[nx][j] = grid[i][j];
        }
        nx--;
    }
    for (int i = nx; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            newgrid[i][j] = '.';
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = newgrid[i][j];
        }
    }
    PlayerScore += full.size() * 1000;
}

bool GameOverCheck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (CurPiece[i][j] == 'x') {
                int gridX = 0 + i;
                int gridY = 3 + j;
                if (gridX >= 0 && gridX < height && gridY >= 0 && gridY < width) {
                    if (grid[gridX][gridY] == 'x') {
                        return true;
                    }
                }
                else if (gridX < 0 || gridY < 0 || gridY >= width) {
                    return true;
                }
            }
        }
    }
    return false;
}

void UpdateGame() {
    if (HittingGround()) counter++;
    else counter = 0;
    if (counter >= 30) {
        counter = 0;
        MovingPiece = false;
        PlayerScore += 100;
    }
    if (MovingPiece) {
        switch(CurKey) {
            case W:
                if (CanRotate()) {
                    rotate(CurPiece);
                }
                if (HittingGround()) counter++;
                break;
            case A:
                if (CanMove(0, -1)) {
                    y--;
                }
                if (HittingGround()) counter++;
                break;
            case S:
                while (CanMove(1, 0)) {
                    x++;
                }
                counter = 0;
                MovingPiece = false;
                PlayerScore += 100;
                Imprint();
                DeleteFullRows();
                CreateNew();
                if (GameOverCheck()) {
                    GameOver = true;
                    return;
                }
                MovingPiece = true;
                if (HittingGround()) counter++;
                break;
            case D:
                if (CanMove(0, 1)) {
                    y++;
                }
                if (HittingGround()) counter++;
                break;
            default:
                if (HittingGround()) counter++;
                break;
        }
        CurKey = NONE;
        if (GameTime % SleepTime == 0 && CanMove(1, 0)) {
            x++;
        }
    }
    else {
        Imprint();
        DeleteFullRows();
        CreateNew();
        if (GameOverCheck()) {
            GameOver = true;
            return;
        }
        MovingPiece = true;
    }
}

void Game() {
    GameTime++;
    Render();
    PlayerInput();
    UpdateGame();
    if (GameOver) {
        HighScore = std::max(HighScore, PlayerScore);
        Render();
        Sleep(1000);
        std::cout << std::endl;
        std::cout << "Game Over, Play Again?(y/n): ";
        char answer;
        std::cin >> answer;
        if (answer == 'y') {
            SetDifficulty();
        }
        else {
            system("cls");
            std::cout << "Thank you for playing my game!\n";
            Sleep(1000);
            std::cout << "And this is \033[31mT\033[38;5;202mE\033[33mT\033[32mR\033[36mI\033[35mS\033[0m in the terminal\n";
            Sleep(1000);
            std::cout << "Made by Nguyen Dinh Anh\n";
            Sleep(1000);
            std::cout << "Exit the game?";
            std::cin >> answer;
        }
    }
    else {
        Sleep(50);
    }
}