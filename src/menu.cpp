#include <iostream>
#include <windows.h>
#include <conio.h>
#include "customSettings.hpp"
#include "game.hpp"
#include "gameRules.hpp"
#include "menu.hpp"
#include "ranking.hpp"

#define GREEN_CONSOLE_COLOR 2
#define WHITE_CONSOLE_COLOR 15
#define UP_ARROW 72
#define DOWN_ARROW 80
#define ESC 27
#define ENTER '\r'

#define EASY_BOARD_WIDTH 8
#define EASY_BOARD_HEIGHT 8
#define EASY_MINE_QUANTITY 10
#define MEDIUM_BOARD_WIDTH 16
#define MEDIUM_BOARD_HEIGHT 16
#define MEDIUM_MINE_QUANTITY 40
#define HARD_BOARD_WIDTH 30
#define HARD_BOARD_HEIGHT 16
#define HARD_MINE_QUANTITY 99

using namespace std;

int activeOption = 0;
string menuOptions[6] = {"Poczatkujący (8x8, 10 min)", "Średni (16x16, 40 min)", "Zaawansowany (30x16, 99 min)", "Niestandardowy", "Zasady gry i instrukcja", "Ranking"};
int numberOfOptions = sizeof(menuOptions)/sizeof(menuOptions[0]);

void showMenu () {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "SAPER" << endl;
    for (int i = 0; i < numberOfOptions; i++) {
        if (activeOption == i) SetConsoleTextAttribute(hConsole, GREEN_CONSOLE_COLOR);
        cout << i+1 << ". " << menuOptions[i] << endl;
        SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
    }
    printf("\e[?25l"); 
}

void menu () {
    system("cls");
    showMenu();
    
    unsigned char key;
    do {
        while(kbhit()) {
            key = getch();
            bool keyClicked = false;

            if (key == UP_ARROW && activeOption != 0) {
                activeOption--;
                keyClicked = true;
            }
            if (key == DOWN_ARROW && activeOption != numberOfOptions - 1) {
                activeOption++;
                keyClicked = true;
            }
            if (key == ENTER) {
                switch (activeOption) {
                    case 0:
                        game(EASY_BOARD_WIDTH,EASY_BOARD_HEIGHT,EASY_MINE_QUANTITY);
                    break;
                    case 1:
                        game(MEDIUM_BOARD_WIDTH,MEDIUM_BOARD_HEIGHT,MEDIUM_MINE_QUANTITY);
                    break;
                    case 2:
                        game(HARD_BOARD_WIDTH,HARD_BOARD_HEIGHT,HARD_MINE_QUANTITY);
                    break;
                    case 3:
                        customSettings();
                    break;
                    case 4:
                        gameRules();
                    break;
                    case 5:
                        ranking();
                    break;
                }
            }

            if (keyClicked) {
                system("cls");
                showMenu();
            }
        }
    } while (key != ESC);
}