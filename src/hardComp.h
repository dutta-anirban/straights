#ifndef _HARDCOMP_H_
#define _HARDCOMP_H_
#include "player.h"

class HardComp : public Player {
    public:
    HardComp(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score);
    bool play() override;
    bool discard() override;  
};

#endif //_HARDCOMP_H_
