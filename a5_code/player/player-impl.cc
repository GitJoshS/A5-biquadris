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
import Board;
import Level;

using namespace std;

Player::Player() : board{make_unique<Board>()}, curScore{0}, playerId{0}, name{""} { }

Player::Player(Board* b, int score, int id, const string name)
    : board{make_unique<Board>()}, curScore{score}, playerId{id}, name{name} {}

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
    board = make_unique<Board>(); 
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
