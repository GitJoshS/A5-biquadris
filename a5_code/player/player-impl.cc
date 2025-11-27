/* 
Filename: plater-impl.cc
Author: Josh Stein
Date: 2024-11-25
Last Edited: 2024-06-26

Description:
This file contains the implementation of the Player class, which manages player state
*/

module Player;

using namespace std;

Player::Player() : board{nullptr}, curScore{0}, playerId{0}, name{""} { }

Player::Player(Board* b, int score, int id, const std::string& name)
    : board{b}, curScore{score}, playerId{id}, name{name} { }

string Player::getName() const {
    return name;
}

int Player::getCurScore() const {
    return curScore;
}

int Player::getPlayerId()const  {
    return playerId;
}

void Player::applySpecialAction() {
    
}

int Player::calculateLineScore(int linesCleared) {
    
}

int Player::calculateBlockScore(Block *b) {
    
}
