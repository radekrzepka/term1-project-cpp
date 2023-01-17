#include <iostream>
#include <windows.h>

#include "functions.hpp"

#define LEFT_UP_BOX "╔"
#define RIGHT_UP_BOX "╗"
#define LEFT_DOWN_BOX "╚"
#define RIGHT_DOWN_BOX "╝"
#define HORIZONTAL_BOX "═"
#define VERTICAL_BOX "║"

using namespace std;

void printBigString (string text, int additionalSpace) {
    if(additionalSpace % 2 == 1) additionalSpace--;

    cout << LEFT_UP_BOX;
    for(int i = 0; i < text.length() + additionalSpace; i++) cout << HORIZONTAL_BOX;
    cout << RIGHT_UP_BOX << endl;
    cout << VERTICAL_BOX;
    for(int i = 0; i < additionalSpace / 2; i++) cout << " ";
    cout << text;
    for(int i = 0; i < additionalSpace / 2; i++) cout << " ";
    cout << VERTICAL_BOX << endl;
    cout << LEFT_DOWN_BOX;
    for(int i = 0; i < text.length() + additionalSpace ; i++) cout << HORIZONTAL_BOX;
    cout << RIGHT_DOWN_BOX << endl;
}

void clearConsole () {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
