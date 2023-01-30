#include "easyComp.h"

EasyComp::EasyComp(int playerNum, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
Player(playerNum, board, cards, discards, score) {}

bool EasyComp::play() {
    int min = 14;
    auto bestCard = cards.begin();
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (board.validMove(*i) && min > static_cast<int>((*i).getRank())) {
            min = static_cast<int>((*i).getRank());
            bestCard = i;
        }
    }
    if (min == 14) {
        discard();
    } else {
        std::cout << "Player" << (playerNum+1) << " plays " << *bestCard << "." << std::endl;
        board.play(*bestCard);
        cards.erase(bestCard);
    }
    return true;
}

bool EasyComp::discard() {
    int max = 0;
    auto bestCard = cards.begin();
    for (auto i = cards.begin(); i != cards.end(); ++i) {
        if (max < static_cast<int>((*i).getRank())) {
            max = static_cast<int>((*i).getRank());
            bestCard = i;
        }
    }
    std::cout << "Player" << (playerNum+1) << " discards " << *bestCard << "." << std::endl;
    discards.emplace_back(*bestCard);
    cards.erase(bestCard);
    return true;
}
