/* 
Filename: game-impl.cc 
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

module Game; 

import <string>;
import <iostream>;

using namespace std;

// default constructor
Game::Game() 
    : p1{nullptr}, 
      p2{nullptr}, 
      currP{nullptr}, 
      textDisplay{nullptr},
      graphicsDisplay{nullptr}, 
      highscore{0},
      textOnly{false} 
{}

// when constructing a game
Game::Game(const vector<string>& argv, const string& player1, const string& player2)
    : cmdCenter{},
      p1{make_unique<Player>(nullptr, 0, 1, player1)}, 
      p2{make_unique<Player>(nullptr, 0, 2, player2)},
      currP{p1.get()},
      textDisplay{nullptr},
      graphicsDisplay{nullptr},
      highscore{0},
      textOnly{true},
      args{argv}
{}

void Game::runGame() {
    while (true){
        Display display (); // Will add parameters later

        string command; 
        cout << "Make a move " << currP->getName() << ": ";

        if (cin >> command) {
            processCommand(command);
        }

        if (/* check for game over condition */) { // recieve state of game from board
            cout << "Game Over!" << endl;
            break;
        }

        currP = (currP == p1.get()) ? p2.get() : p1.get();
    }  
}

void Game::handleSpecialAction(string action) {

}   

void Game::triggerSpecialAction(string action) {
    
}   

void Game::processCommand(string command) {
    CommandCenter cc;
    Command cmd = cc.processCmd(command);
    cc.executeCmd(&cmd);
}

void Game::restart() { //
   
}
