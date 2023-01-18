#include <iostream>
#include <windows.h>

#include "customSettings.hpp"
#include "game.hpp"
#include "functions.hpp"

#define MAX_BOARD_WIDTH 40
#define MIN_BOARD_WIDTH 8
#define MAX_BOARD_HEIGHT 18
#define MIN_BOARD_HEIGHT 8
#define RED_CONSOLE_COLOR 4
#define WHITE_CONSOLE_COLOR 15

using namespace std;

struct GameSettings
{
    string boardWidth;
    string boardHeight;
    string minesQunatity;
};

//check if input given by user is valid number
bool isNumber (string str) {
    for(int i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

//check if all inputs given by user is valid number
bool allNumbersInt (GameSettings gameSettings) {
    if (isNumber(gameSettings.boardWidth) && isNumber(gameSettings.boardHeight) && isNumber(gameSettings.minesQunatity)) return true;
    return false;
}

//check if board size is right
bool rightSize (GameSettings gameSettings) {
    if (stoi(gameSettings.boardWidth) <= MAX_BOARD_WIDTH && stoi(gameSettings.boardHeight) <= MAX_BOARD_HEIGHT && stoi(gameSettings.boardWidth) >= MIN_BOARD_WIDTH && stoi(gameSettings.boardHeight) >= MIN_BOARD_HEIGHT) return false;
    return true;
}

//checks if the user has given too many bombs
bool tooManyBombs (GameSettings gameSettings) {
    int maxBombsQuantity = (stoi(gameSettings.boardHeight) * stoi(gameSettings.boardWidth)) / 3;
    if (stoi(gameSettings.minesQunatity) > maxBombsQuantity || stoi(gameSettings.minesQunatity) == 0) return true;
    return false;
}

//check all conditions for validate data
bool validateData (GameSettings gameSettings) {
    if (allNumbersInt(gameSettings) && !rightSize(gameSettings) && !tooManyBombs(gameSettings)) return true;
    return false;
}

//if data is incorrect, function will return message of error
string errorCode (GameSettings gameSettings) {
    if (!allNumbersInt(gameSettings)) return "Proszę wpisać same liczby";
    if (rightSize(gameSettings)) return "Maksymalny rozmiar planszy to: " + to_string(MAX_BOARD_WIDTH) + " x " + to_string(MAX_BOARD_HEIGHT) + ", a minimalny: " + to_string(MIN_BOARD_WIDTH) + " x " + to_string(MIN_BOARD_HEIGHT);
    if (tooManyBombs(gameSettings)) return "Podaj odpowiednią ilość bomb (maksymalnie (szerokość planszy x wysokość planszy) / 3, minimalnie 1)";
    return "";
}

//function is responsible for collect data from the user, as long as the data is not correct, and then start a game with custom settings 
void customSettings () {
    system("cls");
    clearConsole();
    printf("\e[?25h");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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