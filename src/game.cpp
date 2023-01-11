#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <random>
#include "game.hpp"

#define GREEN_CONSOLE_COLOR 2
#define WHITE_CONSOLE_COLOR 15
#define BLUE_CONSOLE_COLOR 1
#define RED_CONSOLE_COLOR 4
#define PURPLE_CONSOLE_COLOR 5
#define YELLOW_CONSOLE_COLOR 6

#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75
#define Q_KEY 113
#define W_KEY 119

#define LEFT_UP_BOX "╔"
#define RIGHT_UP_BOX "╗"
#define LEFT_DOWN_BOX "╚"
#define RIGHT_DOWN_BOX "╝"
#define LEFT_CONNECTING_BOX "╠"
#define RIGHT_CONNECTING_BOX "╣"
#define HORIZONTAL_BOX "═"
#define VERTICAL_BOX "║"

using namespace std;

enum class State {clicked, flagged, notClicked};

struct Field {
    State state = State::notClicked;
    int howManyBombsNear = 0;
	bool hasBomb = false;
	bool isRevaled = false;
};

struct MoveCords {
    int rowCords = 0;
    int colCords = 0;
};

void printBoard (Field **board, int boardWidth, int boardHeight, MoveCords userMove) {
    system("cls");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << LEFT_UP_BOX;
    for (int i = 0; i < boardWidth * 2 + 1; i++) cout << HORIZONTAL_BOX;
    cout << RIGHT_UP_BOX << endl;

    for (int i = 0; i < boardHeight; i++) {
        
        for (int j = 0; j < boardWidth; j++) {
            if (j == 0) cout << VERTICAL_BOX;
            cout << " ";

            if(i == userMove.rowCords && j == userMove.colCords) {
                SetConsoleTextAttribute(hConsole, YELLOW_CONSOLE_COLOR);
                cout << "x";
                SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
            } else {
                if (board[i][j].hasBomb) cout << "B";
                else if (board[i][j].howManyBombsNear != 0) {
                    switch(board[i][j].howManyBombsNear) {
                        case 1:
                            SetConsoleTextAttribute(hConsole, BLUE_CONSOLE_COLOR);
                        break;
                        case 2:
                            SetConsoleTextAttribute(hConsole, GREEN_CONSOLE_COLOR);
                        break;
                        case 3:
                            SetConsoleTextAttribute(hConsole, RED_CONSOLE_COLOR);
                        break;
                        default:
                            SetConsoleTextAttribute(hConsole, PURPLE_CONSOLE_COLOR);                                             
                    }
                    cout << board[i][j].howManyBombsNear;
                    SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
                }
                else cout << "█";
            }

            if (j == boardWidth - 1) cout << " " << VERTICAL_BOX;
        }

        cout << endl << (i != boardHeight - 1 ? LEFT_CONNECTING_BOX : LEFT_DOWN_BOX);
        for (int k = 0; k < boardWidth * 2 + 1; k++) cout << HORIZONTAL_BOX;
        cout << (i != boardHeight - 1 ? RIGHT_CONNECTING_BOX : RIGHT_DOWN_BOX) << endl;
    }

    printf("\e[?25l"); 
}

int generateRandomCord(int maxSize) {
	random_device rd;
	mt19937 generatorRandomCord(rd());
	uniform_int_distribution<int> distributionRandomCord(0, maxSize);
	return distributionRandomCord(generatorRandomCord);
}

void generateBomb(Field **board, int boardWidth, int boardHeight, int mineQuantity, MoveCords firstMove) {
    int generatedBomb = 0;
    while (generatedBomb != mineQuantity) {
        MoveCords randomCords;
        randomCords.rowCords = generateRandomCord(boardHeight - 1);
        randomCords.colCords = generateRandomCord(boardWidth - 1);

        if ((randomCords.rowCords != firstMove.rowCords) && (randomCords.colCords != firstMove.colCords) && !board[randomCords.rowCords][randomCords.colCords].hasBomb) {
            board[randomCords.rowCords][randomCords.colCords].hasBomb = true;
            generatedBomb++;
        }
    }
}

bool correctCords (int rowCords, int colCords, int boardWidth, int boardHeight) {
    if (rowCords >= 0 && rowCords < boardHeight && colCords >= 0 && colCords < boardWidth) return true;
    else return false;
}

int countBombs(int rowCords, int colCords, Field** board, int boardWidth, int boardHeight) {
    int bombsQuantity = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (correctCords(i + rowCords,j + colCords,boardWidth,boardHeight) && (i != 0 || j != 0) && board[rowCords + i][colCords + j].hasBomb) bombsQuantity++;
        }
    }
    return bombsQuantity;
}

void generateNumbers(Field **board, int boardWidth, int boardHeight, int mineQuantity) {
    for(int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            if (!board[i][j].hasBomb) {
                int bombs = countBombs(i,j, board, boardWidth, boardHeight);
                board[i][j].howManyBombsNear = bombs;
            }
        }
    }
}

void game (int boardWidth, int boardHeight, int mineQuantity) {
    system("cls");
    
    Field **board = new Field*[boardHeight];
    MoveCords userMove;
    bool firstReval = false;

    for (int i = 0; i < boardHeight; i++) {
        board[i] = new Field[boardWidth];
    }

    printBoard(board,boardWidth,boardHeight,userMove);

    char key;
    do {
        while(kbhit()) {
            key = getch();
            bool keyClicked = false;

            if(key == UP_ARROW && userMove.rowCords != 0) {
                userMove.rowCords--;
                keyClicked = true;
            }
            if(key == DOWN_ARROW && userMove.rowCords != boardHeight - 1) {
                userMove.rowCords++;
                keyClicked = true;
            }
            if(key == LEFT_ARROW && userMove.colCords != 0) {
                userMove.colCords--;
                keyClicked = true;
            }
            if(key == RIGHT_ARROW && userMove.colCords != boardWidth - 1) {
                userMove.colCords++;
                keyClicked = true;
            }

            if (keyClicked) printBoard(board,boardWidth,boardHeight,userMove);
            
            if(key == Q_KEY) {
                if(!firstReval) {
                    firstReval = true;
                    generateBomb(board, boardWidth, boardHeight, mineQuantity, userMove);
                    generateNumbers(board, boardWidth, boardHeight, mineQuantity);  
                    printBoard(board,boardWidth,boardHeight,userMove);
                }
            }
            if(key == W_KEY) cout << "W";
        }
    } while (true);

    for (int i = 0; i < boardHeight; i++) delete[] board[i];
    delete[] board;
}