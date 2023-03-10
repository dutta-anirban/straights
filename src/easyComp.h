#ifndef _EASYCOMP_H_
#define _EASYCOMP_H_
#include "player.h"

class EasyComp : public Player {
    public:
    EasyComp(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score);
    bool play() override;
    int discard() override;  
};

#endif //_EASYCOMP_H_
