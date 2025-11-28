/* 
Filename: game-impl.cc 
Author: Josh Stein
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
import <fstream>;
import Player;
import Display;
import TextDisplay;
// import GraphicDisplay;
import CommandCenter;

// import Player;
// import Display;
// import CommandCenter;

using namespace std;

// default constructor
Game::Game()
    : p1{nullptr}, p2{nullptr}, currP{nullptr}, textDisplay{nullptr}, 
   // graphicsDisplay{nullptr}, 
    highscore{0}, textOnly{false} {}

// when constructing a game
Game::Game(const vector<string>& argv, const string& player1, const string& player2)
    : p1{make_unique<Player>(0, 1, player1, "../biquadris/biquadris_sequence1.txt")},
      p2{make_unique<Player>(0, 2, player2, "../biquadris/biquadris_sequence2.txt")},
      currP{p1.get()}, textDisplay{make_unique<TextDisplay>(vector<Player*>{p1.get(), p2.get()})}, 
      //graphicsDisplay{nullptr},
      highscore{0},
      textOnly{true}, cmdCenter{CommandCenter()} { }

Player* Game::getCurrentPlayer() { return currP; }
Player* Game::getPlayer1() { return p1.get(); }
Player* Game::getPlayer2() { return p2.get(); }

void Game::swapTurn() {
    currP = (currP == p1.get()) ? p2.get() : p1.get();
}

void Game::runGame() {
        while (true){
        textDisplay->render(currP->getRenderEffect());
    
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
                // Reset heaviness and render effect when turn ends
                currP->resetHeaviness();
                currP->resetRenderEffect();
                swapTurn();
            }
        }
    }  
}


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
            textDisplay->render(currP->getRenderEffect());  // Show board after each turn-ending move
        }
    }
    return false;  // The sequence command itself doesn't end the turn
}

void Game::handleSpecialAction(string action) {}   
void Game::triggerSpecialAction(string action) {}   

void Game::reset() { 
    p1->reset();
    p2->reset();
}
