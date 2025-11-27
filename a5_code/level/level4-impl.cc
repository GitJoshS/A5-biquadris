module Level4;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

Level4::Level4(): level{4}, howHeavy{1}, count{0}{}

Level4::Level4(ifstream f): level{4}, howHeavy{1}, file{f}, count{0}{}

char Level4::getNextBlockType(){
    count++;
    // Once 5 blocks have been dropped, it should return a * block. 
    // At this point, board should recall the function to get a letter block for "next"
    if (count == 5) {
        count = 0;
        return '*';
    }
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

    // No file was given - Level 4: S and Z have 2/9 probability, others have 1/9
     int randomNum = rand() % 9;
    if (randomNum <= 2) return 'S';
    else if (randomNum <= 4) return 'Z';
    else if (randomNum == 5) return 'I';
    else if (randomNum == 6) return 'J';
    else if (randomNum == 7) return 'L';
    else if (randomNum == 8) return 'O';
    else {
        return 'T';
    }
}
