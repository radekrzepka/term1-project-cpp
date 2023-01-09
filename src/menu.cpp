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
#define UP_ARROW 80
#define DOWN_ARROW 72
#define ESC 27
#define ENTER '\r'

using namespace std;

int activeOption = 0;
string menuOptions[6] = {"Poczatkujacy (8x8, 10 min)", "Niestandardowy (16x16, 40 min)", "Zaawansowany (30x16, 99 min)", "Niestandardowy", "Zasady gry i instrukcja", "Ranking"};
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
}

void menu () {
    system("cls");
    showMenu();
    unsigned char key;

    do {
        while(kbhit()) {
            key = getch();

            if (key == UP_ARROW) activeOption++;
            if (key == DOWN_ARROW) activeOption--;
            if (key == ENTER) {
                switch (activeOption) {
                    case 0:
                        game(8,8,10);
                    break;
                    case 1:
                        game(16,16,40);
                    break;
                    case 2:
                        game(30,16,99);
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
            if (activeOption == numberOfOptions) activeOption--;
            if (activeOption == -1) activeOption++;

            if (key == UP_ARROW || key == DOWN_ARROW) {
                system("cls");
                showMenu();
            }
        }
    } while (key != ESC);
}