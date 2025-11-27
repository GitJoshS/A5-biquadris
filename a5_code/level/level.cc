export module Level;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level {
    int howHeavy;
    int level;
    ifstream file;

    public:
    Level() {}
    // Create the correct level class according to the level
    static Level* create(int levelNum);
    static Level* create(int levelNum, const ifstream f);
    // Returns the block type that should appears next ('I', 'J', 'L', 'O', 'S', 'Z', 'T')
    virtual char getNextBlockType() = 0;  
    virtual int getHowHeavy();
    int getLevel();
    virtual ~Level();
};
// int randomNum = rand() % 100;
