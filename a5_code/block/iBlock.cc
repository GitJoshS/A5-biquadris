export module IBlock;

import <string>;
import <utility>;
import <vector>;
import Block;

using namespace std;

export class IBlock : public Block{
    public:
    IBlock(int level);
};
