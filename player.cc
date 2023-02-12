#include "player.h"
#include "card.h"

Player::Player(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
playerNum{playerNum}, playerName{playerName}, board{board}, cards{cards}, discards{discards}, score{score} {}

Player::~Player() {}

bool Player::play() {
    return true;
}

bool Player::discard() {
    return true;
}
