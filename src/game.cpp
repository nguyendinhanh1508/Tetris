#include "../header/game.h"

void SetDifficulty() {
    std::cout << "Please input your name: " << std::endl;
    std::getline(std::cin, PlayerName);
    std::cout << "Please choose a difficulty from 1 to 15 (set to 1 by default): " << std::endl;
    std::string inpt;
    std::getline(std::cin, inpt);
    if (inpt == "1") {
        SleepTime = 1000;
    }
    else if (inpt == "2") {
        SleepTime = 900;
    }
    else if (inpt == "3") {
        SleepTime = 800;
    }
    else if (inpt == "4") {
        SleepTime = 700;
    }
    else if (inpt == "5") {
        SleepTime = 600;
    }
    else if (inpt == "6") {
        SleepTime = 500;
    }
    else if (inpt == "7") {
        SleepTime = 450;
    }
    else if (inpt == "8") {
        SleepTime = 400;
    }
    else if (inpt == "9") {
        SleepTime = 350;
    }
    else if (inpt == "10") {
        SleepTime = 300;
    }
    else if (inpt == "11") {
        SleepTime = 250;
    }
    else if (inpt == "12") {
        SleepTime = 200;
    }
    else if (inpt == "13") {
        SleepTime = 150;
    }
    else if (inpt == "14") {
        SleepTime = 120;
    }
    else if (inpt == "15") {
        SleepTime = 100;
    }
    else {
        SleepTime = 400;
    }
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
            case 'D':
                CurKey = D;
                break;
        }
    }
}

bool HittingGround() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int nx = x + i;
            int ny = y + j;
            if(nx >= 0 && nx <= height && ny >= 0 && ny <= width) {
                if (CurPiece[i][j] == 'x' && grid[nx + 1][ny] == 'x') {
                    if (nx == height - 1 || grid[nx + 1][ny] == 'x') return true;
                }
            }
        }
    }
    return false;
}

bool DetectCollision(char NewPiece[4][4], int nx, int ny) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int nx = x + i;
            int ny = y + j;
            if(nx >= 0 && nx <= height && ny >= 0 && ny <= width) {
                if (CurPiece[i][j] == 'x' && grid[nx][ny] == 'x') return true;
            }
            else if (CurPiece[i][j] == 'x') return true;
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
    return DetectCollision(NewPiece, x, y);
}

bool CanMove(int change_x, int change_y) {
    int nx = x + change_x;
    int ny = y + change_y;
    return DetectCollision(CurPiece, nx, ny);
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
            if (CurPiece[i][j] == 'x' && nx >= 0 && nx < height && ny >= 0 && ny <= width) {
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
}

void UpdateGame() {
    if (HittingGround()) counter++;
    else counter = 0;
    if (counter == 3) {
        counter = 0;
        MovingPiece = false;
    }
    if (MovingPiece) {
        switch(CurKey) {
            case A:
                if (CanRotate()) {
                    rotate(CurPiece);
                }
                break;
            case W:
                if (CanMove(0, -1)) {
                    y--;
                }
                break;
            case S:
                if (CanMove(1, 0)) {
                    x++;
                }
                break;
            case D:
                if (CanMove(0, 1)) {
                    y++;
                }
                break;
        }
        if (CanMove(1, 0)) {
            x++;
        }
    }
    else {
        Imprint();
        CreateNew();
        MovingPiece = true;
    }
    DeleteFullRows();
}

void Game() {
    Render();
    PlayerInput();
    UpdateGame();
    Sleep(SleepTime);
    if (GameOver) {
        GameInit();
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
            std::cout << "Tetris in Terminal\n";
            std::cout << "© 2025 Nguyen Dinh Anh\n";
            std::cout << "Exit the game?(y/n)\n";
            std::cin >> answer;
            if (answer == 'y') {
                exit(1);
            }
        }
    }
}