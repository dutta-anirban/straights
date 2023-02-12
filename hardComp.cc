#include "hardComp.h"

HardComp::HardComp(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
Player(playerNum, playerName, board, cards, discards, score) {}


bool HardComp::play() {
    int max = 0;
    auto bestCard = cards.begin();
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (board.validMove(*i) && max < static_cast<int>((*i).getRank())) {
            max = static_cast<int>((*i).getRank());
            bestCard = i;
        }
    }
    if (max == 0) {
        discard();
    } else {
        std::cout << playerName << " (Player " << (playerNum+1) << ") plays " << *bestCard << "." << std::endl;
        std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
        board.play(*bestCard);
        cards.erase(bestCard);
    }
    return true;
}

bool HardComp::discard() {
    int min = 13;
    auto bestCard = cards.begin();
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (min > static_cast<int>((*i).getRank())) {
            min = static_cast<int>((*i).getRank());
            bestCard = i;
        }
    }
    std::cout << playerName << " (Player " << (playerNum+1) << ") discards " << *bestCard << "." << std::endl;
    std::cout << std::endl << "----------------------------------------------------------------------" << std::endl;
    discards.emplace_back(*bestCard);
    cards.erase(bestCard);
    return true;
}
