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

import Player;
import Display;
import TextDisplay;
import CommandCenter;

import <string>;
import <memory>;
import <vector>;
import <iostream>;

using namespace std; 

export class Game {
    CommandCenter cmdCenter;

    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    Player* currP;

    unique_ptr<Display> textDisplay;
    unique_ptr<Display> graphicsDisplay;

    int highscore;
    bool textOnly;
    // vector<string> args;

    public:
        Game();
        Game(const vector<string>& argv, const string& player1, const string& player2);

        Player* getCurrentPlayer();
        Player* getPlayer1();
        Player* getPlayer2();

        void swapTurn();

        void runGame();
        bool rerouteCommand(string command);

        void handleSpecialAction(string action);
        void triggerSpecialAction(string action);
        void reset();
};
