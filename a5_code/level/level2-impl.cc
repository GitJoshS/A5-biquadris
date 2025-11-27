module Level2;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

Level2::Level2(): level{2}, howHeavy{0}{}

Level2::Level2(ifstream f): level{2}, howHeavy{0}, file{f}{}

char Level2::getNextBlockType(){
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

    // No file was given - Level 2: Equal probability for all blocks
    const vector<char> blocks = {'I', 'J', 'L', 'S', 'Z', 'O', 'T'};
    int randomNum = rand() % 7;
    return blocks[randomNum];
}
