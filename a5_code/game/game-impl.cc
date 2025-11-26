/* 
Filename: game-impl.cc 
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

module Game; 

import Display; 
import commandCenter; 
import Player; 
import <string>;
import <iostream>;

void Game::runGame() {
    cout << "Starting Game!" << endl;

    cout << "Please enter your name Player 1: ";
    cin << p1;

    cout << "Please enter your name Player 2: ";
    cin << p2;

    // Need to figure out how we will intialize a new board for each player
    Player *p1 = new Player(nullptr, 0, 1, p1Name);
    Player *p2 = new Player(nullptr, 0, 1, p1Name);
    Player *currP = p1;

    while (true){
        Display display (); // Will add parameters later
        string command; 
        cout << "Make a move " <<  << ": ";

        if (cin >> command) {
            processCommand(command);
        }

        if (/* check for game over condition */) {
            cout << "Game Over!" << endl;
            break;
        }

        currP = (currP == p1) ? p2 : p1;
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

void Game::restart() {
    // Reset game state to initial conditions
    Player* p1 = new Player(/* initial params */);
    Player* p2 = new Player(/* initial params */);
    currP = p1;

}
