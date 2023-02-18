#include "card.h"
#include "board.h"
#include "player.h"
#include "humanPlayer.h"
#include "easyComp.h"
#include "medComp.h"
#include "hardComp.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <deque>
#include <limits>
#include <locale>
#include <codecvt>
#include <functional>
#include "inputTaker.h"
#include <unistd.h>

bool strEquals(std::string const& A, std::string const& B) {
    if(A.size() != B.size()) return false;
    for(size_t i = 0; i < A.size(); i++)
        if(std::tolower(A[i]) != std::tolower(B[i]))
            return false;
    return true;
}

bool inpCheck(std::vector<std::string> const& A, std::string const& B) {
    for (size_t i = 0; i < A.size(); i++) {
        if (strEquals(A[i], B))
            return true;
    }
    return false;
}

void printer(const std::string& A, const std::string & type) {
    int len = A.size();

    // HEADERS
    if (type == "header") {
        std::cout << "╔";
        for (int i = 0; i < len+6; i++) {
            std::cout << "═";
        }
        std::cout << "╗\n║ ◊ " << A <<  " ◊ ║\n╚";
        for (int i = 0; i < len+6; i++) {
            std::cout << "═";
        }
        std::cout << "╝\n";
    }

    //SUB-HEADERS
    else if (type == "sub") {
        std::cout << "\n    ┌";
        for (int i = 0; i < len+6; i++) {
            std::cout << "─";
        }
        std::cout << "┐\n    │ ○ " << A <<  " ○ │\n    └";
        for (int i = 0; i < len+6; i++) {
            std::cout << "─";
        }
        std::cout << "┘\n";
    }

    // PROMPTS
    else if (type == "?") {
        std::cout << "╭";
        for (int i = 0; i < len+4; i++) {
            std::cout << "─";
        }
        std::cout << "╮\n│ » " << A << " │\n╰";
        for (int i = 0; i < len+4; i++) {
            std::cout << "─";
        }
        std::cout << "╯\n";\
    }

    // ALERT
    else if (type == "!") {
        std::cout << "┌";
        for (int i = 0; i < len+4; i++) {
            std::cout << "─";
        }
        std::cout << "┐\n│ ҉ " << A << " │\n└";
        for (int i = 0; i < len+4; i++) {
            std::cout << "─";
        }
        std::cout << "┘\n";\
    }

    // MINI TITLE
    else if (type == "mini") {
        std::cout << "╭";
        for (int i = 0; i < len+2; i++) {
            std::cout << "─";
        }
        std::cout << "╮\n│ " << A <<  " │\n╰";
        for (int i = 0; i < len+2; i++) {
            std::cout << "─";
        }
        std::cout << "╯\n";
    }

    return;
}

void printCardVec(std::vector<Card> const &deck, std::wstring const &s, bool cardmode) {
    int i = 0, j = 0, row = 0, sum = 0;
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string ss = converter.to_bytes(s);
    if (deck.empty()) {
        std::cout << "\n╭";
        for (size_t i = 0; i < s.length()+9; i++) {
            std::cout << "─";
        }
        std::cout << "╮\n│ " << ss << " » NONE │\n╰";
        for (size_t i = 0; i < s.length()+9; i++) {
            std::cout << "─";
        }
        std::cout << "╯\n";
    } else if (!cardmode) {
        if (ss != "") {
            printer(ss, "sub");
        }
        for (Card s : deck) {
            ++i;
            std::cout << s;
            if (i % 13 == 0) {
                std::cout << "\n";
            } else {
                std::cout << ' ';
            }
        }
        if (i < 13) {
            std::cout << "\n";
        }
    } else {
        j = deck.size();
        while (j > 0) {
            row = (j > 13)? 13:j;
            j -= 13;
            int slen = s.length();
            for (size_t i = 0; i < slen+8; i++) {
                std::cout << " ";
            }
            for (int d = 0; d < row; ++d) {
                std::cout << "_____    ";
            }
            std::cout << "\n╭";
            for (size_t i = 0; i < slen+4; i++) {
                std::cout << "─";
            }
            std::cout << "╮ ";
            for (int d = 0; d < row; ++d) {
                if ((deck.at(d+sum)).getRank() == Rank::T) {
                    std::cout << "│10   │  ";
                } else {
                    std::cout << "│" << rank_to_string((deck.at(d+sum)).getRank()) << "    │  ";
                }
                //std::cout << "|     |  ";
            }
            std::cout << "\n│ " << ss << " » │";
            for (int d = 0; d < row; ++d) {
                std::cout << " │  ";
                if ((deck.at(d+sum)).getSuit() == Suit::C) {
                    std::cout << "♣  │ ";
                } else if ((deck.at(d+sum)).getSuit() == Suit::D) {
                    std::cout << "♦  │ ";
                } else if ((deck.at(d+sum)).getSuit() == Suit::H) {
                    std::cout << "♥  │ ";
                } else {
                    std::cout << "♠  │ ";
                }
            }
            std::cout << "\n╰";
            for (size_t i = 0; i < slen+4; i++) {
                std::cout << "─";
            }
            std::cout << "╯ ";
            for (int d = 0; d < row; ++d) {
                std::cout << "│___";
                if ((deck.at(d+sum)).getRank() == Rank::T) {
                    std::cout << "10│  ";
                } else {
                    std::cout << "_" << rank_to_string((deck.at(d+sum)).getRank()) << "│  ";
                }
            }
            std::cout << "\n";
            sum += row;
        }   
    }
    std::cout << "\n";
}

int has7S(std::vector<Card> const playerCards[], const int numOfPlayers) {
    for (int i = 0; i < numOfPlayers; i++) {
        for (auto j : playerCards[i]) {
            if (j.getSuit() == Suit::S && j.getRank() == Rank::SEVEN) {
                return i;
            }
        }
    }
    return -1;
}

int getScore(std::vector<Card> discards) {
    int score = 0;
    for (auto i : discards) {
        score += static_cast<int>(i.getRank());
    }
    return score;
}

bool gameOver(int prevScore[], const int maxScore, const int numOfPlayers) {
    for (int i = 0; i < numOfPlayers; ++i) {
        if (prevScore[i] >= maxScore) {
            return true;
        }
    }
    return false;
}

void printHelp() {
    printer("OBJECTIVE", "header");
    std::cout << "Straights is a four-player game. The objective is to get the fewest number of points among the players.\n"
                 "The game ends when one player accumulates 80 points or more, and the player with the lowest score is\n"
                 "declared the winner. If the lowest score is a tie, then all players with that score win.\n\n";
    printer("THE DECK", "header");
    std::cout << "Straights uses a standard 52-card deck, without the jokers. Each player is dealt 13 cards at the\n"
                 "beginning of each round. In this game, the Ace is considered to be the lowest card in each suit (rank\n"
                 "of 1), while the King is the highest (rank of 13). A Jack has a rank of 11, while the Queen has a rank\n"
                 "of 12. The rank of all other cards is their numeric value e.g. 2 has a rank of 2.\n\n";
    printer("GAMEPLAY", "header");
    printer("LEGAL PLAYS", "sub");
    std::cout << "Immediately following the deal, the player with the 7 of spades goes first.\n"
                 "This player must play the 7 of spades in the centre of the table. After the 7 of spades, the players\n"
                 "take turns to play cards on the table. At this point, the players must play cards that constitute legal\n"
                 "plays. The following cards are legal:\n\n"
                 "҉ A 7 of any suit. This card starts a new pile on the table.\n\n"
                 "҉ A card with the same suit and adjacent rank (2A card has adjacent rank if its face value is one more\n"
                 "  or one less than the rank of card under consideration. The King and Ace of a suit are not considered\n"
                 "  to be adjacent ranks to each other) as another card that has already been played.\n\n"
                 "It must be played on the pile of the appropriate suit. (Note that the “pile” is spread across the table,\n"
                 "so that play can proceed at either end). For example, if the 7 of spades is the only card on the table,\n"
                 "then the legal plays are: the 7 of diamonds, the 7 of hearts, the 7 of clubs, the 8 of spades, and the\n"
                 "6 of spades. Once the 8 of spades is played, the next legal plays are: the 9 of spades, the 6 of spades,\n"
                 "the 7 of diamonds, the 7 of hearts, and the 7 of clubs.\n";
    printer("DISCARDS", "sub");
    std::cout << "When a player has no legal plays, they must then choose a card in their hand, and place it face down\n"
                 "in front of them. This is a discard. Note that if a player has at least one legal play in their hand,\n"
                 "then they must make a legal play; they may not discard in this case.\n\n";
    printer("SCORING", "header");
    std::cout << "The round ends when all the cards have either been played or discarded. For each player, their score\n"
                 "for the round is the sum of all the ranks of the player's discards. Jacks, Queens, and Kings count as\n"
                 "11, 12, and 13 points, respectively. For example, if a player discarded an Ace, a Six, and a King,\n"
                 "the number of points would be 1 + 6 + 13 = 20. Each player's game score is of the sum of their scores\n"
                 "in each round. If no player has accumulated 80 or more points at the end of a round, then the deck is\n"
                 "reshuffled and another round begins.\n\n";
                 /*"╔══════════╗\n"
                 "║ COMMANDS ║\n"
                 "╚══════════╝\n\n"
                 "play <card>                       plays the card. The card must be of the format <rank><suit>. Example: play QC\n"
                 "discard <card>                    discards the card. The card must be of the format <rank><suit>. Example: discard 7D\n"
                 "deck                              shows how the deck was shuffled. WARNING: This shows you the cards of all the players.\n"
                 "cardmode <on/off>                 turns the enhanced Card View feature on or off. Example: cardmode on\n"
                 "change <player #> <difficulty>    changes the Difficulty mode of a Computer Player. Example: charge 3 e\n"
                 "                                  If Player3 is a Computer Player, its Difficulty will change to an Easy Computer Player level.\n"
                 "ragequit                          hands over your cards to a computer (Medium Difficulty) to play for you.\n"
                 "quit                              terminates the game immediately. A second confirmaton will be required.\n"
                 "help                              shows the rules, objectives, and command guide for the game.\n"*/
    printer("ACTIONS", "header");
    std::cout << "҉ [PLAY] (followed by a card)-----plays the card. The card must be of the format <rank><suit>. Example: 1C for Ace of Clubs\n"
                 "҉ [DISCARD] (followed by a card)--discards the card. The card must be of the format <rank><suit>. Example: TH for Ten of Spades\n"
                 "҉ [DECK]--------------------------shows the shuffled deck for the current round. WARNING: This shows you everyone's cards.\n"
                 "҉ [CARDMODE]----------------------turns the enhanced Card View feature on or off.\n"
                 "҉ [RAGEQUIT]----------------------hands over your cards to a Computer Player with Medium Difficulty to play for you.\n"
                 "҉ [QUIT]--------------------------terminates the game. A second prompt is provided before exiting.\n"
                 "҉ [HELP]--------------------------shows the rules, objectives, and action guide for the game.\n\n";
}

void exit(std::vector<std::string> const & ynType) {
    printer("Are you sure you want to quit the game? (y/n)", "?");
    std::string isSure = inputTaker<std::string>([&ynType](std::string const& inp){
        return inpCheck(ynType, inp);
    }, "⇨ Please enter y for YES and n for NO.");
    if (strEquals(isSure, "y") || strEquals(isSure, "yes")) {
        printer("Exiting Game ... Shut down complete.", "!");
        exit(0);
    } else {
        printer("Resuming Game ...", "!");
        return;
    }
}

void gameLoop(unsigned seed) {
    // INITIALISING RELEVANT VARIABLES
    std::vector<Card> deck; // main deck
    const int numOfPlayers = 4; // number of players
    std::vector<Card> playerCards[numOfPlayers]; // array of sets of cards in the hands of every player
    std::vector<Card> playerDiscards[numOfPlayers]; // array of sets of discards of every player
    std::vector<std::unique_ptr<Player>> players; // vector of unique pointers to players
    std::vector<Card> legals;
    std::string command = ""; // stores command
    std::string hc; // stores player mode input
    std::vector<std::string> playerNames; // player names
    int prevScore[numOfPlayers]; // accumulation of previous round scores
    for (int i = 0; i < numOfPlayers; ++i) { // initialise to 0
        prevScore[i] = 0;
    }
    int turns = 13; // number of turns every round
    std::string ch[4]; // stores player mode
    int maxScore = 0; // score at game ends
    int min = std::numeric_limits<int>::max(); // to store the least score in the game
    Board board; // main game board initialisation
    int round = 0; // round counter
    int currPlayer = 0; // keeps track of the current player
    std::string mode = ""; // to store computer player mode
    int temp = 0; // temporary int variable to carry out transfers
    int winners = 0;
    int tempWinners = 0;
    std::string cardmode = "";
    bool cardview = true;
    int numLegal = 0;
    std::string compPlayer = "";
    std::string toMode = "";
    // int compNum = -1;
    std::vector<std::string> diffType = {"e", "easy", "m", "medium", "h", "hard"};
    std::vector<std::string> commType = {"play", "discard", "deck", "cardmode", "change", "ragequit", "quit", "help"};
    std::vector<std::string> ynType = {"y", "yes", "n", "no"};

    // FILLING UP DECK WITH CARDS IN ORDER
    for (int i = 0; i < numOfPlayers; ++i) {
        for (int j = 1; j < 14; ++j) {
            deck.push_back(Card(static_cast<Suit>(i), static_cast<Rank>(j)));
        }
    }

    // SETTING UP PLAYERS (HUMAN/COMPUTER)
    for (int i = 0; i < numOfPlayers; i++) {
        playerNames.emplace_back("Robot "+std::to_string(i+1));
    }
    std::cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
    std::cout <<   "║                               WELCOME TO                              ║\n";
    std::cout <<   "║        ░▒▓█▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄ STRAIGHTS ▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█▓▒░        ║\n";
    std::cout <<   "║                       THE FOUR-PLAYER CARD GAME                       ║\n";
    std::cout <<   "╚═══════════════════════════════════════════════════════════════════════╝\n\n";
    printHelp();
    printer("LET'S SET UP THE PLAYERS!", "header");
    for (int i = 0; i < numOfPlayers; ) {
        std::cout << "\n";
        printer("Is Player"+std::to_string(i + 1)+" a human (h) or a computer (c)?", "?");
        //std::cout << "\nIs Player" << (i + 1) << " a human (h) or a computer (c)?\n";
        hc = inputTaker<std::string>([](std::string const& hc) {
            return strEquals(hc, "h") || strEquals(hc, "c") || strEquals(hc, "quit");
        }, "⇨ Let's set up the players correctly! Enter 'h' for human or 'c' for computer.\n TIP: Type 'h' or 'c' in the Input box below and press Enter.\n");
        ch[i] = hc;
        if (hc == "h") {
            printer("What's your name? Please don't use any spaces! Only the first connected name would be taken!", "?");
            playerNames[i] = std::move(inputTaker<std::string>(
                [](std::string const& hc) { return true; }, "⇨ Invalid input! Expected a string."));
            players.emplace_back(std::make_unique<HumanPlayer>(i, playerNames[i], board, playerCards[i], playerDiscards[i], 0));
            printer("Player "+std::to_string(i+1)+" registered as a Human Player. Welcome, "+playerNames[i]+"!", "!");
            i++;
        }
        else if (hc == "c") {
            printer("Select computer player difficulty: EASY(e)  MEDIUM(m)  HARD(h). Enter your choice below.", "?");
            mode = std::move(inputTaker<std::string>(
                [&diffType](std::string const& mode) { 
                    return inpCheck(diffType, mode); },
                    "⇨ Invalid input! Please enter one of: e, m, h."));
            std::string selected;
            if (strEquals(mode, "e") || strEquals(mode, "easy"))  {
                players.emplace_back(std::make_unique<EasyComp>(i, playerNames[i], board, playerCards[i], playerDiscards[i], 0));
                selected = "Easy";
            } else if (strEquals(mode, "m") || strEquals(mode, "medium")) {
                players.emplace_back(std::make_unique<MedComp>(i, playerNames[i], board, playerCards[i], playerDiscards[i], 0));
                selected = "Medium";
            } else {
                players.emplace_back(std::make_unique<HardComp>(i, playerNames[i], board, playerCards[i], playerDiscards[i], 0));
                selected = "Hard";
            }
            printer("Player "+std::to_string(i+1)+" registered as a Computer Player in "+selected+" Mode! Beep boop.", "!");
            i++;
        } 
        else if (hc == "quit") {
            exit(ynType);
        }
    }
    std::cout << "\n";
    printer("LET'S SET THE POINTS THRESHOLD!", "header");
    std::cout << "╭────────────────────────────────────────────────────────────────────────────────────────────╮\n"
                 "│ NOTE: A regular game of straights has » 80 « set as the minimum points to finish the game. │\n"
                 "│ TIP: It must be more than 1. A lower threshold will make the game shorter, and vice-versa. │\n"
                 "│ » Setting it as » 1 « will guarantee a one-round game! What would you like it to be?       │\n"
                 "╰────────────────────────────────────────────────────────────────────────────────────────────╯\n\n";
    maxScore = inputTaker<int>([](int x){
        return x >= 1;
    }, "⇨ Invalid input! Chosen threshold should be more than one (>= 1).\nTIP: Put a number in the Input box below and press Enter.\n");
    printer("The minimum points required to finish this session has been set to » "+std::to_string(maxScore), " « !");

    // GAME PLAY
    while (!gameOver(prevScore, maxScore, numOfPlayers)) {
        
        // LAST ROUND ENDS -- NEW ROUND SET UP
        if (turns == 13) {
            std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

            // INITIALISING A MAIN PUBLIC BOARD
            for (int i = 0; i < 4; ++i) {
                board.moves.limit[i][0] = 7;
                board.moves.limit[i][1] = 7;
            }
            for (int i = 0; i < numOfPlayers; ++i) {
                playerCards[i].clear();
            }
            board.clearBoard();

            // DEALING THE CARDS TO PLAYERS
            for (int i = 0; i < numOfPlayers; ++i) {
                for (int j = 0; j < 13; ++j) {
                    playerCards[i].emplace_back(deck[13 * i + j]);
                }
            }

            // SETTING CURRENT PLAYER TO THE ONE WITH 7S
            int player7S = has7S(playerCards, numOfPlayers);
            currPlayer = player7S;
            if (round != 0) {
                std::cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
                std::cout <<   "║          ▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄ SCORE BOARD ▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀            ║\n";
                std::cout <<   "╚═══════════════════════════════════════════════════════════════════════╝\n\n";
                for (int i = 0; i < numOfPlayers; ++i) {
                    std::cout << "\n┌──────────────────────────────────────────────────────────────────┐\n";
                    std::cout <<   "│                            ↓ PLAYER " << (i+1) << " ↓                          │\n";
                    std::cout <<   "└──────────────────────────────────────────────────────────────────┘\n";
                    printer("Name: "+playerNames[i], "!");
                    if (playerDiscards[i].size() == 0) {
                        printer("Discarded Cards: NONE", "!");
                    } else {
                        //printer("Discarded Cards:", "!");
                        printCardVec(playerDiscards[i], L"DISCARDED CARDS", cardview);
                    }
                    temp = getScore(playerDiscards[i]);
                    printer("Score: "+std::to_string(prevScore[i])+" + "+std::to_string(temp)+" = "+std::to_string(temp + prevScore[i]), "!");
                    prevScore[i] += temp;
                    playerDiscards[i].clear();
                }
                std::cout << "\n───────────────────────────────────────────────────────────────────\n";
                if (gameOver(prevScore, maxScore, numOfPlayers)) {
                    break;
                }
            }
            round++;
            turns = 0;
            printer("The winning threshold hasn't been met yet! Setting up new deck and table . . .", "!");
            printer("                                   ROUND "+std::to_string(round)+"                                   ", "header");
        }

        // BOARD
        printer("CARDS ON THE TABLE", "header");

        // CLUBS
        std::deque<Card> tempDQ = board.getClubs();
        std::vector<Card> temp = {tempDQ.begin(), tempDQ.end()};
        std::string tempStr = "";
        if (temp.empty()) {
            printCardVec(temp, L"♣ CLUBS ♣", cardview);
        } else {
            if (cardview) {
                printCardVec(temp, L"♣ CLUBS ♣", cardview);
            } else {
                for (auto x : temp) {
                    tempStr += " "+rank_to_string(x.getRank());
                }
                printer("♣ CLUBS ♣ :"+tempStr, "mini");
            }
        }

        // DIAMONDS
        tempDQ = board.getDiamonds();
        temp = {tempDQ.begin(), tempDQ.end()};
        tempStr = "";
        if (temp.empty()) {
            printCardVec(temp, L"♦ DIAMONDS ♦", cardview);
        } else {
            if (cardview) {
                printCardVec(temp, L"♦ DIAMONDS ♦", cardview);
            } else {
                for (auto x : temp) {
                    tempStr += " "+rank_to_string(x.getRank());
                }
                printer("♦ DIAMONDS ♦ :"+tempStr, "mini");
            }
        }

        // HEARTS
        tempDQ = board.getHearts();
        temp = {tempDQ.begin(), tempDQ.end()};
        tempStr = "";
        if (temp.empty()) {
            printCardVec(temp, L"♥ HEARTS ♥", cardview);
        } else {
            if (cardview) {
                printCardVec(temp, L"♥ HEARTS ♥", cardview);
            } else {
                for (auto x : temp) {
                    tempStr += " "+rank_to_string(x.getRank());
                }
                printer("♥ HEARTS ♥ :"+tempStr, "mini");
            }
        }

        // SPADES
        tempDQ = board.getSpades();
        temp = {tempDQ.begin(), tempDQ.end()};
        tempStr = "";
        if (temp.empty()) {
            printCardVec(temp, L"♠ SPADES ♠", cardview);
            std::cout << "\n";
        } else {
            if (cardview) {
                printCardVec(temp, L"♠ SPADES ♠", cardview);
            } else {
                for (auto x : temp) {
                    tempStr += " "+rank_to_string(x.getRank());
                }
                printer("♠ SPADES ♠ :"+tempStr, "mini");
            }
        }
        printer("It is "+playerNames[currPlayer]+" (Player "+std::to_string(currPlayer+1)+")'s turn.", "!");
        printCardVec(playerCards[currPlayer], L"YOUR HAND", cardview);
        for (auto x : playerCards[currPlayer]) {
            if (board.validMove(x)) {
                numLegal++;
                legals.emplace_back(x);
            }
        }
        if (numLegal == 0) {
            printer("LEGAL PLAYS: NONE! You must discard.", "!");
        } else {
            printCardVec(legals, L"LEGAL PLAYS", cardview);
            legals.clear();
        }
        
        // HUMAN PLAYER HANDLE
        if (ch[currPlayer] == "h") {
            bool didPlay = false;
            int didDiscard = -1;
            while(true) {
                command = std::move(inputTaker<std::string>(
                    [&commType](std::string const& command) { 
                        return inpCheck(commType, command); },
                        "⇨ Invalid action! Please perform a valid action."));
                
                // PRINT SHUFFLED DECK
                if (strEquals(command, "deck")) {
                    printer("This will show you everyone's cards! Are you sure you want to see it? (y/n)", "?");
                    std::string isSure = inputTaker<std::string>([&ynType](std::string const& inp){
                        return inpCheck(ynType, inp);
                    }, "⇨ Please enter y for YES and n for NO.");
                    if (strEquals(isSure, "y") || strEquals(isSure, "yes")) {
                        printer("SHUFFLED DECK FOR THIS ROUND", "sub");
                        printCardVec(deck, L"", cardview);
                    } else {
                        printer("Deck not shown. Resuming Game ...", "!");
                    }  
                }

                // QUIT / TERMINATE GAME
                else if (strEquals(command, "quit")) {
                    exit(ynType);
                }

                // RAGEQUIT OPTION   
                else if (command == "ragequit") {
                    std::unique_ptr<Player> p = std::make_unique<MedComp>(currPlayer, playerNames[currPlayer], board, playerCards[currPlayer], playerDiscards[currPlayer], getScore(playerDiscards[currPlayer]));
                    players[currPlayer] = std::move(p);
                    ch[currPlayer] = "c";
                    printer("Handing over "+playerNames[currPlayer]+" (Player "+std::to_string(currPlayer+1)+")'s cards to a computer . . . Ragequit successful.", "!");
                    break;
                }

                // CHANGE CARD VIEW MODE
                else if (strEquals(command, "cardmode")) {
                    cardview = !cardview;
                    if (cardview) {
                        printer("Card View Mode has been activated.", "!");
                    } else {
                        printer("Card View Mode has been deactivated.", "!");
                    }
                } 
                
                // PRINT COMMAND HELP
                else if (strEquals(command, "help")) {
                    printHelp();
                }

                // CHANGE COMPUTER DIFFICULTY
                /*else if (command == "change") {
                    compNum = inputTaker<int>([&ch](int x){
                        return x >= 1 && x <= 4 && ch[x-1] == "c";
                    }, "Invalid input! Please enter a valid computer player!");
                    toMode = inputTaker<std::string>([&diffType](std::string const& toMode){
                        return inpCheck(diffType, toMode);
                    }, "Invalid input! Expected a difficulty that is one of: e, m, h.");

                    if (strEquals(toMode, "h") || strEquals(toMode, "hard")) {
                        players[compNum-1] = std::move(std::make_unique<HardComp>(compNum-1, playerNames[compNum-1], board, playerCards[compNum -1], playerDiscards[compNum-1], getScore(playerDiscards[compNum-1])));
                    } else if (strEquals(toMode, "e") || strEquals(toMode, "easy")) {
                        players[compNum-1] = std::move(std::make_unique<EasyComp>(compNum-1, playerNames[compNum-1], board, playerCards[compNum-1], playerDiscards[compNum-1], getScore(playerDiscards[compNum-1])));
                    } else if (strEquals(toMode, "m") || strEquals(toMode, "medium")) {
                        players[compNum-1] = std::move(std::make_unique<MedComp>(compNum-1, playerNames[compNum-1], board, playerCards[compNum-1], playerDiscards[compNum-1], getScore(playerDiscards[compNum-1])));
                    }
                    std::cout << "Player" << (compNum-1) << " is now playing in " << toMode << "-mode.\n";
                }*/

                // PLAY OPTION
                else if (strEquals(command, "play")) {
                    printer("PLAY button pressed. Enter a legal card in the Input box below and press Enter to play.", "!");
                    didPlay = players[currPlayer]->play();
                    if (!didPlay) {

                    }
                } 
                
                // DISCARD ACTION
                else if (strEquals(command, "discard")) {
                    didDiscard = players[currPlayer]->discard();
                    if (didDiscard == 1) {
                        printer("YOU HAVE A LEGAL PLAY! You must play it!", "!");
                    } else if (didDiscard == 2) {
                        printer("INVALID CARD ENTERED! Try again!", "!");
                    } else if (didDiscard == 3) {
                        printer("Please try again with a card selected from your hand!", "!");
                    }
                }

                // INCREMENT TURN AFTER PLAYED
                if (didPlay || didDiscard==0) {
                    currPlayer++;
                    if (currPlayer == 4) {
                        turns++;
                    }
                    currPlayer = currPlayer % 4;
                    break;
                }
            }
        }
        
        // COMPUTER PLAYER HANDLE
        else if (ch[currPlayer] == "c") {
            players[currPlayer]->play();
            currPlayer++;
            if (currPlayer == 4) {
                    turns++;
            }
            currPlayer = currPlayer % 4;
        }
        std::cout << "\n";
    }

    // FINDING THE LOWEST SCORE
    for (int i = 0; i < numOfPlayers; ++i) {
        if (prevScore[i] < min) {
            min = prevScore[i];
            winners = 1;
        } else if (prevScore[i] == min) {
            winners++;
        }
    }

    // DECLARING THE WINNER
    printer("CONGRATULATIONS", "header");
    tempWinners = winners;
    std::string winnerNames = "";
    for (int i = 0; i < numOfPlayers; ++i) {
        if (prevScore[i] == min) {
            winnerNames += playerNames[i];
            tempWinners--;
            if (tempWinners > 1) {
                winnerNames += ", ";
            } else if (tempWinners == 1) {
                winnerNames += " and ";
            }
        }
    }
    winnerNames += (winners > 1)? " win!" : " wins!";
    printer(winnerNames, "mini");
    if (winners > 1) {
        printer("It was a "+std::to_string(winners)+"-way tie!", "!");
    }
    std::cout << "\nThanks for playing " << playerNames[0] << ", " << playerNames[1] << ", " << playerNames[2] << ", and " << playerNames[3] << "! <3\n\n";
    printer("GAME OVER", "header");
    std::cout << "\n";
}

#ifndef WASM
int main(int argc, char **argv) {
    // SHUFFLING THE DECK WITH A SEED
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (argc > 1) {
        try {
            seed = std::stoi(std::string{argv[1]});
        }
        catch (std::invalid_argument &e) {
            std::cerr << e.what() << "\n";
            return 1;
        }
        catch (std::out_of_range &e) {
            std::cerr << e.what() << "\n";
            return -1;
        }
    }

    gameLoop(seed);
}
#endif
