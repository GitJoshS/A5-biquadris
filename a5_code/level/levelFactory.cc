export module LevelFactory;

import <fstream>;
import <memory>;
import Level;

using namespace std;

export class LevelFactory {
    public:
        static unique_ptr<Level> create(int levelNum);
        static unique_ptr<Level> create(int levelNum, ifstream& f);
};