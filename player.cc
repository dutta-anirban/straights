#include "player.h"
#include "card.h"

Player::Player(int playerNum, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
playerNum{playerNum}, board{board}, cards{cards}, discards{discards}, score{score} {}

Player::~Player() {}

bool Player::play() {
    return true;
}

bool Player::discard() {
    return true;
}
