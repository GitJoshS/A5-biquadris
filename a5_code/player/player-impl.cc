/* 
Filename: plater-impl.cc
Author: Josh Stein
Date: 2024-06-15
Last Edited: 2024-06-15

Description:
This file contains the implementation of the Player class, which manages player state
*/

module Player;

using namespace std;

Player::Player() : board(nullptr), curScore(0), playerId(0), playerName("") { }

Player::Player(Board* b, int score, int id, const std::string& name)
    : board(b), curScore(score), playerId(id), playerName(name) { }

int Player::getName() {
    return curScore;
}

int Player::getCurScore() {
    return curScore;
}

int Player::getPlayerId() {
    return playerId;
}

void Player::applySpecialAction() {
    
}

int Player::calculateLineScore(int linesCleared) {
    
}

int Player::calculateBlockScore(Block *b) {
    
}
