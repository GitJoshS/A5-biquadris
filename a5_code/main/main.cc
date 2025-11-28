/* 
Filename: main.cc
Author: Taim Alsaadi, Josh Stein and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This is the main file that runs Biquardis. Mains purpose is 
to parse command-line arguments, set up the game environment,
and initiate the game loop.
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
    string scriptFile1 = "../biquadris/biquadris_sequence1.txt";
    string scriptFile2 = "../biquadris/biquadris_sequence2.txt";
    int seed = -1;  // -1 means no seed set (use default random)
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

    // Convert argv to vector<string>
    vector<string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    } 
    
    // Get player names and start prompt
    string p1, p2, start;

    // p1 name
    cout << "Please enter your name Player 1: ";
    cin >> p1;

    // p2 name
    cout << "Please enter your name Player 2: ";
    cin >> p2;
    
    // Start game prompt
    cout << "Start game? (y/n): ";
    cin >> start;

    // Initialize and run the game: note if startLevel is 0, default behavior is used
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
    else {
        cout << "Okay, goodbye!." << endl;
    }
}
