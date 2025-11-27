export module Level3;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level3 : public Level {
    vector<char> sequence;
    int currentIndex;
    bool useSequence;
    
    public: 
    Level3();
    Level3(ifstream& f);
    char getNextBlockType() override;
};
