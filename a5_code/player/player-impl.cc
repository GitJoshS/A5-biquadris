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

Player::Player() : board{make_unique<Board>(11, 18, 0, "")}, curScore{0}, playerId{0}, name{""}, sequenceFile{""}, additionalHeaviness{0} { }

Player::Player(int score, int id, string name, string sequenceFile)
    : curScore{score}, playerId{id}, name{name}, sequenceFile{sequenceFile}, additionalHeaviness{0} {
    board = make_unique<Board>(11, 18, 0, sequenceFile);
}

Board* Player::getBoard() const {
    return board.get();
}

string Player::getName() const {
    return name;
}

int Player::getCurScore() const {
    return curScore;
}

int Player::getPlayerId()const  {
    return playerId;
}

void Player::applySpecialAction() { } // will modify later

void Player::reset() {
    board = make_unique<Board>(11, 18, 0, sequenceFile);
    curScore = 0;
}

void Player::addScore(int score) {
    curScore += score;
}

bool Player::dropBlock() {
    bool turnEnded = board->drop();
    vector<int> completedRows = board->checkCompletedRows();
    
    int totalScore = 0;
    int linesCleared = completedRows.size();
    
    if (linesCleared > 0) {
        int currentLevel = board->getLevel()->getLevel();
        int lineScore = (currentLevel + linesCleared) * (currentLevel + linesCleared);
        totalScore += lineScore;
        
        for (int row : completedRows) {
            totalScore += board->clearRow(row);
        }
        
        addScore(totalScore);
    }
    
    return turnEnded;
}

bool Player::moveBlock(int x, int y) {
    return board->move(x, y);
}

void Player::rotate(bool clockwise) {
    board->rotate(clockwise);
}

void Player::levelUp() {
    int newLevel = board->getLevel()->getLevel() + 1;
    if (newLevel == 0) {
        ifstream file(sequenceFile);
        board->setLevel(levelFactory.create(0, file));
    } else {
        board->setLevel(levelFactory.create(newLevel));
    }
}

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

void Player::addHeaviness(int amount) {
    additionalHeaviness += amount;
}

void Player::resetHeaviness() {
    additionalHeaviness = 0;
}

int Player::getAdditionalHeaviness() const {
    return additionalHeaviness;
}

void Player::applyEffects() {
    // Apply heavy after every command
    int additionalHeavy = getAdditionalHeaviness();
    board->applyHeavy(additionalHeavy);
}

bool Player::hasSpecialEffects() const {
    // Check if 2 or more rows were cleared in the last drop
    vector<int> completedRows = board->checkCompletedRows();
    return completedRows.size() >= 2;
}
