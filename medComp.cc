#include "medComp.h"

MedComp::MedComp(int playerNum, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
Player(playerNum, board, cards, discards, score) {}

bool MedComp::play() {
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (board.validMove(*i)) {
            std::cout << "Player" << (playerNum+1) << " plays " << *i << "." << std::endl;
            board.play(*i);
            cards.erase(i);
            return true;
        }
    }
    discard();
    return true;
}

bool MedComp::discard() {
    std::cout << "Player" << (playerNum+1) << " discards " << cards.front() << "." << std::endl;
    discards.emplace_back(cards.front());
    cards.erase(cards.begin());
    return true;
}
