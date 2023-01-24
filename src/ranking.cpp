#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>

#include "menu.hpp"
#include "ranking.hpp"
#include "functions.hpp"

#define ESC 27
#define NUMBER_OF_LEVELS 3

using namespace std;

struct RankingRecord {
    string name;
    unsigned int time;
    unsigned int level;
};

//function which allows sort function to sort data by struct parameter
bool compareTwoRecords(RankingRecord a, RankingRecord b) {
    return a.time < b.time;
}

void printRanking(vector<RankingRecord> ranking) {
    sort(ranking.begin(), ranking.end(), compareTwoRecords);

    switch(ranking[0].level) {
        case 1:
            printBigString("Poziom poczatkujacy");
        break;
        case 2:
            printBigString("Poziom sredni");
        break;
        case 3:
            printBigString("Poziom zaawansowany");
        break;
    }

    for (int i = 0; i < ranking.size(); i++) {
        int minutes = ranking[i].time / 60;
        int seconds = ranking[i].time - (minutes * 60);
        cout << i+1 << ". " << ranking[i].name << " " << minutes << ":" << (seconds < 10 ? "0":"") << seconds << endl;
    }
    cout << endl;
}

void ranking () {
    system("cls");
    clearConsole();

    fstream file("ranking.txt", ios::in);
    string word;

    vector <RankingRecord> rankings[NUMBER_OF_LEVELS];
    
    printBigString("Ranking", 26);

    if (file.good()) {
        int wordNumber = 0;
        RankingRecord record;

        while(!file.eof()) {
            file >> word;
            switch (wordNumber % 3) {
                case 0:
                    record.name = word; 
                break;
                case 1:
                    record.time = stoi(word);
                break;
                case 2:
                    record.level = stoi(word);
                    rankings[record.level - 1].push_back(record);
                break;
            }
            wordNumber++;
        }
        for (int i = 0; i < NUMBER_OF_LEVELS; i++) printRanking(rankings[i]);
        file.close();
    }

    cout << endl << "ESC - powrót do menu";
    printf("\e[?25l"); 

    unsigned char key;
    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}