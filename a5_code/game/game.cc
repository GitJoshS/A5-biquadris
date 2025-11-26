/* 
Filename: game.cc
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the implementation of the Game class, which manages the overall game state,
including player turns, game initialization, and victory conditions.
*/

export module Game;

import Player;
import Display;
import <string>;

export class Game {
    Player* p1;
    Player* p2;
    Player* currP;
    Display* textDisplay;
    Display* graphicsDisplay;
    int highscore;
    bool textOnly;

    public: 
        void runGame(); // Will add more parameters later
        void handleSpecialAction(string action);
        void triggerSpecialAction(string action);
        void processCommand(string command);
        void restart();
};
