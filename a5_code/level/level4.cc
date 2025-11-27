export module Level4;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level4 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    int count;
    
    public: 
    Level4();
    Level4(ifstream& f);
    char getNextBlockType() override;
};
