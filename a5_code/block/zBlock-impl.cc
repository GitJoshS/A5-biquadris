module ZBlock;

import string;
import utility;
import vector;
import Block;

ZBlock::ZBlock(int level) : tilesLeft{4}, blockType{Z}, levelGenerated{level}, curRotation{0},
                            cells{{0,2}, {1,2}, {1,3}, {2,3}}{}
char ZBlock::getShape() {
    return 'Z';
}
