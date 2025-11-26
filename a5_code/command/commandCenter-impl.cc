/* 
Filename: commandCenter-impl.cc 
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the implementation of the CommandCenter class, which serves as the central hub for 
command processing
*/

module CommandCenter; 

using namespace std;

Command CommandCenter::processCmd(string cmdStr) {
    /*
    check which command it is and create a Command object accordingly. Must be 
    a substring match for minimal unique prefixes.
    */
    
    Command cmd;
    cmd.name = cmdStr; // Placeholder, will set actual name based on parsing
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

    } else if (cmd->name == "restart") {

    } else {
        // Handle unknown command
    }
}
