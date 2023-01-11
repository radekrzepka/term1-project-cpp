#include <iostream>
#include <conio.h>
#include <windows.h>
#include "game.hpp"

#define GREEN_CONSOLE_COLOR 2
#define WHITE_CONSOLE_COLOR 15
#define UP_ARROW 72
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define LEFT_ARROW 75

using namespace std;

enum class State {clicked, flagged, notClicked};

struct Field {
    State state = State::notClicked;
    unsigned short int howManyBombsNear = 0;
	bool hasBomb = false;
	bool isRevaled = false;
};

struct MoveCords {
    unsigned short int rowCords = 0;
    unsigned short int colCords = 0;
};

void printBoard (Field **board, unsigned short int boardWidth, unsigned short int boardHeight, MoveCords userMove) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            if(i == userMove.rowCords && j == userMove.colCords) {
                SetConsoleTextAttribute(hConsole, GREEN_CONSOLE_COLOR);
                cout << "x";
                SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
            } else cout << board[i][j].isRevaled;
            cout << " ";
        }
        cout << endl;
    }
}

void game (unsigned short int boardWidth, unsigned short int boardHeight, unsigned short int mineQuantity) {
    system("cls");
    
    Field **board = new Field*[boardHeight];
    MoveCords userMove;

    for (int i = 0; i < boardHeight; i++) {
        board[i] = new Field[boardWidth];
    }

    printBoard(board,boardWidth,boardHeight,userMove);

    unsigned char key;
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

            if (keyClicked)  {
                system("cls");
                printBoard(board,boardWidth,boardHeight,userMove);
            }
        }
    } while (true);

    for (int i = 0; i < boardHeight; i++) delete[] board[i];
    delete[] board;
}