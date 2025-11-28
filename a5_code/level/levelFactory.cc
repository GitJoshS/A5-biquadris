export module LevelFactory;

import <fstream>;
import <memory>;
import Level;

using namespace std;

export class LevelFactory {
    public:
        unique_ptr<Level> create(int levelNum);
        unique_ptr<Level> create(int levelNum, ifstream& f);
};