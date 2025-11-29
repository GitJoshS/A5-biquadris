/* 
Filename: graphicDisplay.cc 
Author: Josh, Taim and Linh
Date: 2024-11-28
Last Edited: 2024-06-28

Description:
This file contains the interface of the GraphicDisplay class, which provides a graphical display for the game.
*/

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
        /*
        Purpose: Constructor for GraphicDisplay class.
        @param: players - vector of pointers to Player objects
        returns: GraphicDisplay object
        */
        GraphicDisplay(vector<Player*> players);

        /*
        Purpose: Render the current game state graphically.
        @param: highscore - current high score in the game
        returns: None
        */
        void render(int highscore) override;
    private:
        // Helper methods to break down rendering

        /*
        Purpose: Render player information (name, level, score).
        @param: playerIndex - index of the player to render
                xOffset - horizontal offset for rendering
        returns: None
        */
        void renderPlayerInfo(int playerIndex, int xOffset);
        
        /*
        Purpose: Render the game board for a player.
        @param: playerIndex - index of the player to render
            xOffset - horizontal offset for rendering
            yOffset - vertical offset for rendering
        returns: None
        */
        void renderBoard(int playerIndex, int xOffset, int yOffset);

        /*
        Purpose: Render the next block preview for a player.
        @param: playerIndex - index of the player to render
            xOffset - horizontal offset for rendering
            yOffset - vertical offset for rendering
        returns: None
        */
        void renderNextBlock(int playerIndex, int xOffset, int yOffset);

        /*  
        Purpose: Get the color associated with a block type.
        @param: type - character representing the block type
        returns: integer representing the color
        */
        int getColorForBlock(char type);  // Map block types to colors
};
