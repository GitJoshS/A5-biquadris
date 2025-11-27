module Level1;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

Level1::Level1(): level{1}, howHeavy{0}{}

Level1::Level1(ifstream f): level{1}, howHeavy{0}, file{f}{}

char Level1::getNextBlockType(){
    // If file is initialized, read from file
    if (file.is_open()) {
        char blockType;
        
        if (file >> blockType) {
            return blockType;
        } else {
            // End of file, reset to beginning
            file.clear();           
            file.seekg(0, ios::beg);
            
            if (file >> blockType) {
                return blockType;
            }
        }
    }

    // No file was given - Level 1: S and Z have 1/12 probability, others have 1/6 probability
    int randomNum = rand() % 12;
    if (randomNum == 1) return 'S';
    else if (randomNum == 2) return 'Z';
    else if (randomNum <= 4) return 'I';
    else if (randomNum <= 6) return 'J';
    else if (randomNum <= 8) return 'L';
    else if (randomNum <= 10) return 'O';
    else {
        return 'T';
    }
}
