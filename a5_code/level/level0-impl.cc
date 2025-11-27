module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

Level0::Level0() : Level{}, currentIndex{0} {
    level = 0;
    howHeavy = 0;
    sequence = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
}

Level0::Level0(ifstream& f) : Level{}, currentIndex{0} {
    level = 0;
    howHeavy = 0;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        sequence = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};
    }
}

char Level0::getNextBlockType(){
    if (sequence.empty()) return 'I';
    char result = sequence[currentIndex];
    currentIndex = (currentIndex + 1) % sequence.size();
    return result;
}
