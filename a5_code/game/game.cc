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
import GraphicDisplay;
import CommandCenter;

import <string>;
import <memory>;
import <vector>;
import <iostream>;

using namespace std; 

export class Game {
    vector<string> args;
    int highscore;
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
    Player* currP;
    unique_ptr<TextDisplay> textDisplay;
    unique_ptr<GraphicDisplay> graphicsDisplay;
    bool textOnly;
    CommandCenter cmdCenter;


    public:
        Game(const vector<string>& argv, const string& player1, const string& player2);
        Game(const vector<string>& argv, const string& player1, const string& player2, int startLevel);
        Game(const vector<string>& argv, const string& player1, const string& player2, 
             const string& scriptFile, bool script1);

        Player* getCurrentPlayer();
        Player* getPlayer1();
        Player* getPlayer2();

        void swapTurn();

        void runGame();
        bool rerouteCommand(string command);
        bool runSeq(string name);

        void handleSpecialAction(string action);
        void triggerSpecialAction(string action);
        void reset();
};
