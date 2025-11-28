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
import <cstdlib>;
import <iostream>;

using namespace std;

int main(int argc, char* argv[]) {
    // Default values
    int seed = -1;  // -1 means no seed set (use default random)
    string scriptFile1 = "../biquadris/biquadris_sequence1.txt";
    string scriptFile2 = "../biquadris/biquadris_sequence2.txt";
    int startLevel = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        if (arg == "-seed" && i + 1 < argc) {
            seed = stoi(argv[i + 1]);
            i++; // Skip the next argument since we consumed it
        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            scriptFile1 = argv[i + 1];
            i++; // Skip the next argument since we consumed it
        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            scriptFile2 = argv[i + 1];
            i++; // Skip the next argument since we consumed it
        } else if (arg == "-startlevel" && i + 1 < argc) {
            startLevel = stoi(argv[i + 1]);
            i++; // Skip the next argument since we consumed it
        }
    }

    // Set random seed if provided
    if (seed != -1) {
        srand(seed);
    }

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

    Game game = Game(args, p1, p2);
    if (start == "y" || start == "yes") {
        if (startLevel != 0) {
            game = Game(args, p1, p2, startLevel);
        }
        else if (scriptFile1 != "../biquadris/biquadris_sequence1.txt"){
            game = Game(args, p1, p2, scriptFile1, true);
        }
         else if (scriptFile2 != "../biquadris/biquadris_sequence2.txt"){
            game = Game(args, p1, p2, scriptFile2, false);
        }
        game.runGame(); 
    }
}
