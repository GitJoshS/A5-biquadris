/* 
Filename: game-impl.cc 
Author: Josh, Taim and Linh
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

module Game; 

import <iostream>;
import <string>;
import <vector>;
import <memory>;
import <algorithm>;
import <fstream>;
import Player;
import Display;
import TextDisplay;
import GraphicDisplay;
import CommandCenter;

// import Player;
// import Display;
// import CommandCenter;

using namespace std;

/*
Basic constructor with command-line options - no startLevel or file Note, we intialize the two players
here which will then intialize their boards, blocks, levels, etc.
*/
Game::Game(const vector<string>& argv, const string& player1, const string& player2)
    : args{argv}, highscore{0},
      p1{make_unique<Player>(0, 1, player1, "../biquadris/biquadris_sequence1.txt")},
      p2{make_unique<Player>(0, 2, player2, "../biquadris/biquadris_sequence2.txt")},
      currP{p1.get()}, textDisplay{make_unique<TextDisplay>(vector<Player*>{p1.get(), p2.get()})}, 
      graphicsDisplay{find(argv.begin(), argv.end(), string("-text")) == argv.end() 
                      ? make_unique<GraphicDisplay>(vector<Player*>{p1.get(), p2.get()})
                      : nullptr},
      textOnly{true}, cmdCenter{CommandCenter()} {}

/*
Constructor with command-line options - startLevel.
*/
Game::Game(const vector<string>& argv, const string& player1, const string& player2, int startLevel)
    : args{argv}, highscore{0},
      p1{make_unique<Player>(0, 1, player1, "../biquadris/biquadris_sequence1.txt", startLevel)},
      p2{make_unique<Player>(0, 2, player2, "../biquadris/biquadris_sequence2.txt", startLevel)},
      currP{p1.get()}, textDisplay{make_unique<TextDisplay>(vector<Player*>{p1.get(), p2.get()})}, 
      graphicsDisplay{find(argv.begin(), argv.end(), string("-text")) == argv.end() 
                      ? make_unique<GraphicDisplay>(vector<Player*>{p1.get(), p2.get()})
                      : nullptr},
      textOnly{true}, cmdCenter{CommandCenter()} {}

/*
Constructor with command-line options - script file.
*/
Game::Game(const vector<string>& argv, const string& player1, const string& player2, 
             const string& scriptFile, bool script1) 
    : args{argv}, highscore{0},
      p1{script1 ? make_unique<Player>(0, 1, player1, scriptFile) 
                 : make_unique<Player>(0, 1, player1, "../biquadris/biquadris_sequence1.txt")},
      p2{!script1 ? make_unique<Player>(0, 2, player2, scriptFile) 
                  : make_unique<Player>(0, 2, player2, "../biquadris/biquadris_sequence2.txt")},
      currP{p1.get()}, textDisplay{make_unique<TextDisplay>(vector<Player*>{p1.get(), p2.get()})}, 
      graphicsDisplay{find(argv.begin(), argv.end(), string("-text")) == argv.end() 
                      ? make_unique<GraphicDisplay>(vector<Player*>{p1.get(), p2.get()})
                      : nullptr},
      textOnly{true}, cmdCenter{CommandCenter()} {}

/*
Get the current player whose turn it is.
*/
Player* Game::getCurrentPlayer() { return currP; }

/*
Get player 1.
*/
Player* Game::getPlayer1() { return p1.get(); }

/*
Get player 2.
*/
Player* Game::getPlayer2() { return p2.get(); }

/*
swapTurn switches the current player pointer to the other player.
We call this at the end of each turn aka a block is dropped.
*/
void Game::swapTurn() {
    currP = (currP == p1.get()) ? p2.get() : p1.get();
}

/*
Main game loop that runs until the game is exited. It works by rendering the displays,
processing user commands, checking for game over conditions, and managing turn transitions.
In addition if applicable it may apply special effects between turns.
*/
void Game::runGame() {

        // See if use wants text only mode
        auto it = find(args.begin(), args.end(), string("-text"));
        bool textOnly = it != args.end();

        while (true){
        textDisplay->render(highscore);
        if (!textOnly) {
            graphicsDisplay->render(highscore);
        }

    
        string command; 
        cout << "Make a move " << currP->getName() << ": ";

        if (cin >> command) {
            bool turnEnded = rerouteCommand(command);
            
            if (currP->getBoard()->isGameOver()) { // Check game over BEFORE swapping
                cout << "Game Over!" << endl;
                reset(); 
            }
            
            if (turnEnded) {
                // Handle special effects for 2+ row clears
                if (currP->hasSpecialEffects()) {
                    Player* otherPlayer = (currP == p1.get()) ? p2.get() : p1.get();
                    cmdCenter.executeSpecialEffectsCmd("", currP, otherPlayer);
                    currP->resetSpecialEffects();
                }

                // Apply highscore
                if (currP->getCurScore() > highscore) {
                    highscore = currP->getCurScore();
                }

                // Reset heaviness and render effect when turn ends
                currP->resetHeaviness();
                currP->resetRenderEffect();
                swapTurn();
            }
        }
    }  
}


/*
Reroute command handles commands that need access to Game state before passing them to CommandCenter.
*/
bool Game::rerouteCommand(string command) {
    int mult = 0;
    string cmd = cmdCenter.processCmd(command, &mult);
    
    // Handle game-level commands that need access to Game state
    if (cmd == "restart") {
        reset();
        return false; // Don't end turn
    }
    if (cmd == "sequence") {
        string name;
        cin >> name;
        for (int i = 0; i < mult; ++i) {
            runSeq(name);
            cout << "RunSeq ran" << endl;
        }
        return false;
    }
    
    Player* otherPlayer = (currP == p1.get()) ? p2.get() : p1.get();
    return cmdCenter.executeCmd(cmd, currP, otherPlayer, mult);
}

/*
runSeq reads commands from a file and executes them one at a time. It checks for game over conditions
after each command and handles turn transitions appropriately. It is used for the "sequence" command.
*/
bool Game::runSeq(string name) {

    ifstream file("files/" + name);
    if (!file) {
        cerr << "Error: Could not open sequence.txt" << endl;
        return false;
    }
    
    // Read and execute commands from file one at a time
    string fileCmd;
    while (file >> fileCmd) {
        bool turnEnded = rerouteCommand(fileCmd);  // Recursive, but controlled
        
        if (currP->getBoard()->isGameOver()) {
            cout << "Game Over!" << endl;
            reset();
        }
        
        if (turnEnded) {
            // Handle special effects for 2+ row clears
            if (currP->hasSpecialEffects()) {
                Player* otherPlayer = (currP == p1.get()) ? p2.get() : p1.get();
                cmdCenter.executeSpecialEffectsCmd("", currP, otherPlayer);
                currP->resetSpecialEffects();
            }
            // Reset heaviness and render effect when turn ends
            currP->resetHeaviness();
            currP->resetRenderEffect();
            swapTurn();
            textDisplay->render(highscore);  // Show board after each turn-ending move
        }
    }
    return false;  // The sequence command itself doesn't end the turn
}

/*
reset resets the game state for both players by calling their reset methods.
*/
void Game::reset() { 
    p1->reset();
    p2->reset();
}
