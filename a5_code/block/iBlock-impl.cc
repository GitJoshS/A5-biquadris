module IBlock;

import string;
import utility;
import vector;
import Block;

IBlock::IBlock(int level) : tilesLeft{4}, blockType{I}, levelGenerated{level}, curRotation{0},
                            cells{{0,3}, {1,3}, {2,3}, {3,3}}{}
char IBlock::getShape() {
    return 'I';
}
