export module Display;

import Board;

export class Display {
    public:
    virtual void render(vector<Board*> board, vector<int> score, vector<int> level, vector<Block*> next) = 0;
};

