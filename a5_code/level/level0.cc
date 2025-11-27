export module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;
import Level;

using namespace std;

export class Level0 : public Level {
    vector<char> sequence;
    int currentIndex;
    
    public: 
    Level0();
    Level0(ifstream& f);
    char getNextBlockType() override;
};
