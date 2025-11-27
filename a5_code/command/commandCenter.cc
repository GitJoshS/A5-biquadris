/* 
Filename: commandCenter.cc 
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Game class, which manages the overall game state,
*/

export module CommandCenter;    

// import Command;
import <string>;
import <vector>;

export class Game; // NEED TO DOUBLE CHECK, I THINK THIS MAKES IT OK????

using namespace std;

export class CommandCenter {
    Game* game; 

    vector<string> commandList; 
    // will probably change to:
    // vector<sting> commandList;

    vector<string> loadCommandsFromFile();
    string findUniqueCommand(const string &input);
    
    public:
        CommandCenter(Game* g);

        string processCmd(string cmd);
        // Command processCmd(const std::string& cmdStr);
        
        void executeCmd(string cmd);
        // void executeCmd(Command* cmd);
};
