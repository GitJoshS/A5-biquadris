export module TextDisplay;

import <vector>;
import <string>;
import Player;
import Display;

using namespace std;

export class TextDisplay : public Display {
    string boardsSpace = string(10, ' ');

    public:
        TextDisplay(vector<Player*> players);
        void render(int highscore) override;
        string spaceGen(int score);
    private:
        void renderStats(int width, int height, int playerCount, char blank);
        void renderBoards(int width, int height, int playerCount, char blank);
        void renderNexts(int width, int height, int playerCount, char blank);
};

