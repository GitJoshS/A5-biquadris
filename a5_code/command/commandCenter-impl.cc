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
import Command;

using namespace std;

CommandCenter::CommandCenter(Game* g) : game{g}, commandList{loadCommandsFromFile()} {}

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
string CommandCenter::findUniqueCommand(const string input) {
    string match = "";
    for (const auto& cmd : commandList) {
        if (cmd.find(input) == 0) {
            if (!match.empty()) return ""; // multiple matches -> ambiguous
            match = cmd;
        }
    }
    return match;
}

string CommandCenter::processCmd(const string& cmdStr) {
    string result = findUniqueCommand(cmdStr);
    if (!result.empty()) return result;
    return "unknown";
}

bool CommandCenter::executeCmd(string cmd) {
    Player* player = game->getCurrentPlayer();
    if (cmd == "left") {
        return player->moveBlock(-1, 0);
    } else if (cmd == "right") {
        return player->moveBlock(1, 0);
    } else if (cmd == "down") {
        return player->moveBlock(0, 1);
    } else if (cmd == "drop") {
        return player->dropBlock();
    } else if (cmd == "clockwise") {
        player->rotate(true);
        return false;
    } else if (cmd == "counterclockwise") {
        player->rotate(false);
        return false;
    } else if (cmd == "levelup") {
        player->levelUp();
        return false;
    } else if (cmd == "leveldown") {
        player->levelDown();
        return false;
    } else if (cmd == "random") {
        return false;
    } else if (cmd == "norandom") {
        return false;
    } else if (cmd == "sequence") {
        return false;
    } else if (cmd == "restart") {
        return false;
    } else {
        cout << "Unknown command: " << cmd << endl;
        return false;
    }
}
