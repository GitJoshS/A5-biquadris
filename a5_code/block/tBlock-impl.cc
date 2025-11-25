module TBlock;

import string;
import utility;
import vector;
import Block;

TBlock::TBlock(int level) : tilesLeft{4}, blockType{T}, levelGenerated{level}, curRotation{0},
                            cells{{0,2}, {1,2}, {1,3}, {2,2}}{}
char TBlock::getShape() {
    return 'T';
}