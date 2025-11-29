export module GraphicDisplay;

import <vector>;
import <memory>;
import Display;
import Player;
import xwindow;

using namespace std;

export class GraphicDisplay : public Display {
    Xwindow window;

    const int cellSize = 20;        // pixels per grid cell
    const int boardSpacing = 100;   // space between player boards
    const int topMargin = 80;       // space for level/score text
    const int bottomMargin = 150;
    const int nextBlockMargin = 20; // space for "Next:" section
    const int extraMargin = 20;

    public:
        GraphicDisplay(vector<Player*> players);
        void render() override;
    private:
        // Helper methods to break down rendering
        void renderPlayerInfo(int playerIndex, int xOffset);
        void renderBoard(int playerIndex, int xOffset, int yOffset);
        void renderNextBlock(int playerIndex, int xOffset, int yOffset);
        int getColorForBlock(char type);  // Map block types to colors
};