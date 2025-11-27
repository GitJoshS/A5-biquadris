export module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level0 :: public Level {
    public: 
    Level0(ifstream f);
    char getNextBlockType();
}
