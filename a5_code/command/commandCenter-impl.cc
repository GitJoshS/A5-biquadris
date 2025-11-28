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
import <sstream>;
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

string CommandCenter::processCmd(string cmd, int* multiplier) {
    istringstream iss{cmd};
    if (!(iss >> *multiplier)) {
        iss.clear();
        iss.seekg(0);
        *multiplier = 1;
    }
    iss >> cmd;
    string result = findUniqueCommand(cmd);
    if (!result.empty()) return result;
    return "unknown";
}

bool CommandCenter::executeCmd(string cmd, Player* currentPlayer, Player* otherPlayer, int mult) {
    if (cmd == "left") {    
        for(int i = 0; i < mult; ++i) currentPlayer->moveBlock(-1, 0);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "right") {
        for(int i = 0; i < mult; ++i) currentPlayer->moveBlock(1, 0);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "down") {
        for(int i = 0; i < mult; ++i) currentPlayer->moveBlock(0, 1);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "drop") {
        for(int i = 0; i < mult; ++i) currentPlayer->dropBlock();
        return true;
    } else if (cmd == "clockwise") {
        for(int i = 0; i < mult; ++i) currentPlayer->rotate(true);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "counterclockwise") {
        for(int i = 0; i < mult; ++i) currentPlayer->rotate(false);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "levelup") {
        for(int i = 0; i < mult; ++i) currentPlayer->levelUp();
    } else if (cmd == "leveldown") {
        for(int i = 0; i < mult; ++i) currentPlayer->levelDown();
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
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || 
               cmd == "S" || cmd == "T" || cmd == "Z") {
        // Force current player's block
        currentPlayer->getBoard()->forceBlockType(cmd[0]);
        return false;
    } else {
        cout << "Unknown command: " << cmd << endl;
        return false;
    }
    return false;
}

bool CommandCenter::executeSpecialEffectsCmd(string cmd, Player* currentPlayer, Player* otherPlayer) {
    cout << "Apply special effects: ";
    string command;
    cin >> command;
    
    if (command == "force") {
        string blockType;
        if (cin >> blockType && blockType.length() == 1) {
            char type = blockType[0];
            if (type == 'I' || type == 'J' || type == 'L' || type == 'O' || 
                type == 'S' || type == 'T' || type == 'Z') {
                if (otherPlayer) {
                    otherPlayer->getBoard()->forceBlockType(type);
                }
            } else {
                cout << "Invalid block type for special effects: " << type << endl;
            }
        } else {
            cout << "Force command requires a block type (I, J, L, O, S, T, Z)" << endl;
        }
    } else if (command == "heavy") {
        if (otherPlayer) {
            otherPlayer->addHeaviness(2);
        }
    } else if (command == "blind") {
        if (otherPlayer) {
            otherPlayer->setRenderEffect("blind");
        }
    } else {
        cout << "Invalid special effects command. Use 'force', 'heavy', or 'blind'." << endl;
    }
    return true; // Special effects commands always succeed
}
