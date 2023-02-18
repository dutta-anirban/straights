#ifndef CARD_H
#define CARD_H

#include <ostream>
#include <istream>
#include <string>
#include <vector>
#include <iostream>

enum class Suit { C=0, D=1, H=2, S=3 };
enum class Rank { A=1, TWO=2, THREE=3, FOUR=4, FIVE=5, SIX=6, SEVEN=7, EIGHT=8, NINE=9, T=10, J=11, Q=12, K=13 };

class Card {
    Suit s;
	Rank r;
    friend std::istream &operator>>(std::istream &, Card &);
	friend std::ostream &operator<<(std::ostream &, const Card &);
	friend bool operator<(const Card & c1, const Card & c2);
	
    public:
	Card(Suit, Rank);
	Card() : s{Suit::C}, r{Rank::A} { };
	Suit getSuit() const;
	Rank getRank() const;
    std::string getCardName() const;
	int getPointValue() const;
};

std::string suit_to_string(Suit suit);
std::string rank_to_string(Rank rank);
bool operator==(const Card &, const Card &);
std::ostream &operator<<(std::ostream & out, const Card & card);
std::istream &operator>>(std::istream &in, Card &c);
bool operator<(const Card & c1, const Card & c2);

#endif
