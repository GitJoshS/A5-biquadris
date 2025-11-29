/* 
Filename: textDisplay.cc 
Author: Josh, Taim and Linh
Date: 2024-11-25
Last Edited: 2024-06-28

Description:
This file contains the interface of the TextDisplay class, which provides a text-based display for the game.
*/

export module TextDisplay;

import <vector>;
import <string>;
import Player;
import Display;

using namespace std;

export class TextDisplay : public Display {
    string boardsSpace = string(10, ' ');

    public:
        /*
        Purpose: Constructor for TextDisplay class.
        @param: players - vector of pointers to Player objects
        returns: TextDisplay object
        */
        TextDisplay(vector<Player*> players);

        /*
        Purpose: Render the current game state as text.
        @param: highscore - current high score in the game
        returns: None
        */
        void render(int highscore) override;

        /*
        Purpose: Generate a string of spaces for formatting.
        @param: score - score to determine the number of spaces
        returns: string of spaces
        */
        string spaceGen(int score);
    private:
        /*
        Purpose: Render the statistics section of the display.
        @param: width - width of the display area
            height - height of the display area
            playerCount - number of players
            blank - character representing blank space
        returns: None
        */
        void renderStats(int width, int height, int playerCount, char blank);

        /*
        Purpose: Render the boards section of the display.
        @param: width - width of the display area
            height - height of the display area
            playerCount - number of players
            blank - character representing blank space
        returns: None
        */
        void renderBoards(int width, int height, int playerCount, char blank);
        
        /*
        Purpose: Render the next blocks section of the display.
        @param: width - width of the display area
            height - height of the display area
            playerCount - number of players
            blank - character representing blank space
        returns: None
        */
        void renderNexts(int width, int height, int playerCount, char blank);
};
