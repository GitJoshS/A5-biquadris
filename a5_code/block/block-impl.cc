/* 
Filename: block-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This is the implementation file for the Block class, which represents individual blocks and is a
super class for all specific block types in the Biquadris game. This file contains the definitions of the
Block class methods. It handles the construction of blocks, rotation logic, position management, and cell tracking.
*/

module Block;

import <string>;
import <utility>;
import <vector>;

using namespace std;

/*
The constructor for the Block class.
*/
Block::Block(char blockType, int levelGenerated, int cellsLeft, vector<pair<int,int>> cells) : 
    blockType{blockType}, levelGenerated{levelGenerated}, cellsLeft{cellsLeft}, cells{cells} {}

/*
 Get's the current position of the block's cells. This method returns the coordinates of 
the block's cells on the board.
*/
vector<pair<int,int>> Block::getPosition() {
    return cells;
}

/*
setPosition Sets the position of the block to a new position and updates the coordinates of the block's cells.
*/
void Block::setPosition(vector<pair<int,int>>& newPos) {
    cells = newPos;
}

/*
getType just returns the type of the block as a character. It indicates what kind of block it is 
(I, J, L, O, S, T, Z).
*/
char Block::getType(){
    return blockType;
}

/*
rotatePositions works by first determining the bounding rectangle of the block's current cells.
It then calculates the new positions of each cell based on whether the rotation is clockwise or counterclockwise.
Finally, it adjusts the positions so that the rotated block's lower-left corner aligns with the original position.
It returns a vector of pairs representing the new coordinates after rotation.
*/
vector<pair<int,int>> Block::rotatePosition(bool clockwise) {
    vector<pair<int,int>> rotated;
    
    // Find bounding rectangle 
    int min_x = cells[0].first, max_x = cells[0].first;
    int min_y = cells[0].second, max_y = cells[0].second;
    
    for (const auto& cell : cells) {
        min_x = min(min_x, cell.first);
        max_x = max(max_x, cell.first);
        min_y = min(min_y, cell.second);
        max_y = max(max_y, cell.second);
    }
    
    // Store original lower-left corner 
    int orig_x = min_x;
    int orig_y = max_y;
    
    // Rotate each cell around origin
    for (const auto& cell : cells) {
        int rel_x = cell.first - orig_x;
        int rel_y = cell.second - orig_y;
        
        int new_x, new_y;
        if (clockwise) {
            // Clockwise: (x,y) -> (y, -x)
            new_x = rel_y;
            new_y = -rel_x;
        } else {
            // Counter-clockwise: (x,y) -> (-y, x)
            new_x = -rel_y;
            new_y = rel_x;
        }
        
        rotated.push_back({new_x, new_y});
    }
    
    // Find bounding rectangle of rotated block
    int rot_min_x = rotated[0].first, rot_max_x = rotated[0].first;
    int rot_min_y = rotated[0].second, rot_max_y = rotated[0].second;
    
    for (const auto& cell : rotated) {
        rot_min_x = min(rot_min_x, cell.first);
        rot_max_x = max(rot_max_x, cell.first);
        rot_min_y = min(rot_min_y, cell.second);
        rot_max_y = max(rot_max_y, cell.second);
    }
    
    // Position the rotated block so its lower-left corner is at original position
    int offset_x = orig_x - rot_min_x;
    int offset_y = orig_y - rot_max_y;
    
    // Apply offset to final positions
    for (auto& cell : rotated) {
        cell.first += offset_x;
        cell.second += offset_y;
    }
    
    return rotated;
}

/*
decreaseCells works by decreasing the cellsLeft attribute by 1 each time a cell in the block is destroyed.
*/
bool Block::decreaseCells() {
    cellsLeft--;
    if (cellsLeft == 0) {
        return true;
    }
    return false;
}

/*
getLevelGenerated simply returns the level at which the block was generated.
*/
int Block::getLevelGenerated() {
    return levelGenerated;
}
