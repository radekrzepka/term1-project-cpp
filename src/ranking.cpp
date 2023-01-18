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

struct RankingData {
    string name;
    unsigned int time;
    unsigned int level;
};

//function which allows sort function to sort data by struct parameter
bool compareTwoRecords(RankingData a, RankingData b) {
    return a.time < b.time;
}

void printRanking(vector<RankingData> ranking) {
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

    ifstream file("ranking.txt");
    string line;

    vector <RankingData> rankings[NUMBER_OF_LEVELS];
    
    printBigString("Ranking", 26);

    if (file.good()) {
        while(!file.eof()) {
            getline(file,line);

            RankingData record;
            size_t pos = 0;
            string space_delimiter = " ";
            int wordNumber = 0;

            while((pos = line.find(space_delimiter)) != string::npos) {
                string text = line.substr(0, pos);

                switch (wordNumber) {
                    case 0:
                        record.name = text;
                    break;
                    case 1:
                        record.time = stoi(text);
                    break;
                }

                wordNumber++;
                line.erase(0, pos+space_delimiter.length());
            }

            record.level = stoi(line);
            rankings[record.level - 1].push_back(record);
        }
        for (int i = 0; i < NUMBER_OF_LEVELS; i++) printRanking(rankings[i]);
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