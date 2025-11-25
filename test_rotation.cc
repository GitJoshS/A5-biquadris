#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// Copy the corrected rotation function for testing
vector<pair<int,int>> testRotation(vector<pair<int,int>>& cells, bool clockwise) {
    vector<pair<int,int>> rotated;
    
    // Find bounding rectangle (top-left origin: min_x,min_y = top-left, max_x,max_y = bottom-right)
    int min_x = cells[0].first, max_x = cells[0].first;
    int min_y = cells[0].second, max_y = cells[0].second;
    
    for (const auto& cell : cells) {
        min_x = min(min_x, cell.first);
        max_x = max(max_x, cell.first);
        min_y = min(min_y, cell.second);
        max_y = max(max_y, cell.second);
    }
    
    // Store original lower-left corner (min_x, max_y in top-left coordinate system)
    int orig_lower_left_x = min_x;
    int orig_lower_left_y = max_y;
    
    // Rotate each cell around origin
    for (const auto& cell : cells) {
        int rel_x = cell.first - orig_lower_left_x;
        int rel_y = cell.second - orig_lower_left_y;
        
        int new_x, new_y;
        if (clockwise) {
            // 90° clockwise: (x,y) -> (y, -x)
            new_x = rel_y;
            new_y = -rel_x;
        } else {
            // 90° counter-clockwise: (x,y) -> (-y, x)
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
    // Lower-left corner of rotated block is (rot_min_x, rot_max_y)
    int offset_x = orig_lower_left_x - rot_min_x;
    int offset_y = orig_lower_left_y - rot_max_y;
    
    // Apply offset to final positions
    for (auto& cell : rotated) {
        cell.first += offset_x;
        cell.second += offset_y;
    }
    
    return rotated;
}

void printBlock(const vector<pair<int,int>>& cells, const string& name) {
    cout << name << ": ";
    for (const auto& cell : cells) {
        cout << "(" << cell.first << "," << cell.second << ") ";
    }
    cout << endl;
}

int main() {
    // Test I-block
    vector<pair<int,int>> iblock = {{0,3}, {1,3}, {2,3}, {3,3}};
    printBlock(iblock, "I-block original");
    auto i_cw = testRotation(iblock, true);
    printBlock(i_cw, "I-block clockwise");
    auto i_ccw = testRotation(iblock, false);
    printBlock(i_ccw, "I-block counter-clockwise");
    cout << endl;
    
    // Test O-block
    vector<pair<int,int>> oblock = {{0,2}, {0,3}, {1,2}, {1,3}};
    printBlock(oblock, "O-block original");
    auto o_cw = testRotation(oblock, true);
    printBlock(o_cw, "O-block clockwise");
    auto o_ccw = testRotation(oblock, false);
    printBlock(o_ccw, "O-block counter-clockwise");
    cout << endl;
    
    // Test L-block
    vector<pair<int,int>> lblock = {{0,3}, {1,3}, {2,2}, {2,3}};
    printBlock(lblock, "L-block original");
    auto l_cw = testRotation(lblock, true);
    printBlock(l_cw, "L-block clockwise");
    auto l_ccw = testRotation(lblock, false);
    printBlock(l_ccw, "L-block counter-clockwise");
    cout << endl;
    
    // Test S-block
    vector<pair<int,int>> sblock = {{0,3}, {1,2}, {1,3}, {2,2}};
    printBlock(sblock, "S-block original");
    auto s_cw = testRotation(sblock, true);
    printBlock(s_cw, "S-block clockwise");
    auto s_ccw = testRotation(sblock, false);
    printBlock(s_ccw, "S-block counter-clockwise");
    cout << endl;
    
    // Test T-block
    vector<pair<int,int>> tblock = {{0,2}, {1,2}, {1,3}, {2,2}};
    printBlock(tblock, "T-block original");
    auto t_cw = testRotation(tblock, true);
    printBlock(t_cw, "T-block clockwise");
    auto t_ccw = testRotation(tblock, false);
    printBlock(t_ccw, "T-block counter-clockwise");
    
    return 0;
}