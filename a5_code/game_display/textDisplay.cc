export module TextDisplay;

import <vector>;
import <string>;
import Player;
import Display;

using namespace std;

export class TextDisplay : public Display {
    string boardsSpace = "          ";
    public:
        TextDisplay(vector<Player*> players);

        // void render(vector<Board*> board, vector<int> score, vector<int> level, vector<Block*> next);
        void render() override;
        string spaceGen(int score);
};

