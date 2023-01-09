#include <iostream>
#include <conio.h>
#include "menu.hpp"

#define ESC 27

using namespace std;

void ranking () {
    system("cls");

    unsigned char key;
    cout << "Ranking 123" << endl;
    cout << "ESC - powrot do menu";

    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}