/* 
Filename: display.cc 
Author: Josh, Taim and Linh
Date: 2024-11-25
Last Edited: 2024-06-28

Description:
This file contains the interface of the Display class, which serves as a base class for different types of game displays.
*/

export module Display;

import <vector>;
import Player;

using namespace std;

export class Display {
    protected:
        vector<Player*> players;
    public:
        /*
        Purpose: General constructor that initializes the Display with a list of players.
        @param: players - vector of pointers to Player objects
        returns: Display object
        */
        Display(vector<Player*> players);

        /*
        Purpose: Render the current game state.
        @param: highscore - current high score in the game
        returns: None
        */
        virtual void render(int highscore) = 0;
};

