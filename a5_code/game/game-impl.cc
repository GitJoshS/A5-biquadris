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
    : p1{make_unique<Player>(nullptr, 0, 1, player1)},
      p2{make_unique<Player>(nullptr, 0, 2, player2)},
      currP{p1.get()}, textDisplay{nullptr}, graphicsDisplay{nullptr}, highscore{0},
      textOnly{true}, args{argv} {
    cmdCenter = make_unique<CommandCenter>(this);
}

Player* Game::getCurrentPlayer() { return currP; }
Player* Game::getPlayer1() { return p1.get(); }
Player* Game::getPlayer2() { return p2.get(); }

void Game::swapTurn() {
    currP = (currP == p1.get()) ? p2.get() : p1.get();
}

void Game::runGame() {
    while (true){
        Display display{}; // Will add parameters later

        string command; 
        cout << "Make a move " << currP->getName() << ": ";

        if (cin >> command) {
            processCommand(command);
        }

        if (/* check for game over condition */) { // recieve state of game from board
            cout << "Game Over!" << endl;
            break;
        }

        if (/* logic for swapping turn from p1 to p2 */) { // need to swap turn when block droppped
            swapTurn();
        }
    }  
}

void Game::processCommand(string command) {
    Command cmd = cmdCenter->processCmd(command);
    cmdCenter->executeCmd(&cmd);
}

void Game::handleSpecialAction(string action) {}   
void Game::triggerSpecialAction(string action) {}   
void Game::restart() {
    // Reset game state    
}
