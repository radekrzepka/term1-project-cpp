#include <iostream>
#include <conio.h>
#include "menu.hpp"
#include "gameRules.hpp"
#include "functions.hpp"

#define ESC 27

using namespace std;

void gameRules () {
    system("cls");

    unsigned char key;
    printBigString("Zasady gry");
    cout << endl << "Saper jest grą logiczną, ktora powstała w 1981 roku." << endl;
    cout << "Gra polega na odkrywaniu na planszy poszczególnych pol w taki sposób, aby nie natrafić na minę." << endl;
    cout << "Na każdym z odkrytych pól napisana jest liczba min, " << endl;
    cout << "które bezpośrednio stykają sie z danym polem (od jeden do ośmiu; jeśli min jest zero to na polu nie ma wpisanej liczby)." << endl;
    cout << "Na każdym z odkrytych pól napisana jest liczba min." << endl;
    cout << "Nalezy uzywać tych liczb by wydedukować gdzie schowane są miny." << endl;
    cout << "Każde pole można również oflagować, aby oznaczyć sobie gdzie może znajdować się potencjalnie mina." << endl << endl;

    printBigString("Instrukcja gry");
    cout << endl << "Strzałki - zmiana akutalnie wybranego pola" << endl;
    cout << "Q - sprawdzenie akutalnie wybranego pola" << endl;
    cout << "W - oflagowanie akutalnie wybranego pola" << endl << endl;

    cout << "ESC - wróć do menu";

    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}