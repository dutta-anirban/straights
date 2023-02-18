#include "humanPlayer.h"
#include "inputTaker.h"

HumanPlayer::HumanPlayer(int playerNum, std::string playerName, Board & board, std::vector<Card> & cards, std::vector<Card> & discards, int score):
Player(playerNum, playerName, board, cards, discards, score) {}

bool HumanPlayer::play() {
    Card cardChoice;
    try {
        cardChoice = inputTaker<Card>([](Card const& ignored){ return true; }, "⇨ Error is impossible.");
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    
    if (!(board.validMove(cardChoice))) {
        return false;
    }

    auto it = find(cards.begin(), cards.end(), cardChoice);
    if (it != cards.end()) {
        std::cout << "⇨ "<< playerName << " (Player " << (playerNum+1) << ") plays " << cardChoice << ".\n\n";
        bar();
        board.play(cardChoice);
        cards.erase(it);
        return true;
    }
    else {
        return false;
    }
}

int HumanPlayer::discard() {
    // CHECKING IF LEGAL MOVES EXIST
    for (auto x : cards) {
        if (board.validMove(x)) {
            return 1;                   // ERROR 1: HAS LEGAL PLAY(S)
        }
    }

    std::cout << "\n┌─────────────────────────────────────────────────────────────────┐\n";
    std::cout <<   "│ DISCARD button pressed. Enter a card from your hand to discard! │\n";
    std::cout <<   "└─────────────────────────────────────────────────────────────────┘\n";
    Card cardChoice;
    int counter = -1;
    int index = -1;
    try {
        cardChoice = inputTaker<Card>([](Card const& ignored){ return true; }, "⇨ Error is impossible.");
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 2;                   // ERROR 2: INVALID CARD ENTRY
    }

    // CHECKING IF THE CARD IS OWNED
    for (auto x : cards) {
        counter++;
        if (x.getSuit() == cardChoice.getSuit() && x.getRank() == cardChoice.getRank()) {
            index = counter;
        }
    }

    // DISCARDING CARD
    if (index == -1) {
        return 3;                   // ERROR 3: ILLEGAL CARD SELECTED
    } else {
        std::cout << "⇨ " << playerName << " (Player " << (playerNum+1) << ") discards " << cardChoice << ".\n\n";
        bar();
        discards.emplace_back(cardChoice);
        cards.erase(cards.begin()+index);
        return 0;
    }
}
