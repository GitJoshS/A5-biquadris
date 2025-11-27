export module TextDisplay;

import <vector>;
import Player;

export class TextDisplay : public Display {
    string boardsSpace = "          ";
    public:

        TextDisplay();

        TextDisplay(vector<Player*> players);

        // void render(vector<Board*> board, vector<int> score, vector<int> level, vector<Block*> next);
        void render();
        string levelSpaceGen(int score);
};

