#include <iostream>
#include <conio.h>
#include <windows.h>
#include "menu.hpp"
#include "gameRules.hpp"
#include "functions.hpp"

#define YELLOW_CONSOLE_COLOR 6
#define BLUE_CONSOLE_COLOR 1
#define WHITE_CONSOLE_COLOR 15
#define ESC 27

using namespace std;

void gameRules () {
    system("cls");
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    unsigned char key;
    printBigString("Zasady gry");
    cout << endl << "Saper jest grą logiczną, ktora powstała w 1981 roku." << endl;
    cout << "Gra polega na odkrywaniu na planszy poszczególnych pol w taki sposób, aby nie natrafić na minę." << endl;
    cout << "Na każdym z odkrytych pól napisana jest liczba min, " << endl;
    cout << "które bezpośrednio stykają sie z danym polem (od jeden do ośmiu; jeśli min jest zero to na polu nie ma wpisanej liczby)." << endl;
    cout << "Na każdym z odkrytych pól napisana jest liczba min." << endl;
    cout << "Należy używać tych liczb by wydedukować gdzie schowane są miny." << endl;
    cout << "Każde pole można również oflagować, aby oznaczyć sobie gdzie może znajdować się potencjalnie mina." << endl;
    cout << "Gra jest wygrana, gdy gracz poprawnie oflaguję każdą znajdującą się na mapie bombę." << endl << endl;

    printBigString("Instrukcja gry");
    cout << endl << "Strzałki - zmiana akutalnie wybranego pola" << endl;
    cout << "Q - sprawdzenie akutalnie wybranego pola" << endl;
    cout << "W - oflagowanie akutalnie wybranego pola" << endl << endl;

    
    printBigString("Oznaczenia");
    cout << endl;
    SetConsoleTextAttribute(hConsole, YELLOW_CONSOLE_COLOR);
    cout << "x";
    SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
    cout << " - akutalne położenie gracza" << endl;
    cout << "█ - nieodkryte pole" << endl;
    cout << "  - odkryte puste pole" << endl;
    cout << "F - oflagowana mina" << endl;
    SetConsoleTextAttribute(hConsole, BLUE_CONSOLE_COLOR);
    cout << "1";
    SetConsoleTextAttribute(hConsole, WHITE_CONSOLE_COLOR);
    cout << " - ilość bomb wokół danego pola." << endl << endl;

    cout << "ESC - wróć do menu";

    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}