export module Display;

import Board;

export class Display {
    protected:
        vector<Player*> players;
    public:
        virtual void render(vector<Board*> board, vector<int> score, vector<int> level, vector<Block*> next) = 0;
};

