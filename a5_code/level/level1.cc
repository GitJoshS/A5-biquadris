export module Level1;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level1 :: public Level {
    public: 
    Level1();
    Level1(ifstream f);
    char getNextBlockType();
}
