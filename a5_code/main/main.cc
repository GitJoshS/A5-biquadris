/* 
Filename: main.cc
Author: Taim Alsaadi and Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This is the main file that runs Biquardis.
*/

import Game;

import <iostream>;
import <vector>;
import <string>;
import <sstream>;

using namespace std;

int main(int argc, char* argv[]) {

    vector<string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    } 

    string p1, p2, start;

    cout << "Please enter your name Player 1: ";
    cin >> p1;

    cout << "Please enter your name Player 2: ";
    cin >> p2;
    
    cout << "Start game? (y/n): ";
    cin >> start;

    if (start == "y" || start == "Y" || start == "yes" || start == "YES") {
        Game game = Game(args, p1, p2);
        game.runGame(); 
    }
}
