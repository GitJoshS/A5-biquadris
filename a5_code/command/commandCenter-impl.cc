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

using namespace std;

vector<string> CommandCenter::loadCommandsFromFile() {
    vector<string> commands;
    ifstream file("commands.txt");
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

Command CommandCenter::processCmd(const string& cmdStr) {
    Command cmd;
    string result = findUniqueCommand(cmdStr);

    if (!result.empty()) {
        cmd.name = result;
    } else {
        cmd.name = "unknown";
    }

    return cmd;
}

void CommandCenter::executeCmd(Command* cmd) {
    if (cmd->name == "left") {
        
    } else if (cmd->name == "right") {

    } else if (cmd->name == "down") {
        
    } else if (cmd->name == "clockwise") {

    } else if (cmd->name == "counterclockwise") {

    } else if (cmd->name == "drop") {
        
    } else if (cmd->name == "levelup") {

    } else if (cmd->name == "leveldown") {
        
    } else if (cmd->name == "random") {

    } else if (cmd->name == "norandom") {

    } else if (cmd->name == "sequence") {
        // take next work after sequence as the file name
    } else if (cmd->name == "restart") {
        
    } else {
        // Handle unknown command
    }
}
