module Block;

import <string>;
import <utility>;
import <vector>;

using namespace std;

Block::Block(char blockType, int levelGenerated, int cellsLeft, vector<pair<int,int>> cells) : 
    blockType{blockType}, levelGenerated{levelGenerated}, cellsLeft{cellsLeft} {}

vector<pair<int,int>> Block::getPosition() {
    return cells;
}
void Block::setPosition(vector<pair<int,int>>& newPos) {
    if (newPos.size() == 4) {
        cells = newPos;
    }
}

char Block::getType(){
    return blockType;
}
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

bool Block::decreaseCells() {
    cellsLeft--;
    if (cellsLeft == 0) {
        return true;
    }
    return false;
}

int Block::getLevelGenerated() {
    return levelGenerated;
}
