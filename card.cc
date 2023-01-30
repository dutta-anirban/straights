#include "card.h"

Card::Card(Suit s, Rank r): s{s}, r{r} {}

Suit Card::getSuit() const {
	return s;
}

Rank Card::getRank() const {
	return r;
}

std::string suit_to_string(Suit suit) {
   if (suit == Suit::S) {
        return "S";
    } else if (suit == Suit::C) {
        return "C";
    } else if (suit == Suit::D) {
        return "D";
    } else {
        return "H";
    }
}

std::string rank_to_string(Rank rank) {
   int iRank = static_cast<int>(rank);
   if (iRank == 1) {
       return "A";
   } else if (iRank == 10) {
       return "T";
   } else if (iRank == 11) {
       return "J";
   } else if (iRank == 12) {
       return "Q";
   } else if (iRank == 13) {
       return "K";
   } else {
       return std::to_string(iRank);
   }
}

std::string Card::getCardName() const {
    return (suit_to_string(s) + rank_to_string(r));
}

bool operator==(const Card &a, const Card &b) {
	return (a.getSuit() == b.getSuit() && a.getRank() == b.getRank());
}

int Card::getPointValue() const {
    return static_cast<int>(r);
}

bool operator<(const Card & c1, const Card & c2) {
    return ((13*(int)c1.s + (int)c1.r) < (13*(int)c2.s + (int)c2.r));
}

std::ostream &operator<<(std::ostream &out, const Card &c) {
    out << rank_to_string(c.getRank()) << suit_to_string(c.getSuit());
	return out;
}

std::istream &operator>>(std::istream &in, Card &c) {
    std::string str;
    in >> str;
    if (str.length() > 2) {
        throw std::invalid_argument("Invalid Length.");
    }
    if (str.at(0) == 'A') {
        c.r = Rank::A;
    } else if (str.at(0) == 'T') {
        c.r = Rank::T;
    } else if (str.at(0) == 'J') {
        c.r = Rank::J;
    } else if (str.at(0) == 'Q') {
        c.r = Rank::Q;
    } else if (str.at(0) == 'K') {
        c.r = Rank::K;
    } else if ((str.at(0)-'0') > 1 && (str.at(0)-'0') < 10) {
        c.r = static_cast<Rank>((str.at(0))-'0');
    } else {
        throw std::invalid_argument("Wrong Card<Rank> Syntax.");
    }
    if (str.at(1) == 'C') {
        c.s = Suit::C;
    } else if (str.at(1) == 'D') {
        c.s = Suit::D;
    } else if (str.at(1) == 'H') {
        c.s = Suit::H;
    } else if (str.at(1) == 'S') {
        c.s = Suit::S;
    } else {
        throw std::invalid_argument("Wrong Card<Suit> Syntax.");
    }
	return in;
}
