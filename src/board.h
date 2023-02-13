#ifndef BOARD_H
#define BOARD_H
#include "card.h"
#include <deque>
#include <memory>
#include <string>

class Board {
    private:
    std::deque<Card> board[4];
    public:
    struct Moves {
        int limit[4][2];
    } moves;
    bool validMove(const Moves & m, Card c);
    bool validMove(Card c);
    Moves validMoves();
    bool play(Card card);
    std::deque<Card> getClubs();
    std::deque<Card> getDiamonds();
    std::deque<Card> getHearts();
    std::deque<Card> getSpades();
    void clearBoard();
};

#endif //BOARD_H
