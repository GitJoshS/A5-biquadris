export module Level2;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level2 :: public Level {
    public: 
    Level2();
    Level2(ifstream f);
    char getNextBlockType();
}
