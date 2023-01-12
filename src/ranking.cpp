#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "menu.hpp"
#include "ranking.hpp"
#include "functions.hpp"

#define ESC 27

using namespace std;

struct RankingData {
    string name;
    unsigned int time;
    unsigned int level;
};

void printRanking(vector<RankingData> ranking) {
    cout << endl;
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
}

bool compareTwoRecords(RankingData a, RankingData b) {
    return a.time < b.time;
}

void ranking () {
    system("cls");

    ifstream file("ranking.txt");
    string line;

    vector <RankingData> begginerScores;
    vector <RankingData> intermediateScores;
    vector <RankingData> advancedScores;
    
    printBigString("Ranking", 16);

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

            switch (record.level) {
                case 1:
                    begginerScores.push_back(record);
                break;
                case 2:
                    intermediateScores.push_back(record);
                break;
                case 3:
                    advancedScores.push_back(record);
                break;
            }
        }

        sort(begginerScores.begin(), begginerScores.end(), compareTwoRecords);
        sort(intermediateScores.begin(), intermediateScores.end(), compareTwoRecords);
        sort(advancedScores.begin(), advancedScores.end(), compareTwoRecords);

        printRanking(begginerScores);
        printRanking(intermediateScores);
        printRanking(advancedScores);
    }

    cout << endl << "ESC - powrot do menu";

    unsigned char key;
    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}