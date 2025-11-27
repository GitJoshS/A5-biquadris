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

using namespace std;

Player::Player() : board{nullptr}, curScore{0}, playerId{0}, name{""} { }

Player::Player(Board* b, int score, int id, const string& name)
    : board{b}, curScore{score}, playerId{id}, name{name} {}

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
int Player::calculateLineScore(int linesCleared) { } // need to implement
int Player::calculateBlockScore(Block *b) { } // need to implement
