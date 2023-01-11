#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include "menu.hpp"
#include "ranking.hpp"

#define ESC 27

using namespace std;

struct RankingData {
    string name;
    unsigned int time;
    unsigned int level;
};

void ranking () {
    system("cls");

    ifstream file("ranking.txt");
    string line;

    vector <RankingData> begginerScores;
    vector <RankingData> intermediateScores;
    vector <RankingData> advancedScores;
    
    cout << "Ranking" << endl;

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
                    case 2:
                        record.level = stoi(text);
                    break;
                }

                wordNumber++;
                line.erase(0, pos+space_delimiter.length());
            }

            switch (record.level) {
                case 0:
                    begginerScores.push_back(record);
                break;
                case 1:
                    intermediateScores.push_back(record);
                break;
                case 2:
                    advancedScores.push_back(record);
                break;
            }
        }

        for (int i = 0; i < begginerScores.size(); i++) {
            cout << i << endl;
            cout << begginerScores[i].name << " " << begginerScores[i].time << " " << begginerScores[i].level << endl;
        }
    }

    cout << "ESC - powrot do menu";

    unsigned char key;
    do {
        while(kbhit()) {
            key = getch();
        }
    } while (key != ESC);

    menu();
}