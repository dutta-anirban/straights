#ifndef _MEDCOMP_H_
#define _MEDCOMP_H_
#include "player.h"

class MedComp : public Player {
    public:
    MedComp(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score);
    bool play() override;
    bool discard() override;  
};

#endif //_MEDCOMP_H_
