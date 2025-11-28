export module Level;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

export class Level {
    protected:
        int howHeavy;
        int level;
        ifstream file;

    public:
        Level(int level, ifstream& file = "");
        //// // Create the correct level class according to the level
        //// static Level* create(int levelNum);
        //// static Level* create(int levelNum, ifstream& f);
        // Returns the block type that should appears next ('I', 'J', 'L', 'O', 'S', 'Z', 'T')
        virtual char getNextBlockType() = 0;  
        virtual int getHowHeavy();
        int getLevel();
        virtual ~Level();
};
// int randomNum = rand() % 100;
