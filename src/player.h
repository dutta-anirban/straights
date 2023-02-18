#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "board.h"
#include <set>
#include <memory>
#include <string>
#include <iostream>

class Player {
    protected:
    int playerNum;
    std::string playerName;
    Board & board;
    std::vector<Card> & cards;
    std::vector<Card> & discards;
    int score = 0;

public:
    virtual ~Player() = 0;
    Player(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score);
    virtual bool play();
    virtual int discard();
    virtual void bar();
};
#endif //PLAYER_H
