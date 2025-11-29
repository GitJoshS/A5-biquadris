/* 
Filename: graphicDisplay-impl.cc 
Author: Josh, Taim and Linh
Date: 2024-11-28
Last Edited: 2024-06-28

Description:
This file contains the implementation of the GraphicDisplay class, which provides a graphical display for the game.
*/

module GraphicDisplay;

import <iostream>;
import <string>;
import <memory>;
import <climits>;
import Player;
import Board;
import Level;
import Block;
import xwindow;

using namespace std;

/*
Constructor that initializes the GraphicDisplay with a list of players. Note, we need to 
use static_cast to convert size_t to int for Xwindow dimensions.
*/
GraphicDisplay::GraphicDisplay(vector<Player*> players) 
    : Display{players},
       window{
         static_cast<int>(players.size() * (players[0]->getBoard()->getWidth() * cellSize) + (players.size() - 1) * boardSpacing) + 44, // width
         static_cast<int>(topMargin + players[0]->getBoard()->getHeight() * cellSize + bottomMargin) // length
        } {}

/*
render works by clearing the window, then rendering each player's info, board, and next block preview
*/
void GraphicDisplay::render(int highscore) {
    int width = players[0]->getBoard()->getWidth();
    int height = players[0]->getBoard()->getHeight();
    int playerCount = players.size();
    
    // Clear window by filling with white
    window.fillRectangle(0, 0, 2000, 2000, Xwindow::White);
    
    string strHighscore = "Highscore: " + to_string(highscore);
    int vertical = 20;
    window.drawString(extraMargin, vertical, strHighscore);

    // Render each player's display
    for (int player = 0; player < playerCount; ++player) {
        int xOffset = player * (width * cellSize + boardSpacing) + extraMargin;

        // Render player info (name, level, score)
        renderPlayerInfo(player, xOffset);
        
        // Render the game board
        renderBoard(player, xOffset, topMargin);
        
        // Render next block preview
        int boardBottomY = topMargin + height * cellSize + extraMargin;
        renderNextBlock(player, xOffset, boardBottomY);
    }

    window.flush();
}

/*
renderPlayerInfo works by drawing the player's name, level, and score at specified offsets.
Then it uses the Xwindow's drawString method to render the text.
*/
void GraphicDisplay::renderPlayerInfo(int playerIndex, int xOffset) {
    // Draw player name
    int vertical = 20;
    string name = players[playerIndex]->getName();
    window.drawString(xOffset, 2*vertical, name);
    
    // Draw level
    int level = players[playerIndex]->getBoard()->getLevel()->getLevel();
    string levelText = "Level: " + to_string(level);
    window.drawString(xOffset, 3*vertical, levelText);
    
    // Draw score
    int score = players[playerIndex]->getCurScore();
    string scoreText = "Score: " + to_string(score);
    window.drawString(xOffset, 4*vertical, scoreText);
}

/*
renderBoard works by iterating through each cell in the player's board grid.
Then it draws filled rectangles for blocks and empty cells, applying special effects like "blind" as needed.
*/
void GraphicDisplay::renderBoard(int playerIndex, int xOffset, int yOffset) {
    int width = players[playerIndex]->getBoard()->getWidth();
    int height = players[playerIndex]->getBoard()->getHeight();
    const vector<vector<shared_ptr<Block>>>& grid = players[playerIndex]->getBoard()->getGrid();
    
    // Draw board border (black outline)
    // All integers just shift the box to give a little visual leeway
    window.fillRectangle(xOffset - 2, yOffset - 2, 
                        width * cellSize + 4, height * cellSize + 4, 
                        Xwindow::Black);
    
    // Draw each cell
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int x = xOffset + col * cellSize;
            int y = yOffset + row * cellSize;
            
            // Check for blind effect
            if (players[playerIndex]->getRenderEffect() == "blind" && 
                (row <= 11 && row >= 2) && (col <= 8 && col >= 2)) {
                // Draw question mark area (gray)
                window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
                window.drawString(x + 8, y + 18, "?");
            } else if (grid[col][row]) {
                // Draw filled block with appropriate color
                char type = grid[col][row]->getType();
                int color = getColorForBlock(type);
                window.fillRectangle(x, y, cellSize, cellSize, color);
                
                // Draw cell border for definition
                window.fillRectangle(x, y, cellSize, 1, Xwindow::Black);
                window.fillRectangle(x, y, 1, cellSize, Xwindow::Black);
            } else {
                // Empty cell - white
                window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
            }
        }
    }
}

/*
renderNextBlock works by first drawing the "Next:" label.
Then it retrieves the next block's default position and type, normalizes the coordinates,
and draws the block preview in the designated area.
*/
void GraphicDisplay::renderNextBlock(int playerIndex, int xOffset, int yOffset) {
    
    // Draw "Next:" label
    window.drawString(xOffset, yOffset, "Next:");
    
    // Get next block info
    shared_ptr<Block> nextBlock = players[playerIndex]->getBoard()->getNextBlock();
    vector<pair<int,int>> nextDefPos = nextBlock->getPosition();
    char type = nextBlock->getType();
    
    // Find minimum row to normalize coordinates
    int minRow = INT_MAX;
    int minCol = INT_MAX;
    for (const auto& coord : nextDefPos) {
        minRow = min(minRow, coord.second);
        minCol = min(minCol, coord.first);
    }
    
    // Draw next block preview
    int previewY = yOffset + 20;
    int color = getColorForBlock(type);
    
    for (const auto& coord : nextDefPos) {
        int normalizedCol = coord.first - minCol;
        int normalizedRow = coord.second - minRow;
        
        int x = xOffset + normalizedCol * cellSize;
        int y = previewY + normalizedRow * cellSize;
        
        window.fillRectangle(x, y, cellSize, cellSize, color);
        // Draw cell border
        window.fillRectangle(x, y, cellSize, 1, Xwindow::Black);
        window.fillRectangle(x, y, 1, cellSize, Xwindow::Black);
    }
}

/*
This method maps block types to specific X11 colors for rendering.
*/
int GraphicDisplay::getColorForBlock(char type) {
    // Map block types to X11 colors
    switch(type) {
        case 'I': return Xwindow::Cyan;
        case 'J': return Xwindow::Blue;
        case 'L': return Xwindow::Orange;
        case 'O': return Xwindow::Yellow;
        case 'S': return Xwindow::Green;
        case 'Z': return Xwindow::Red;
        case 'T': return Xwindow::Magenta;
        case '*': return Xwindow::Brown;  // Special block
        default: return Xwindow::White;
    }
}
