#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <random>
#include <chrono>
#include <fstream>

#include "ranking.hpp"
#include "menu.hpp"
#include "game.hpp"
#include "functions.hpp"

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
#define ESC 27

#define LEFT_UP_BOX "╔"
#define RIGHT_UP_BOX "╗"
#define LEFT_DOWN_BOX "╚"
#define RIGHT_DOWN_BOX "╝"
#define LEFT_CONNECTING_BOX "╠"
#define RIGHT_CONNECTING_BOX "╣"
#define HORIZONTAL_BOX "═"
#define VERTICAL_BOX "║"

using namespace std;

struct Field {
    int howManyBombsNear = 0;
	bool hasBomb = false;
	bool isRevaled = false;
    bool isFlagged = false;
};

struct MoveCords {
    int rowCords = 0;
    int colCords = 0;
};

//function is responsible for printing the board
void printBoard (Field **board, int boardWidth, int boardHeight, MoveCords userMove, int howManyFlagged, int mineQuantity) {
    clearConsole();
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "Oflagowano: " << howManyFlagged << "/" << mineQuantity << endl;

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
                if (board[i][j].isRevaled) {
                    if (board[i][j].howManyBombsNear != 0) {
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
                    } else cout << " ";
                } else if (board[i][j].isFlagged) cout << "F";
                else cout << "█";
            }
            if (j == boardWidth - 1) cout << " " << VERTICAL_BOX;
        }

        cout << endl << (i != boardHeight - 1 ? LEFT_CONNECTING_BOX : LEFT_DOWN_BOX);
        for (int k = 0; k < boardWidth * 2 + 1; k++) cout << HORIZONTAL_BOX;
        cout << (i != boardHeight - 1 ? RIGHT_CONNECTING_BOX : RIGHT_DOWN_BOX) << endl;
    }

    printf("\e[?25l");
    cout << endl << endl;
}

//function checks that the entered cords don't go outside the array
bool correctCords (int rowCords, int colCords, int boardWidth, int boardHeight) {
    if (rowCords >= 0 && rowCords < boardHeight && colCords >= 0 && colCords < boardWidth) return true;
    else return false;
}

//function for genereting random Cord
int generateRandomCord (int maxCord) {
	random_device rd;
	mt19937 generatorRandomCord(rd());
	uniform_int_distribution<int> distributionRandomCord(0, maxCord);
	return distributionRandomCord(generatorRandomCord);
}

//function which generete bombs on the board after first reveal
void generateBomb (Field **board, int boardWidth, int boardHeight, int mineQuantity, MoveCords firstMove) {
    int generatedBomb = 0;

    while (generatedBomb != mineQuantity) {
        bool closeToFirstMove = false;
        MoveCords randomCords{generateRandomCord(boardHeight - 1), generateRandomCord(boardWidth - 1)};

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if(correctCords(randomCords.rowCords + i,randomCords.colCords + j,boardWidth,boardHeight) && randomCords.rowCords + i == firstMove.rowCords && randomCords.colCords + j == firstMove.colCords) closeToFirstMove = true;
            }
        }

        if (!closeToFirstMove && !board[randomCords.rowCords][randomCords.colCords].hasBomb) {
            board[randomCords.rowCords][randomCords.colCords].hasBomb = true;
            generatedBomb++;
        }
    }
}

//function count how many bombs are across specific field
int countBombsNextToField (int rowCords, int colCords, Field** board, int boardWidth, int boardHeight) {
    int bombsQuantity = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (correctCords(i + rowCords,j + colCords,boardWidth,boardHeight) && (i != 0 || j != 0) && board[rowCords + i][colCords + j].hasBomb) bombsQuantity++;
        }
    }
    return bombsQuantity;
}

//function generate number of bombs next to every field 
void generateNumbers (Field **board, int boardWidth, int boardHeight, int mineQuantity) {
    for(int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            if (!board[i][j].hasBomb) {
                int bombs = countBombsNextToField(i,j, board, boardWidth, boardHeight);
                board[i][j].howManyBombsNear = bombs;
            }
        }
    }
}

//function that uses recursion to reveal the relevant fields after the user clicks on a field where there is no bomb
void revealFields (Field **board, int boardWidth, int boardHeight, MoveCords userMove) {
    if(board[userMove.rowCords][userMove.colCords].isRevaled) return;
    
    board[userMove.rowCords][userMove.colCords].isRevaled = true;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            MoveCords newCord{userMove.rowCords + i, userMove.colCords + j};
            
            if (correctCords(newCord.rowCords, newCord.colCords, boardWidth, boardHeight)) {
                if (board[newCord.rowCords][newCord.colCords].howManyBombsNear == 0 && !board[newCord.rowCords][newCord.colCords].hasBomb && !board[newCord.rowCords][newCord.colCords].isRevaled) {
                    revealFields(board, boardWidth, boardHeight, newCord); 
                }
                if (!board[newCord.rowCords][newCord.colCords].hasBomb) board[newCord.rowCords][newCord.colCords].isRevaled = true;
            }
        }
    }
}

//function which is responsible for flag or unflag field
void flagField (Field **board, MoveCords userMove) {
    if (board[userMove.rowCords][userMove.colCords].isFlagged) board[userMove.rowCords][userMove.colCords].isFlagged = false; 
    else if (!board[userMove.rowCords][userMove.colCords].isRevaled && !board[userMove.rowCords][userMove.colCords].isFlagged) board[userMove.rowCords][userMove.colCords].isFlagged = true; 
}

//function which count how many fields user has been flagged
int countFlags (Field **board, int boardWidth, int boardHeight) {
    int howManyFlags = 0;
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++ ) {
            if(board[i][j].isFlagged) howManyFlags++;
        }
    }
    return howManyFlags;
}

//function checks if every bomb is flagged and number of flags is the same as number of bombs
bool checkIfGameWon (Field **board, int boardWidth, int boardHeight, int mineQuantity, int howManyFlagged) {
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            if (board[i][j].hasBomb && !board[i][j].isFlagged) return false;
        }
    }
    if (howManyFlagged == mineQuantity) return true;
    return false;
}

//function returns the level of the map
string checkBoardLevel (int boardWidth, int boardHeight, int mineQuantity) {
    if (boardWidth == 8 && boardHeight == 8 && mineQuantity == 10) return "początkującym";
    else if (boardWidth == 16 && boardHeight == 16 && mineQuantity == 40) return "średnim";
    else if (boardWidth == 30 && boardHeight == 16 && mineQuantity == 99) return "zaawansowanym";
    return "niestandardowym";
}

void game (int boardWidth, int boardHeight, int mineQuantity) {
    system("cls");
    MoveCords userMove;
    auto start = chrono::high_resolution_clock::now(); //use to measure game time

    int howManyFlagged = 0;
    bool firstReveal = false;
    bool endGame = false;
    bool gameEscaped = false;
    bool gameWon = false;
    
    bool customLevel = ((checkBoardLevel(boardWidth, boardHeight, mineQuantity) == "niestandardowym") ? true : false);
    string boardLevel = checkBoardLevel(boardWidth, boardHeight, mineQuantity);

    Field **board = new Field*[boardHeight];
    for (int i = 0; i < boardHeight; i++) {
        board[i] = new Field[boardWidth];
    }

    printBoard(board,boardWidth,boardHeight,userMove, howManyFlagged, mineQuantity); //first print of board

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
            if(key == Q_KEY) {
                if(!firstReveal) { //bombs are generated after first click
                    firstReveal = true;
                    generateBomb(board, boardWidth, boardHeight, mineQuantity, userMove);
                    generateNumbers(board, boardWidth, boardHeight, mineQuantity);
                } 
                if (board[userMove.rowCords][userMove.colCords].hasBomb) endGame = true;
                revealFields(board, boardWidth, boardHeight, userMove);
                keyClicked = true;
            }
            if(key == W_KEY) {
                flagField(board, userMove);
                howManyFlagged = countFlags(board, boardWidth, boardHeight);
                if(checkIfGameWon(board, boardWidth, boardHeight, mineQuantity, howManyFlagged)) {
                    endGame = true;
                    gameWon = true;
                }
                keyClicked = true;
            }
            if(key == ESC) {
                endGame = true;
                gameEscaped = true;
            }
            if (keyClicked) printBoard(board,boardWidth,boardHeight,userMove,howManyFlagged,mineQuantity);
        }
    } while (!endGame);

    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    int time = elapsed.count();

    if (gameWon) {
        printBigString("Gratulacje wygrales", 12);
        cout << endl << endl << "Udało ci się wygrać na poziomie " << boardLevel << endl;
        cout << "Twój czas rozwiązywania to: " << time << " sekund";

        //if level is not custom allows you to add the result to the ranking
        if (!customLevel) {
            string name,level;
            bool correctName = false;
            printf("\e[?25h");

            while (!correctName) {
                cout << endl << "Podaj swój nick, aby zapisać twój wynik do rankigu (maksymalnie 20 znaków): ";
                cin >> name;
                if (name.length() >= 20) cout << "Twój nick może mieć maksymalnie 20 znaków długości";
                else correctName = true;
            }

            if (boardLevel == "początkującym") level = "1";
            else if (boardLevel == "średnim") level = "2";
            else level = "3";

            string line = "\n" + name + " " + to_string(time) + " " + level;

            ofstream file("ranking.txt", ios_base::app);
            file << line;
            file.close();
        } else {
            cout << endl << endl << "Naciśnij ESC aby wrócić do menu...";
            unsigned char key;
            do {
                while(kbhit()) {
                    key = getch();
                }
            } while (key != ESC);
        }

    } else if (!gameEscaped) {
        printBigString("Przegrales", 12);
        cout << endl << endl << "Naciśnij ESC aby wrócić do menu...";
        unsigned char key;
        do {
            while(kbhit()) {
                key = getch();
            }
        } while (key != ESC);
    }

    for (int i = 0; i < boardHeight; i++) delete[] board[i];
    delete[] board;

    if (!customLevel && gameWon) ranking();
    else menu();
}