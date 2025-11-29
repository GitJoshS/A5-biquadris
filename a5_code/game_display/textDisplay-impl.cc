/* 
Filename: textDisplay-impl.cc 
Author: Josh, Taim and Linh
Date: 2024-11-25
Last Edited: 2024-06-28

Description:
This file contains the implementation of the TextDisplay class, which provides a text-based display for the game.
*/

module TextDisplay;

import <iostream>;
import <cmath>;
import <memory>;
import Player;
import Board;
import Level;
import Block;

using namespace std;

/*
General constructor that initializes the TextDisplay with a list of players.
*/
TextDisplay::TextDisplay(vector<Player*> players) : Display{players} {}

void TextDisplay::render(int highscore) {
    int width = players[0]->getBoard()->getWidth();
    int height = players[0]->getBoard()->getHeight();
    int playerCount = players.size();
    char blank = ' ';
    cout << highscore << endl;
    renderStats(width, height, playerCount, blank);
    renderBoards(width, height, playerCount, blank);
    renderNexts(width, height, playerCount, blank);
};

/* 
renders the stats section of the text display. Works by iterating through each player and printing their
name, level, and score with appropriate spacing.
*/
void TextDisplay::renderStats(int width, int height, int playerCount, char blank) {
    //Print out Names
    for (int player = 0; player < playerCount; ++player) {
        string name = players[player]->getName();
        cout << name;
        string space = string(width - name.length(), ' ');
        cout << space << boardsSpace;
    }
    cout << endl;
    // Print out level indicator for all players
    for (int player = 0; player < playerCount; ++player) {
        int level = players[player]->getBoard()->getLevel()->getLevel();
        string space = spaceGen(level);
        cout << "Level:" << space << level << boardsSpace;
    }
    cout << endl;
    // Print out score indicator for all players
    for (int player = 0; player < playerCount; ++player) {
        int score = players[player]->getCurScore();
        string space = spaceGen(score);
        cout << "Score:" << space << score << boardsSpace;
    }
    cout << endl;
};


/*
This renders the boards section of the text display. It prints the game board for each player row by row,
taking into account any special rendering effects like "blind". 
*/
void TextDisplay::renderBoards(int width, int height, int playerCount, char blank) {
    // print out top of the board horizontal line
    for (int player = 0; player < playerCount; ++player) {
        cout << string(width, '-') << boardsSpace;
    }
    cout << endl;
    // print the game board for all players row by row
    // for each row
    for (int rows = 0; rows < height; ++rows) { 
        // for each player
        for (int player = 0; player < playerCount; ++player) {
            // fetch the players active board (the grid)  
            const vector<vector<shared_ptr<Block>>>& grid = players[player]->getBoard()->getGrid();
            // for each column  
            for (int col = 0; col < width; ++col) {
                if (players[player]->getRenderEffect() == "blind" && (rows <= 11 && rows >= 2) && (col <= 8 && col >= 2)) {
                    cout << '?';
                    continue;
                }
                // gives Block*->getChar()
                if (grid[col][rows]) {
                    cout << grid[col][rows]->getType();
                } else {
                    cout << blank;
                }
            }
            // print space bewteen players boards
            cout << boardsSpace;
        }
        cout << endl;
    }
    // print out bottom of the board horizontal line
    for (int player = 0; player < playerCount; ++player) {
        cout << string(width, '-') << boardsSpace;
    }
    cout << endl;
};



/*
renderNexts renders the "Next" blocks section of the text display. It prints the next block for each player
row by row, normalizing the block's position to fit within a 4-row display area.
*/
void TextDisplay::renderNexts(int width, int height, int playerCount, char blank) {
    // print out next indicator for all players
    for (int player = 0; player < playerCount; ++player) {
        string next = "Next:";
        int spaceCount = width - next.length();
        cout << next << string(spaceCount, ' ') << boardsSpace;
    }
    cout << endl;
    // print out next block
    int defaultBlockRows = 4;
    // for each row
    for (int row = 0; row < defaultBlockRows; ++row) {
        // for each player
        for (int player = 0; player < playerCount; ++player) {
            // fetch default coords and type of next block
            shared_ptr<Block> nextBlock = players[player]->getBoard()->getNextBlock();
            vector<pair<int,int>> nextDefPos = nextBlock->getPosition();
            char type = nextBlock->getType();
            
            // Find minimum row to normalize coordinates
            int minRow = INT_MAX;
            for (const auto& coord : nextDefPos) {
                minRow = min(minRow, coord.second);
            }

            for (int col = 0; col < width; ++col) {
                // for each coordinate
                bool found = false;
                for (const pair<int, int>& coord : nextDefPos) {
                    if (coord.first == col && (coord.second - minRow) == row) {
                        cout << type;
                        found = true;
                        break;
                    }
                } 
                if (!found) cout << blank;
            }
            cout << boardsSpace;
        }
        cout << endl;
    }
};

/*
spaceGen generates a string of spaces for formatting based on the length of the given number.
*/
string TextDisplay::spaceGen(int number) {
    int charsAfterTitle = 5;
    number = abs(number);
    string strNumber = to_string(number);
    string space(charsAfterTitle - strNumber.length(), ' ');
    return space;
}
