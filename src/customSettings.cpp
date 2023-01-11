#include <iostream>
#include "customSettings.hpp"
#include "game.hpp"

#define MAX_BOARD_SIZE 50

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
    if (stoi(gameSettings.boardWidth) <= MAX_BOARD_SIZE && stoi(gameSettings.boardHeight) <= MAX_BOARD_SIZE) return false;
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
    if (boardToBig(gameSettings)) return "Maksymalny rozmiar planszy to: " + to_string(MAX_BOARD_SIZE) + " x " + to_string(MAX_BOARD_SIZE);
    if (tooManyBombs(gameSettings)) return "Podaj odpowiednią ilość bomb";
}

void customSettings () {
    system("cls");
    printf("\e[?25h");
    
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
            cout << errorCode(gameSettings) << endl;
        }

    } while (!isDataVaild);

    game(stoi(gameSettings.boardWidth), stoi(gameSettings.boardHeight), stoi(gameSettings.minesQunatity));
}