/* 
Filename: main.cc
Author: Taim Alsaadi
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This is the main file that runs Biquardis.
*/

import <iostream>;
import <string>;
import <sstream>;
import Game;

using namespace std;

int main(int argc, char* argv[]) {

    cout << "Start game? (y/n): ";
    string input = '';

    vector<string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    } 

    if (cin >> input && input == "y") {
        Game game = Game{args, /*INPUTS*/};
        game.startGame(/*INPUTS*/);
    }

    return 0;
}