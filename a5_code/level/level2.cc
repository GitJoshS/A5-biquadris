export module Level2;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level2 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    
    public: 
    Level2();
    Level2(ifstream& f);
    char getNextBlockType() override;
};
