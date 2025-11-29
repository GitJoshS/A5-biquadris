/* 
Filename: plater-impl.cc
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Player class, which manages player state
*/

module Player;

import <string>;
import <memory>;
import <vector>;
import <fstream>;
import Board;
import Level;
import LevelFactory;

using namespace std;

/*
Inital constructor for Player class. Note, for board we intialize with a make_unique call.
*/
Player::Player(int score, int id, string name, string sequenceFile)
    : curScore{score}, playerId{id}, name{name}, sequenceFile{sequenceFile}, additionalHeaviness{0}, shouldTriggerSpecialEffects{false}, renderEffect{""} {
    board = make_unique<Board>(11, 18, 0, sequenceFile);
}

/*
Constructor for Player class with starting level. Only ran when we want to start at a level > 0
*/
Player::Player(int score, int id, string name, string sequenceFile, int startLevel)
    : curScore{score}, playerId{id}, name{name}, sequenceFile{sequenceFile}, additionalHeaviness{0}, shouldTriggerSpecialEffects{false}, renderEffect{""} {
    board = make_unique<Board>(11, 18, startLevel, sequenceFile);
}

/*
Getter for the player's board.
*/
Board* Player::getBoard() const {
    return board.get();
}

/*
Getter for the player's name.
*/
string Player::getName() const {
    return name;
}

/*
Getter for the player's current score.
*/
int Player::getCurScore() const {
    return curScore;
}

/*
Getter for the player's ID.
*/
int Player::getPlayerId()const  {
    return playerId;
}

/*
reset will reset the player's state, including the board and score.
*/
void Player::reset() {
    board = make_unique<Board>(11, 18, 0, sequenceFile);
    curScore = 0;
    renderEffect = "";
}

/*
addScore adds the specified score to the player's current score.
*/
void Player::addScore(int score) {
    curScore += score;
}

/*
dropBlock works by dropping the active block on the player's board.
Then, it checks for completed rows, calculates the score based on the number of lines cleared,
and updates the active block's position accordingly.
*/
bool Player::dropBlock() {
    bool turnEnded = board->drop();
    vector<int> completedRows = board->checkCompletedRows();
    
    int totalScore = 0;
    int linesCleared = completedRows.size();
    
    // Set special effects flag if 2+ lines cleared
    shouldTriggerSpecialEffects = (linesCleared >= 2);
    
    if (linesCleared > 0) {
        int currentLevel = board->getLevel()->getLevel();
        int lineScore = (currentLevel + linesCleared) * (currentLevel + linesCleared);
        totalScore += lineScore;
        
        for (int row : completedRows) {
            totalScore += board->clearRow(row);
        }
        
        // Update active block position after grid shift
        vector<pair<int, int>> currentPos = board->getActiveBlock()->getPosition();
        for (auto& coord : currentPos) {
            coord.second += linesCleared; // Shift down by number of cleared lines
        }
        board->getActiveBlock()->setPosition(currentPos);
        
        addScore(totalScore);
    }
    
    return turnEnded;
}

/*
moveBlock will move the active block by the specified x and y offsets on the player's board.
*/
bool Player::moveBlock(int x, int y) {
    return board->move(x, y);
}

/*
rotate will call the rotate function on the player's board to rotate the active block.
*/
void Player::rotate(bool clockwise) {
    board->rotate(clockwise);
}

/*
levelup will increase the player's board level by 1.
*/ 
void Player::levelUp() {
    int newLevel = board->getLevel()->getLevel() + 1;
    if (newLevel == 0) {
        ifstream file(sequenceFile);
        board->setLevel(levelFactory.create(0, file));
    } else {
        board->setLevel(levelFactory.create(newLevel));
    }
}

/*
lveveldown will decrease the player's board level by 1.
*/
void Player::levelDown() {
    int newLevel = board->getLevel()->getLevel() - 1;
    if (newLevel < 0) return; // Can't go below level 0
    if (newLevel == 0) {
        ifstream file(sequenceFile);
        board->setLevel(levelFactory.create(0, file));
    } else {
        board->setLevel(levelFactory.create(newLevel));
    }
}

/*
addHeaviness increases the heaviness of the player's blocks by the specified amount.
*/
void Player::addHeaviness(int amount) {
    additionalHeaviness += amount;
}

/*
resetHeaviness resets the additional heaviness to 0.
*/
void Player::resetHeaviness() {
    additionalHeaviness = 0;
}

/*
getAdditionalHeaviness returns the additional heaviness of the player's blocks.
*/
int Player::getAdditionalHeaviness() const {
    return additionalHeaviness;
}

/*
applyEffects applies any effects on the player's board, such as heaviness.
*/
bool Player::applyEffects() {
    // Apply heavy after every command
    int additionalHeavy = getAdditionalHeaviness();
    return board->applyHeavy(additionalHeavy);
}

/*
hasSpecialEffects checks if the player has any special effects active.
*/
bool Player::hasSpecialEffects() const {
    return shouldTriggerSpecialEffects;
}

/*
resetSpecialEffects resets the special effects for the player.
*/
void Player::resetSpecialEffects() {
    shouldTriggerSpecialEffects = false;
}

/*
setRenderEffect sets a render effect for the player.
*/
void Player::setRenderEffect(const string& effect) {
    renderEffect = effect;
}

/*
getRenderEffect returns the current render effect for the player.
*/
string Player::getRenderEffect() const {
    return renderEffect;
}

/*
resetRenderEffect resets the render effect for the player.
*/
void Player::resetRenderEffect() {
    renderEffect = "";
}
