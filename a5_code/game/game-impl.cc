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
import Player;
import Display;
import TextDisplay;
import CommandCenter;

// import Player;
// import Display;
// import CommandCenter;

using namespace std;

// default constructor
Game::Game()
    : p1{nullptr}, p2{nullptr}, currP{nullptr}, textDisplay{nullptr}, 
    graphicsDisplay{nullptr}, highscore{0}, textOnly{false} {}

// when constructing a game
Game::Game(const vector<string>& argv, const string& player1, const string& player2)
    : p1{make_unique<Player>(0, 1, player1, "../biquadris/biquadris_sequence1.txt")},
      p2{make_unique<Player>(0, 2, player2, "../biquadris/biquadris_sequence2.txt")},
      currP{p1.get()}, textDisplay{TextDisplay(vector<Player*>{p1.get(), p2.get()})}, graphicsDisplay{nullptr}, highscore{0},
      textOnly{true}, cmdCenter{CommandCenter()} { }

Player* Game::getCurrentPlayer() { return currP; }
Player* Game::getPlayer1() { return p1.get(); }
Player* Game::getPlayer2() { return p2.get(); }

void Game::swapTurn() {
    currP = (currP == p1.get()) ? p2.get() : p1.get();
}

void Game::runGame() {
    while (true){
        textDisplay.render();
    
        string command; 
        cout << "Make a move " << currP->getName() << ": ";

        if (cin >> command) {
            bool turnEnded = rerouteCommand(command);
            if (turnEnded) {
                swapTurn();
            }
        }

        if (currP->getBoard()->isGameOver()) { // recieve state of game from board
            cout << "Game Over!" << endl;
            reset(); 
        }
    }  
}

bool Game::rerouteCommand(string command) {
    string cmd = cmdCenter.processCmd(command);
    
    // Handle game-level commands that need access to Game state
    if (cmd == "restart") {
        reset();
        return false; // Don't end turn
    }
    
    Player* otherPlayer = (currP == p1.get()) ? p2.get() : p1.get();
    return cmdCenter.executeCmd(cmd, currP, otherPlayer);
}

void Game::handleSpecialAction(string action) {}   
void Game::triggerSpecialAction(string action) {}   

void Game::reset() { 
    p1->reset();
    p2->reset();
}
