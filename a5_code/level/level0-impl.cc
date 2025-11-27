module Level0;

import <vector>;
import <cstdlib>;
import <fstream>;
import <iostream>;

using namespace std;

Level0::Level0(ifstream f): level{0}, howHeavy{0}, file{f}{}

char Level0::getNextBlockType(){
    char blockType;
    
    if (file >> blockType) { // Successfully read a character
        return blockType;
    } else { // Reached end of file, reset to beginning
        file.clear();           
        file.seekg(0, ios::beg);
        
        if (file >> blockType) {
            return blockType;
        } else {
            return 'I'; // Default block type if any error occurs
        }
    }
}
