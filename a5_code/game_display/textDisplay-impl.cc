module TextDisplay;

import <iostream>;
import <cmath>;

using namespace std;

//todo should it be vector<Board*>& board OR vector<Board&>& board
void TextDisplay::render(vector<Board*>& board, vector<int> score, vector<int> level, vector<Block*> next) {
    int height = board[0]->height;
    int width = board[0]->width;
    //! Make sure that sizes are equal (they should be)
    if (!(board.size() == score.size() && score.size() == level.size() && level.size() == next.size())) return;
    int playerCount = board.size();
    // Print out level indicator for all players
    for (int player = 0; player < playerCount; ++i) {
        string space = spaceGen(level[player]);
        cout << "Level:" << space << level[player] << boardsSpace;
    }
    // Print out score indicator for all players
    for (int player = 0; player < playerCount; ++i) {
        string space = spaceGen(score[player]);
        cout << "Score:" << space << score[player] << boardsSpace;
    }
    // print out top of the board horizontal line
    for (int player = 0; player < playerCount; ++i) {
        cout << string(width, '-') << boardsSpace;
    }
    // print the game board for all players row by row
    // for each row
    //todo HARD CODING NEED TO RESOLVE THIS AND MAKE MORE DYNAMIC
    //todo ///////////////////////
    for (int rows = 0; rows < height; ++rows) { 
        // for each player
        for (int player = 0; i < playerCount; ++i) {
            // fetch the players active board (the grid)
            vector<vector<Block*>>& grid = board[player]->grid;
            // for each column  
            for (int col = 0; col < width; ++i) {
                // gives Block*->getChar()
                cout << grid[rows][column]->getChar();
            }
            // print space bewteen players boards
            cout << boardsSpace;
        }
    }
    // print out bottom of the board horizontal line
    for (int player = 0; player < playerCount; ++i) {
        cout << string(width, '-') << boardsSpace;
    }
    // print out next indicator for all players
    for (int player = 0; player < playerCount; ++i) {
        string next = "Next:";
        int spaceCount = width - next.length();
        cout << next << string(spaceCount, ' ') << boardsSpace;
    }
    // print out next block
    for (int player = 0; player < playerCount; ++i) {
        int defaultBlockLayers = next->getDefaultLayers()/*IMPLEMENT THAT IN BLOCK*/;
        for (int layer = 0; layer < defaultBlockLayers; ++layer) {
            //todo Somehow print the "layer" layer of the block
            cout << next->/*layer[layer]*/ << boardsSpace;
        }
    }
};


string TextDisplay::spaceGen(int number) {
    //! HARD CODING INVOLVED, CAN BE SOLVED IF WE SET A MINIMUM LIMIT TO BOARD WIDTH CUSTOMIZATION
    charsAfterTitle = 5;
    //! ////////////////
    score = abs(score);
    string strscore = to_string(score);
    string space(charsAfterTitle - strscore.length(), ' ');
    return space;
}
