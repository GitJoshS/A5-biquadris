export module GraphicDisplay;

import <vector>;
import <memory>;
import Display;
import Player;
import xwindow;

using namespace std;

export class GraphicDisplay : public Display {
    Xwindow window;

    static const int cellSize = 20;        // pixels per grid cell
    static const int boardSpacing = 100;   // space between player boards
    static const int topMargin = 100;       // space for level/score text
    static const int bottomMargin = 150;
    static const int nextBlockMargin = 20; // space for "Next:" section
    static const int extraMargin = 20;

    public:
        GraphicDisplay(vector<Player*> players);
        void render(int highscore) override;
    private:
        // Helper methods to break down rendering
        void renderPlayerInfo(int playerIndex, int xOffset);
        void renderBoard(int playerIndex, int xOffset, int yOffset);
        void renderNextBlock(int playerIndex, int xOffset, int yOffset);
        int getColorForBlock(char type);  // Map block types to colors
};