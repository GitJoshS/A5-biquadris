module Level;

import <vector>;
import <cstdlib>;

using namespace std;

Level* Level::create(int level) {
    switch(level) {
        case 0: return new Level0();
        case 1: return new Level1();
        case 2: return new Level2();
        case 3: return new Level3();
        case 4: return new Level4();
        default: return new Level0();
    }
}

Level* Level::create(int level, const ifstream f) {
    switch(level) {
        case 0: return new Level0(f);
        case 1: return new Level1(f);
        case 2: return new Level2(f);
        case 3: return new Level3(f);
        case 4: return new Level4(f);
        default: return new Level0(f);
    }
}

int Level::getHowHeavy() {
    return howHeavy;
}

int Level::getLevel() {
    return level;
}

Level::~Level() {
        if (inputFile.is_open()) {
            inputFile.close();
        }
    }
    