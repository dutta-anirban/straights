#include "medComp.h"

MedComp::MedComp(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
Player(playerNum, playerName, board, cards, discards, score) {}

bool MedComp::play() {
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (board.validMove(*i)) {
            std::cout << playerName << " (Player " << (playerNum+1) << ") plays " << *i << "." << std::endl;
            std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
            board.play(*i);
            cards.erase(i);
            return true;
        }
    }
    discard();
    return true;
}

bool MedComp::discard() {
    std::cout << playerName << " (Player " << (playerNum+1) << ") discards " << cards.front() << "." << std::endl;
    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    discards.emplace_back(cards.front());
    cards.erase(cards.begin());
    return true;
}
