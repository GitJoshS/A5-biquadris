module Level3;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;
import <string>;

using namespace std;

/*
Constructor for Level3 class.
*/
Level3::Level3() : Level(3), currentIndex{0}, useSequence{false} {
    level = 3;
    howHeavy = 1;
}

/*
Constructor for Level3 class that takes in a file stream. File stream contains the sequence
*/
Level3::Level3(ifstream& f) : Level(3), currentIndex{0}, useSequence{true} {
    level = 3;
    howHeavy = 1;
    char c;
    while (f >> c) {
        sequence.push_back(c);
    }
    if (sequence.empty()) {
        useSequence = false;
    }
}

/*
getNextBlockType works by first checking if a sequence is being used. If so, it returns the next block type
in the sequence, cycling through it as needed. If no sequence is used, it generates a random number
and maps it to a block type according to Level 3 rules for probabilities. It additionally sets howHeavy to 1.
*/
char Level3::getNextBlockType(){
    // If file sequence is being used, read from sequence
    if (useSequence && !sequence.empty()) {
        char result = sequence[currentIndex];
        currentIndex = (currentIndex + 1) % sequence.size();
        return result;
    }

    // No file was given - Level 3: S and Z have 2/9 probability, others have 1/9
    int randomNum = rand() % 9;
    if (randomNum <= 1) return 'S';
    else if (randomNum <= 3) return 'Z';
    else if (randomNum == 4) return 'I';
    else if (randomNum == 5) return 'J';
    else if (randomNum == 6) return 'L';
    else if (randomNum == 7) return 'O';
    else return 'T';
}
