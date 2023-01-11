#include <iostream>
#include <windows.h>
#include "customSettings.hpp"
#include "game.hpp"
#include "functions.hpp"

#define MAX_BOARD_WIDTH 40
#define MAX_BOARD_HEIGHT 18
#define RED_CONSOLE_COLOR 4
#define WHITE_CONSOLE_COLOR 15

using namespace std;

struct GameSettings
{
    string boardWidth;
    string boardHeight;
    string minesQunatity;
};

bool isNumber (string str) {
    for(int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool allNumbersInt (GameSettings gameSettings) {
    if (isNumber(gameSettings.boardWidth) && isNumber(gameSettings.boardHeight) && isNumber(gameSettings.minesQunatity)) return true;
    return false;
}

bool boardToBig (GameSettings gameSettings) {
    if (stoi(gameSettings.boardWidth) <= MAX_BOARD_WIDTH && stoi(gameSettings.boardHeight) <= MAX_BOARD_HEIGHT) return false;
    return true;
}

bool tooManyBombs (GameSettings gameSettings) {
    int maxBombsQuantity = (stoi(gameSettings.boardHeight) * stoi(gameSettings.boardWidth)) - 2;
    if (stoi(gameSettings.minesQunatity) > maxBombsQuantity) return true;
    return false;
}

bool validateData (GameSettings gameSettings) {
    if (allNumbersInt(gameSettings) && !boardToBig(gameSettings) && !tooManyBombs(gameSettings)) return true;
    return false;
}

string errorCode (GameSettings gameSettings) {
    if (!allNumbersInt(gameSettings)) return "Proszę wpisać same liczby";
    if (boardToBig(gameSettings)) return "Maksymalny rozmiar planszy to: " + to_string(MAX_BOARD_WIDTH) + " x " + to_string(MAX_BOARD_HEIGHT);
    if (tooManyBombs(gameSettings)) return "Podaj odpowiednią ilość bomb";
    return "";
}

void customSettings () {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    printf("\e[?25h");
    printBigString("Niestandardowe ustawienia gry");
    
    bool isDataVaild = false;
    GameSettings gameSettings;

    do {
        cout << "Podaj szerokość planszy: ";
        cin >> gameSettings.boardWidth;
        cout << "Podaj wysokość planszy: ";
        cin >> gameSettings.boardHeight;
        cout << "Podaj ilość min: ";
        cin >> gameSettings.minesQunatity;

        if(validateData(gameSettings)) isDataVaild = true;
        else {
            system("cls");
            printBigString("Niestandardowe ustawienia gry");
            SetConsoleTextAttribute(hConsole, RED_CONSOLE_COLOR);
            cout << errorCode(gameSettings) << endl;
            SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
        }

    } while (!isDataVaild);

    game(stoi(gameSettings.boardWidth), stoi(gameSettings.boardHeight), stoi(gameSettings.minesQunatity));
}