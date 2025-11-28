module LevelFactory;

import Level0;
import Level1;
import Level2;
import Level3;
import Level4;

using namespace std;

unique_ptr<Level> LevelFactory::create(int level) {
    switch(level) {
        case 0: return make_unique<Level0>();
        case 1: return make_unique<Level1>();
        case 2: return make_unique<Level2>();
        case 3: return make_unique<Level3>();
        case 4: return make_unique<Level4>();
        default: return make_unique<Level0>();
    }
}

unique_ptr<Level> LevelFactory::create(int level, ifstream& f) {
    switch(level) {
        case 0: return make_unique<Level0>(f);
        case 1: return make_unique<Level1>(f);
        case 2: return make_unique<Level2>(f);
        case 3: return make_unique<Level3>(f);
        case 4: return make_unique<Level4>(f);
        default: return make_unique<Level0>(f);
    }
}