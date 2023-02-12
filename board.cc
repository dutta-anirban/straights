#include "board.h"

bool Board::validMove(const Moves & m, Card c) {
    int rank = static_cast<int>(c.getRank());
    int suit = static_cast<int>(c.getSuit());
    if (board[(int)Suit::S].empty()) {
        return (c.getSuit() == Suit::S && c.getRank() == Rank::SEVEN);
    } else {
        return (m.limit[suit][0] <= rank && m.limit[suit][1] >= rank);
    }
}

bool Board::validMove(Card c) {
    return validMove(validMoves(), c);
}

Board::Moves Board::validMoves() {
    Moves m;
    for (int i = 0; i < 4; i++) {
        if (board[i].empty()) {
            m.limit[i][0] = m.limit[i][1] = 7;
        } else {
            m.limit[i][0] = static_cast<int>(board[i].front().getRank()) - 1;
            m.limit[i][1] = static_cast<int>(board[i].back().getRank()) + 1;
        }
    }
    return m;
}

bool Board::play(Card card) {
    Moves m = validMoves();
    if (!(validMove(m, card))) {
        return false;
    } else {
        int rank = static_cast<int>(card.getRank());
        int suit = static_cast<int>(card.getSuit());
        if (m.limit[suit][0] == rank) {
            board[suit].push_front(card);
        } else if (m.limit[suit][1] == rank) {
            board[suit].push_back(card);
        }
        return true;
    }
}

std::deque<Card> Board::getClubs() {
    return board[static_cast<int>(Suit::C)];
}

std::deque<Card> Board::getDiamonds() {
    return board[static_cast<int>(Suit::D)];
}

std::deque<Card> Board::getHearts() {
    return board[static_cast<int>(Suit::H)];
}

std::deque<Card> Board::getSpades() {
    return board[static_cast<int>(Suit::S)];
}

void Board::clearBoard() {
    for (int i = 0; i < 4; i++) {
        board[i].clear();
    }
}
