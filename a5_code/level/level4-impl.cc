module Level4;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

Level4::Level4() : Level{}, currentIndex{0}, useSequence{false}, count{0} {
    level = 4;
    howHeavy = 1;
}

Level4::Level4(ifstream& f) : Level{}, currentIndex{0}, useSequence{true}, count{0} {
    level = 4;
    howHeavy = 1;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        useSequence = false;
    }
}

char Level4::getNextBlockType(){
    count++;
    // Once 5 blocks have been dropped, it should return a * block. 
    // At this point, board should recall the function to get a letter block for "next"
    if (count == 5) {
        count = 0;
        return '*';
    }
    // If file sequence is being used, read from sequence
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }

    // No file was given - Level 4: S and Z have 2/9 probability, others have 1/9
    int randomNum = rand() % 9;
    if (randomNum <= 1) return 'S';
    else if (randomNum <= 3) return 'Z';
    else if (randomNum == 4) return 'I';
    else if (randomNum == 5) return 'J';
    else if (randomNum == 6) return 'L';
    else if (randomNum == 7) return 'O';
    else return 'T';
}
