export module Level3;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level3 :: public Level {
    public: 
    Level3();
    Level3(ifstream f);
    char getNextBlockType();
}
