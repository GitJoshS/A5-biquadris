module Level2;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

Level2::Level2() : Level{}, currentIndex{0}, useSequence{false} {
    level = 2;
    howHeavy = 0;
}

Level2::Level2(ifstream& f) : Level{}, currentIndex{0}, useSequence{true} {
    level = 2;
    howHeavy = 0;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        useSequence = false;
    }
}

char Level2::getNextBlockType(){
    // If file sequence is being used, read from sequence
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }

    // No file was given - Level 2: Equal probability for all blocks
    const vector<char> blocks = {'I', 'J', 'L', 'S', 'Z', 'O', 'T'};
    int randomNum = rand() % 7;
    return blocks[randomNum];
}
