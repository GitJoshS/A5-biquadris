export module Level4;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level4 :: public Level {
    int count;
    public: 
    Level4();
    Level4(ifstream f);
    char getNextBlockType();
}
