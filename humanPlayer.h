#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include <algorithm>

class HumanPlayer : public Player {
    public:
    HumanPlayer(int playerNum, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score);
    bool play() override;
    bool discard() override;  
};

#endif //HUMANPLAYER_H
