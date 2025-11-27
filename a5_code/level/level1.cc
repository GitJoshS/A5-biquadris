export module Level1;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level1 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    
    public: 
    Level1();
    Level1(ifstream& f);
    char getNextBlockType() override;
};
