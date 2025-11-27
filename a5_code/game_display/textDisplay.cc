export module TextDisplay;

import Board;

export class TextDisplay : public Display {
    string boardsSpace = "          ";
    public:
        void render(vector<Board*> board, vector<int> score, vector<int> level, vector<Block*> next);
        string levelSpaceGen(int score);
};

