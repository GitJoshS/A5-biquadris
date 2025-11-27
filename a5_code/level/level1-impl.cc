module Level1;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

Level1::Level1() : Level{}, currentIndex{0}, useSequence{false} {
    level = 1;
    howHeavy = 0;
}

Level1::Level1(ifstream& f) : Level{}, currentIndex{0}, useSequence{true} {
    level = 1;
    howHeavy = 0;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        useSequence = false;
    }
}

char Level1::getNextBlockType(){
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }
    
    int randomNum = rand() % 12;
    if (randomNum == 1) return 'S';
    else if (randomNum == 2) return 'Z';
    else if (randomNum <= 4) return 'I';
    else if (randomNum <= 6) return 'J';
    else if (randomNum <= 8) return 'L';
    else if (randomNum <= 10) return 'O';
    else return 'T';
}
