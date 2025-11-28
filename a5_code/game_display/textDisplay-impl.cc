module TextDisplay;

import <iostream>;
import <cmath>;
import Player;
import Board;
import Level;

using namespace std;

TextDisplay::TextDisplay(vector<Player*> players) : Display{players} {}

void TextDisplay::render() {
    int width = players[0]->getBoard()->getWidth();
    int height = players[0]->getBoard()->getHeight();
    int playerCount = players.size();
    char blank = ' ';
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
            vector<vector<shared_ptr<Block>>>& grid = players[player]->getBoard()->getGrid();
            // for each column  
            for (int col = 0; col < width; ++col) {
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
    // print out next indicator for all players
    for (int player = 0; player < playerCount; ++player) {
        string next = "Next:";
        int spaceCount = width - next.length();
        cout << next << string(spaceCount, ' ') << boardsSpace;
    }
    cout << endl;
    // print out next block
    int defaultBlockRows = 2;
    // for each row
    for (int row = 0; row < defaultBlockRows; ++row) {
        // for each player
        for (int player = 0; player < playerCount; ++player) {
            // fetch default coords and type of next block
            shared_ptr<Block> nextBlock = players[player]->getBoard()->getNextBlock();
            vector<pair<int,int>> nextDefPos = nextBlock->getPosition();
            char type = nextBlock->getType();
            // for each column
            for (int col = 0; col < width; ++col) {
                // for each coordinate
                bool found = false;
                for (const pair<int, int>& coord : nextDefPos) {
                    if (coord.first == col && coord.second == row) {
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


string TextDisplay::spaceGen(int number) {
    int charsAfterTitle = 5;
    number = abs(number);
    string strNumber = to_string(number);
    string space(charsAfterTitle - strNumber.length(), ' ');
    return space;
}


// //todo should it be vector<Board*>& board OR vector<Board&>& board
// void TextDisplay::render(vector<Board*>& board, vector<int> score, vector<int> level, vector<Block*> next) {
//     int height = board[0]->height;
//     int width = board[0]->width;
//     //! Make sure that sizes are equal (they should be)
//     if (!(board.size() == score.size() && score.size() == level.size() && level.size() == next.size())) return;
//     int playerCount = board.size();
//     // Print out level indicator for all players
//     for (int player = 0; player < playerCount; ++i) {
//         string space = spaceGen(level[player]);
//         cout << "Level:" << space << level[player] << boardsSpace;
//     }
//     // Print out score indicator for all players
//     for (int player = 0; player < playerCount; ++i) {
//         string space = spaceGen(score[player]);
//         cout << "Score:" << space << score[player] << boardsSpace;
//     }
//     // print out top of the board horizontal line
//     for (int player = 0; player < playerCount; ++i) {
//         cout << string(width, '-') << boardsSpace;
//     }
//     // print the game board for all players row by row
//     // for each row
//     //todo HARD CODING NEED TO RESOLVE THIS AND MAKE MORE DYNAMIC
//     //todo ///////////////////////
//     for (int rows = 0; rows < height; ++rows) { 
//         // for each player
//         for (int player = 0; i < playerCount; ++i) {
//             // fetch the players active board (the grid)
//             vector<vector<Block*>>& grid = board[player]->grid;
//             // for each column  
//             for (int col = 0; col < width; ++i) {
//                 // gives Block*->getChar()
//                 cout << grid[rows][column]->getChar();
//             }
//             // print space bewteen players boards
//             cout << boardsSpace;
//         }
//     }
//     // print out bottom of the board horizontal line
//     for (int player = 0; player < playerCount; ++i) {
//         cout << string(width, '-') << boardsSpace;
//     }
//     // print out next indicator for all players
//     for (int player = 0; player < playerCount; ++i) {
//         string next = "Next:";
//         int spaceCount = width - next.length();
//         cout << next << string(spaceCount, ' ') << boardsSpace;
//     }
//     // print out next block
//     for (int player = 0; player < playerCount; ++i) {
//         int defaultBlockLayers = next->getDefaultLayers()/*IMPLEMENT THAT IN BLOCK*/;
//         for (int layer = 0; layer < defaultBlockLayers; ++layer) {
//             //todo Somehow print the "layer" layer of the block
//             cout << next->/*layer[layer]*/ << boardsSpace;
//         }
//     }
// };