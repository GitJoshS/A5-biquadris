/* 
Filename: game.cc
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
including player turns, game initialization, and victory conditions.
*/

export module Game;

import Display; 
import CommandCenter; 
import Player; 

import <string>;

using namespace std;

export class Game {
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    Player* currP;
    
    unique_ptr<Display> textDisplay;
    unique_ptr<Display> graphicsDisplay;

    int highscore;
    bool textOnly;

    vector<string> args;
    CommandCenter cmdCenter; 

    public: 
        Game();
        Game(const vector<string>& argv, const string& player1, const string& player2);

        void runGame(); // Will add more parameters later
        void handleSpecialAction(string action);
        void triggerSpecialAction(string action);
        void processCommand(string command);
        void restart();
};
