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

CommandCenter::CommandCenter(Game* g) : game{g}, commandList{loadCommandsFromFile()} {}

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

/* need to fix*/
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
    string result = findUniqueCommand(cmdStr);
    if (!result.empty()) return result;
    return "unknown";
}

void CommandCenter::executeCmd(Command* cmd) {
    Board* board = game->getCurrentPlayer()->getBoard();
    Block* active = board->getActiveBlock();

    if (cmd->name == "left") {
        for (auto& cell : newPos) cell.first -= 1;
        if (board->isValidMove(newPos)) {
            active->setPosition(newPos);
        }
    } else if (cmd->name == "right") {
        for (auto& cell : newPos) cell.first += 1;
        if (board->isValidMove(newPos)) {
            active->setPosition(newPos);
        }
    } else if (cmd->name == "down") {
        for (auto& cell : newPos) cell.second += 1;
        if (board->isValidMove(newPos)) {
            active->setPosition(newPos);
        }
    } 
    else if (cmd->name == "drop") {
        if (!active) return;

        Board* board = game->getCurrentPlayer()->getBoard();
        Player* player = game->getCurrentPlayer();

        // Move block down until it can't move further
        while (true) {
            auto newPos = active->getPosition();
            for (auto& cell : newPos) cell.second += 1;

            if (board->isValidMove(newPos)) {
                active->setPosition(newPos);
            } else {
                break;  // Block can't move further
            }
        }

        // Place the block on the board
        board->placeBlock(active);

        // Check and clear completed rows
        auto completedRows = board->checkCompletedRows();
        int linesCleared = completedRows.size();
        for (int row : completedRows) {
            board->clearRow(row);
        }

        // Update player's score based on lines cleared
        int points = player->calculateLineScore(linesCleared);
        player->incrementScore(points);

        // Update game's highscore
        game->updateHighscore(player->getCurScore());

        // Generate next block
        Block* next = board->getLevel()->generateNextBlock();
        board->setActiveBlock(next);
    }
    else if (cmd == "clockwise") {
        auto rotated = active->rotatePosition(true);
        if (board->isValidMove(rotated)) {
            active->setPosition(rotated);
        }
    } else if (cmd == "counterclockwise") {
        auto rotated = active->rotatePosition(false);
        if (board->isValidMove(rotated)) {
            active->setPosition(rotated);
        }
    } else if (cmd->name == "levelup") {
        Level* lvl = board->getLevel();
        lvl->increaseLevel();  // NEED TO IMPLEMENT FUNCTION IN BOARD
    } else if (cmd == "leveldown") {
        Level* lvl = board->getLevel();
        lvl->decreaseLevel(); // NEED TO IMPLEMENT FUNCTION IN BOARD
    } else if (cmd->name == "random") {
        // set the block generation to random
        
    } else if (cmd->name == "norandom") {
        // set the block generation to non-random

    } else if (cmd->name == "sequence") {
        // take next work after sequence as the file name

    } else if (cmd->name == "restart") {
        // reset the game state, not the players, just the boards

    } else {
        // Handle unknown command
        cout << "Unknown command: " << cmd->name << endl;
    }
}
