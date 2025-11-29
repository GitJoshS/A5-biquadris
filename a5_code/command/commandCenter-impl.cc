/* 
Filename: commandCenter-impl.cc
Author: Taim, Josh and Linh
Date: 2024-11-25
Last Edited: 2024-11-28

Description:
This file contains the implementation of the CommandCenter class, which serves as the
central hub for command processing in the Biquadris game.
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

// Note, we loadCommandFromFile() in constructor in order to have commandList ready
//  from a file called "command/commands.txt" which contains all valid commands
//  in the game. We do this to enable abbreviation matching.
CommandCenter::CommandCenter() : commandList{loadCommandsFromFile()} {}

// Helper function to load commands from file, used in the constructor
// to populate commandList.
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

// Helper function to find unique commands from the commandList that match
//  the given input prefix. Returns the full command if unique match found,
//  otherwise returns an empty string since ambiguity means no valid command.
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

// Process command string to extract multiplier and command. It
//  does this using a pointer so that we can access the multiplier
//  the multiplier inside of Game class to execute the commands multiple times.
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

// Execute the given command for the current player. For example, 
//  "left" moves the block left, "drop" drops the block, etc. Calls
//  appropriate Player methods to perform actions from objects,
//  contained in the current Game instance. 
bool CommandCenter::executeCmd(string cmd, Player* currentPlayer, Player* otherPlayer, int mult) {
    if (cmd == "left") {    
        for (int i = 0; i < mult; ++i) currentPlayer->moveBlock(-1, 0);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "right") {
        for (int i = 0; i < mult; ++i) currentPlayer->moveBlock(1, 0);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "down") {
        for (int i = 0; i < mult; ++i) currentPlayer->moveBlock(0, 1);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "drop") {
        for (int i = 0; i < mult; ++i) currentPlayer->dropBlock();
        return true;
    } else if (cmd == "clockwise") {
        for (int i = 0; i < mult; ++i) currentPlayer->rotate(true);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "counterclockwise") {
        for (int i = 0; i < mult; ++i) currentPlayer->rotate(false);
        bool turnEnded = currentPlayer->applyEffects();
        if (turnEnded) return true;
    } else if (cmd == "levelup") {
        for (int i = 0; i < mult; ++i) currentPlayer->levelUp();
    } else if (cmd == "leveldown") {
        for (int i = 0; i < mult; ++i) currentPlayer->levelDown();
    } else if (cmd == "random") {
        currentPlayer->getBoard()->restoreRandomLevel();
        return false;
    } else if (cmd == "norandom") {
        string name;
        cin >> name;

        ifstream file("files/" + name);
        if (!file) {
            cerr << "Error: Could not open "+name << endl;
            return false;
        }

        currentPlayer->getBoard()->noRandomLevel(file);
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

// Execute special effects command after turn ends. We do this by prompting the user for special effect 
//  commands until a valid one is given. Then, for each valid special effect command, we call appropriate 
//  Player methods to apply effects to 
the other player.
bool CommandCenter::executeSpecialEffectsCmd(string cmd, Player* currentPlayer, Player* otherPlayer) {
    while (true) {
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
            break;
        } else if (command == "heavy") {
            if (otherPlayer) {
                otherPlayer->addHeaviness(2);
            }
            break;
        } else if (command == "blind") {
            if (otherPlayer) {
                otherPlayer->setRenderEffect("blind");
            }
            break;
        } else {
            cout << "Invalid special effects command. Use 'force', 'heavy', or 'blind'." << endl;
        }
    }
    return true; 
}
