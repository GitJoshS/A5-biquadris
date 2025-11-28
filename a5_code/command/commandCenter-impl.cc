/* 
Filename: commandCenter-impl.cc 
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the CommandCenter class, which serves as the central hub for 
command processing
*/

module CommandCenter; 

import <string>;
import <vector>;
import <fstream>;
import <iostream>;
import Board;
import Player;


using namespace std;

CommandCenter::CommandCenter() : commandList{loadCommandsFromFile()} {}

// helper function to load commands from file
vector<string> CommandCenter::loadCommandsFromFile() {
    vector<string> commands;
    ifstream file("command/commands.txt");
    if (!file) {
        cerr << "Error: commands.txt could not be opened." << endl;
        return commands;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) commands.push_back(line);
    }
    return commands;
}

// helper function to find unique command
string CommandCenter::findUniqueCommand(const string& input) {
    string match = "";
    for (const auto& cmd : commandList) {
        if (cmd.find(input) == 0) {
            if (!match.empty()) return ""; // multiple matches -> ambiguous
            match = cmd;
        }
    }
    return match;
}

string CommandCenter::processCmd(string cmd) {
    string result = findUniqueCommand(cmd);
    if (!result.empty()) return result;
    return "unknown";
}

bool CommandCenter::executeCmd(string cmd, Player* currentPlayer, Player* otherPlayer) {
    if (cmd == "left") {
        return currentPlayer->moveBlock(-1, 0);
    } else if (cmd == "right") {
        return currentPlayer->moveBlock(1, 0);
    } else if (cmd == "down") {
        return currentPlayer->moveBlock(0, 1);
    } else if (cmd == "drop") {
        return currentPlayer->dropBlock();
    } else if (cmd == "clockwise") {
        currentPlayer->rotate(true);
        return false;
    } else if (cmd == "counterclockwise") {
        currentPlayer->rotate(false);
        return false;
    } else if (cmd == "levelup") {
        currentPlayer->levelUp();
        return false;
    } else if (cmd == "leveldown") {
        currentPlayer->levelDown();
        return false;
    } else if (cmd == "random") {
        currentPlayer->getBoard()->restoreRandomLevel();
        return false;
    } else if (cmd == "norandom") {
        // This would need a file parameter - for now just return false
        // Implementation depends on how the file is provided
        return false;
    } else if (cmd == "sequence") {
        // This would need a sequence file parameter
        return false;
    } else {
        cout << "Unknown command: " << cmd << endl;
        return false;
    }
}
