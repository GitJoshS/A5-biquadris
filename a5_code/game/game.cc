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
        /*
        Purpose: constructor for Game class.
        @param: argv - vector of command-line arguments
                player1 - name of player 1
                player2 - name of player 2
        returns: Game object
        */
        Game(const vector<string>& argv, const string& player1, const string& player2);

        /*
        Purpose: constructor for Game class with starting level.
        @param: argv - vector of command-line arguments
                player1 - name of player 1
                player2 - name of player 2
                startLevel - starting level for both players
        returns: Game object
        */
        Game(const vector<string>& argv, const string& player1, const string& player2, int startLevel);

        /*
        Purpose: constructor for Game class with script file.
        @param: argv - vector of command-line arguments
                player1 - name of player 1
                player2 - name of player 2
                scriptFile - path to the script file
                script1 - boolean indicating if script is for player 1
        returns: Game object
        */
        Game(const vector<string>& argv, const string& player1, const string& player2, 
             const string& scriptFile, bool script1);

        /*
        Purpose: Get the current player whose turn it is.
        @param: None
        returns: pointer to the current Player object
        */
        Player* getCurrentPlayer();

        /*
        Purpose: Get player 1.
        @param: None
        returns: pointer to Player 1 object
        */
        Player* getPlayer1();

        /*
        Purpose: Get player 2.
        @param: None
        returns: pointer to Player 2 object
        */
        Player* getPlayer2();

        /*
        Purpose: Swap the turn to the other player.
        @param: None
        returns: None
        */
        void swapTurn();

        /*
        Purpose: Run the main game loop, handling player turns and commands.
        @param: None
        returns: None
        */
        void runGame();

        /*
        Purpose: Reroute the given command to the appropriate handler.
        @param: command - string representing the command to be executed
        returns: true if the turn has ended, false otherwise
        */
        bool rerouteCommand(string command);

        /*
        Purpose: Execute a sequence of commands from a file.
        @param: name - name of the sequence file
        returns: true if the sequence was executed successfully, false otherwise
        */
        bool runSeq(string name);

        /*
        Purpose: Handle a special action triggered by a player.
        @param: action - string representing the special action to be handled
        returns: None
        */
        void handleSpecialAction(string action);

        /*
        Purpose: Trigger a special action for the current player.
        @param: action - string representing the special action to be triggered
        returns: None
        */
        void triggerSpecialAction(string action);

        /*
        Purpose: Reset the game to its initial state.
        @param: None
        returns: None
        */
        void reset();
};
