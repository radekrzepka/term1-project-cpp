#include <iostream>
#include "functions.hpp"

#define LEFT_UP_BOX "╔"
#define RIGHT_UP_BOX "╗"
#define LEFT_DOWN_BOX "╚"
#define RIGHT_DOWN_BOX "╝"
#define HORIZONTAL_BOX "═"
#define VERTICAL_BOX "║"

using namespace std;

void printBigString (string text) {
    cout << LEFT_UP_BOX;
    for(int i = 0; i < text.length(); i++) cout << HORIZONTAL_BOX;
    cout << RIGHT_UP_BOX << endl;
    cout << VERTICAL_BOX << text << VERTICAL_BOX << endl;
    cout << LEFT_DOWN_BOX;
    for(int i = 0; i < text.length(); i++) cout << HORIZONTAL_BOX;
    cout << RIGHT_DOWN_BOX << endl;
}