#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
class Card {
public:
    std::string suit;
    std::string number;
    int value;
    int pokervalue;
    Card();
    Card(std::string s, std::string num, int val);
    Card(std::string s, std::string num, int val, int pval);
    void showCard();
};

Card::Card() {

}

Card::Card(const std::string s, const std::string num, int val) :suit(s), number(num), value(val) {

}
Card::Card(const std::string s, const std::string num, int val, int pval) : suit(s), number(num), value(val), pokervalue(pval) {

}
class Deck :public Card {
    std::vector<Card>* deckOfCards;
    const std::string SUITS[4] = { "Clubs", "Hearts", "Spades", "Diamonds" };
    const std::string TYPE[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    const int VALUE[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
    const int POKERVALUE[13] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
public:
    Deck();
    void show();
    void shuffle();
    int blackjack();
    int poker();
    ~Deck();

};

//may be thinking that all cards have the same pval
Deck::Deck() {
    deckOfCards = new std::vector<Card>();
    deckOfCards->reserve(52);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 13; ++j)
            deckOfCards->emplace_back(Card(SUITS[i], TYPE[j], VALUE[j], POKERVALUE[j]));
}

void Deck::show() {
    std::string showCard("");
    auto it = deckOfCards->begin();
    while (it != deckOfCards->end()) {
        showCard.append((it->number));
        showCard.append(" of ");
        showCard.append((it->suit));
        showCard.append("\n");
        showCard.append(" Value: ");
        showCard.append(std::to_string(it->value));
        showCard.append("\n");
        it = std::next(it);
    }
    std::cout << showCard << std::endl;
}

void Card::showCard() {
    std::string showCard("");
    showCard.append((this->number));
    showCard.append(" of ");
    showCard.append((this->suit));
    showCard.append("\n");
    showCard.append(" Value: ");
    showCard.append(std::to_string(this->value));
    showCard.append("\n");
    std::cout << showCard << std::endl;

}

//ace equalling 1 when you hit and it would put you over 21 if it was 11 is not implemented yet do that in the future.
int Deck::blackjack() {
    std::string choice = "";
    bool running = true;
    bool hitting = true;
    Card playerHand[7] = { Card(), Card(), Card(), Card(), Card(), Card(), Card() };
    Card opponentHand[7] = { Card(), Card(), Card(), Card(), Card(), Card(), Card() };
    int playerHandIndex = 2;
    int opponentHandIndex = 2;
    int playerHandValue = 0;
    int opponentHandValue = 0;
    auto it = deckOfCards->begin();
    for (int i = 0; i < 2; i++) {
        playerHand[i].suit = it->suit;
        playerHand[i].number = it->number;
        playerHand[i].value = it->value;
        it = std::next(it);
    }
    for (int i = 0; i < 2; i++) {
        opponentHand[i].suit = it->suit;
        opponentHand[i].number = it->number;
        opponentHand[i].value = it->value;
        it = std::next(it);
    }
    while (running) {
        while (hitting) {
            playerHandValue = 0;
            opponentHandValue = 0;
            std::cout << "Player Hand is: \n ";
            for (int i = 0; i < sizeof(playerHand) / sizeof(playerHand[0]); i++) {
                if (playerHand[i].suit.length() == 0) {
                    continue;
                }

                else {
                    playerHand[i].showCard();
                    playerHandValue += playerHand[i].value;
                }
            }
            std::cout << "\nOpponents Hand is: \n ";
            for (int i = 0; i < sizeof(opponentHand) / sizeof(opponentHand[0]); i++) {
                if (opponentHand[i].suit.length() == 0) {
                    continue;
                }

                else {
                    opponentHand[i].showCard();
                    opponentHandValue += opponentHand[i].value;
                }
            }
            if (opponentHandValue == 21 && playerHandValue == 21) {
                std::cout << "You both got 21. Tie. \n";
                return 0;
            }
            else if (playerHandValue == 21) {
                std::cout << "You got to 21 first. You win! \n";
                return 1;
            }
            else if (opponentHandValue == 21) {
                std::cout << "They got to 21 first. You lose. \n";
                return -1;
            }
            std::cout << "Do you want to Hit or Stop? \n 1 = Hit, 2 = Stop \n";
            std::cin >> choice;
            if (choice == "1") {
                playerHand[playerHandIndex].suit = it->suit;
                playerHand[playerHandIndex].number = it->number;
                playerHand[playerHandIndex].value = it->value;
                playerHandValue += playerHand[playerHandIndex].value;
                it = std::next(it);
                playerHandIndex += 1;
            }
            else if (choice == "2") {
                hitting = false;
            }
            else {
                std::cout << "Error. Response not recognized.";
            }
            if (playerHandValue > 21) {
                std::cout << "You went over 21. You lose. \n";
                return -1;
            }
            int safeValue = 21 - opponentHandValue;
            int values[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
            int numSafe = 0;
            for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
                if (values[i] <= safeValue) {
                    numSafe++;
                }
            }
            // chanceHit was automatically rounding up or down
            double chanceHit = (double(numSafe) / 13) * (100);
            std::cout << "AI chance to roll is: " << chanceHit << "\n";
            if (rand() % 100 < chanceHit) {
                std::cout << "AI IS ROLLING \n";
                opponentHand[opponentHandIndex].suit = it->suit;
                opponentHand[opponentHandIndex].number = it->number;
                opponentHand[opponentHandIndex].value = it->value;
                opponentHandValue += opponentHand[opponentHandIndex].value;
                it = std::next(it);
                opponentHandIndex += 1;
            }
            else {
                std::cout << "The AI has chosen to pass. \n";
            }
            if (opponentHandValue > 21) {
                std::cout << "\nOpponents Hand was: \n ";
                for (int i = 0; i < sizeof(opponentHand) / sizeof(opponentHand[0]); i++) {
                    if (opponentHand[i].suit.length() == 0) {
                        continue;
                    }
                    else {
                        opponentHand[i].showCard();
                        opponentHandValue += opponentHand[i].value;
                    }
                }
                std::cout << "They went over 21. You win! \n";
                return 1;
            }
        }
        if (playerHandValue > opponentHandValue) {
            std::cout << "You win!!! \n";
            return 1;
        }
        else if (playerHandValue < opponentHandValue) {
            std::cout << "You lost. \n";
            return -1;
        }
        else {
            return 0;
        }
    }
    return 0;
}


void insertionSort(Card hand[], int n)
{
    int i, j;
    Card key;
    for (i = 1; i < n; i++)
    {
        key = hand[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && hand[j].value > key.value)
        {
            hand[j + 1] = hand[j];
            j = j - 1;
        }
        hand[j + 1] = key;
    }
}

int Deck::poker() {
    Card playerHand[5] = { Card(), Card(), Card(), Card(), Card() };
    Card opponentHand[5] = { Card(), Card(), Card(), Card(), Card() };
    Card placeholder = Card();
    bool sorting = true;
    int playerCardValues[5] = { 0, 0, 0, 0, 0 };
    int opponentCardValues[5] = { 0, 0, 0, 0, 0 };
    int playerHandRanking = 0;
    int opponentHandRanking = 0;
    int playerHighCard = 0;
    int opponentHighCard = 0;
    int playerHandValue = 0;
    int opponentHandValue = 0;
    int playerSize = sizeof(playerCardValues) / sizeof(playerCardValues[0]);
    int opponentSize = sizeof(opponentCardValues) / sizeof(opponentCardValues[0]);
    auto it = deckOfCards->begin();
    //sort cards as they are added to hand?

    for (int i = 0; i < 5; i++) {
        playerHand[i].suit = it->suit;
        playerHand[i].number = it->number;
        playerHand[i].value = it->value;
        playerHand[i].pokervalue = it->pokervalue;
        playerCardValues[i] = playerHand[i].value;
        it = std::next(it);
    }
    for (int i = 0; i < 5; i++) {
        opponentHand[i].suit = it->suit;
        opponentHand[i].number = it->number;
        opponentHand[i].value = it->value;
        opponentHand[i].pokervalue = it->pokervalue;
        opponentCardValues[i] = opponentHand[i].value;
        it = std::next(it);
    }
    insertionSort(playerHand, 5);
    insertionSort(opponentHand, 5);
    // std::sort(playerCardValues, playerCardValues + playerSize); 
    // std::sort(opponentCardValues, opponentCardValues + opponentSize); 
    std::cout << "Player Hand is: \n ";
    for (int i = 0; i < sizeof(playerHand) / sizeof(playerHand[0]); i++) {
        if (playerHand[i].suit.length() == 0) {
            continue;
        }

        else {
            playerHand[i].showCard();
            playerHandValue += playerHand[i].pokervalue;
        }
    }
    std::cout << "\nOpponents Hand is: \n ";
    for (int i = 0; i < sizeof(opponentHand) / sizeof(opponentHand[0]); i++) {
        if (opponentHand[i].suit.length() == 0) {
            continue;
        }

        else {
            opponentHand[i].showCard();
            opponentHandValue += opponentHand[i].pokervalue;
        }
    }
    //if you want to cheat
    playerHand[4] = Card("Hearts", "Ace", 11, 14);
    playerHand[3] = Card("Clubs","Nine",11, 9);
    playerHand[2] = Card("Diamonds", "Six", 5, 6);
    playerHand[1] = Card("Hearts", "Four", 11, 4);
    playerHand[0] = Card("Spades","Two",11, 2);
    opponentHand[4] = Card("Hearts", "Ace", 11, 14);
    opponentHand[3] = Card("Clubs", "Nine", 11, 9);
    opponentHand[2] = Card("Diamonds", "Six", 5, 6);
    opponentHand[1] = Card("Hearts", "Four", 11, 4);
    opponentHand[0] = Card("Spades", "Two", 11, 2);

    if (playerHand[0].number == "Ten" && 
        playerHand[1].number == "Jack" && 
        playerHand[2].number == "Queen" && 
        playerHand[3].number == "King" && 
        playerHand[4].number == "Ace" && 
        playerHand[0].suit == playerHand[1].suit && 
        playerHand[1].suit == playerHand[2].suit && 
        playerHand[2].suit == playerHand[3].suit && 
        playerHand[3].suit == playerHand[4].suit) {
        playerHandRanking = 1;
        std::cout << "ROYAL FLUSH!!!!\n";
    }
    else if ((playerHand[0].pokervalue == (playerHand[1].pokervalue - 1) && 
        playerHand[1].pokervalue == (playerHand[2].pokervalue - 1) && 
        playerHand[2].pokervalue == (playerHand[3].pokervalue - 1) && 
        playerHand[3].pokervalue == (playerHand[4].pokervalue - 1)) || 
       (playerHand[0].number == "Two" &&
        playerHand[1].number == "Three" &&
        playerHand[2].number == "Four" &&
        playerHand[3].number == "Five" &&
        playerHand[4].number == "Ace") &&
        playerHand[0].suit == playerHand[1].suit &&
        playerHand[1].suit == playerHand[2].suit && 
        playerHand[2].suit == playerHand[3].suit && 
        playerHand[3].suit == playerHand[4].suit){
        playerHandRanking = 2;
        std::cout << "Straight Flush!!!\n";
    }
    else if ((playerHand[0].pokervalue == playerHand[1].pokervalue && 
        playerHand[1].pokervalue == playerHand[2].pokervalue && 
        playerHand[2].pokervalue == playerHand[3].pokervalue) || 
       (playerHand[1].pokervalue == playerHand[2].pokervalue &&
        playerHand[2].pokervalue == playerHand[3].pokervalue &&
        playerHand[3].pokervalue == playerHand[4].pokervalue)){
        playerHandRanking = 3;
        std::cout << "Four of a Kind!!!\n";
    }
    else if (playerHand[0].pokervalue == playerHand[1].pokervalue &&
        playerHand[1].pokervalue == playerHand[2].pokervalue && 
        playerHand[3].pokervalue == playerHand[4].pokervalue || 
      ((playerHand[0].pokervalue == playerHand[1].pokervalue &&
        playerHand[2].pokervalue == playerHand[3].pokervalue) && 
        playerHand[3].pokervalue == playerHand[4].pokervalue)){
        playerHandRanking = 4;
        std::cout << "Full House!!!\n";
    }
    else if (playerHand[0].suit == playerHand[1].suit &&
        playerHand[1].suit == playerHand[2].suit &&
        playerHand[2].suit == playerHand[3].suit &&
        playerHand[3].suit == playerHand[4].suit) {
        playerHandRanking = 5;
        std::cout << "Flush!!!\n";
    }
    else if ((playerHand[0].pokervalue == (playerHand[1].pokervalue - 1) &&
        playerHand[1].pokervalue == (playerHand[2].pokervalue - 1) &&
        playerHand[2].pokervalue == (playerHand[3].pokervalue - 1) &&
        playerHand[3].pokervalue == (playerHand[4].pokervalue - 1)) ||
       (playerHand[0].number == "Two" &&
        playerHand[1].number == "Three" &&
        playerHand[2].number == "Four" &&
        playerHand[3].number == "Five" &&
        playerHand[4].number == "Ace")){
        playerHandRanking = 6;
        std::cout << "Straight!!!\n";
    }
    else if (playerHand[0].pokervalue == playerHand[1].pokervalue &&
        playerHand[1].pokervalue == playerHand[2].pokervalue ||
        ((playerHand[2].pokervalue == playerHand[3].pokervalue) &&
        playerHand[3].pokervalue == playerHand[4].pokervalue) ||
        ((playerHand[1].pokervalue == playerHand[2].pokervalue) &&
        playerHand[2].pokervalue == playerHand[3].pokervalue)){
        playerHandRanking = 7;
        std::cout << "Three of a Kind!!!\n";
    }
    else if (playerHand[0].pokervalue == playerHand[1].pokervalue &&
        playerHand[2].pokervalue == playerHand[3].pokervalue ||
        ((playerHand[1].pokervalue == playerHand[2].pokervalue) &&
        playerHand[3].pokervalue == playerHand[4].pokervalue) ||
        ((playerHand[0].pokervalue == playerHand[1].pokervalue && playerHand[3].pokervalue == playerHand[4].pokervalue))){
        playerHandRanking = 8;
        std::cout << "Two Pair!!!\n";
    }
    else if (playerHand[0].pokervalue == playerHand[1].pokervalue ||
        ((playerHand[1].pokervalue == playerHand[2].pokervalue) ||
        ((playerHand[2].pokervalue == playerHand[3].pokervalue) ||
        playerHand[3].pokervalue == playerHand[4].pokervalue))){
        playerHandRanking = 9;
        std::cout << "One Pair!!!\n";
    }
    else {
        playerHandRanking = 10;
        playerHighCard = playerHand[4].pokervalue;
        std::cout << "High Card!!!\n";

    }

    if (opponentHand[0].number == "Ten" &&
        opponentHand[1].number == "Jack" &&
        opponentHand[2].number == "Queen" &&
        opponentHand[3].number == "King" &&
        opponentHand[4].number == "Ace" &&
        opponentHand[0].suit == opponentHand[1].suit &&
        opponentHand[1].suit == opponentHand[2].suit &&
        opponentHand[2].suit == opponentHand[3].suit &&
        opponentHand[3].suit == opponentHand[4].suit) {
        opponentHandRanking = 1;
        std::cout << "Opponent got ROYAL FLUSH!!!!\n";
    }
    else if ((opponentHand[0].pokervalue == (opponentHand[1].pokervalue - 1) &&
        opponentHand[1].pokervalue == (opponentHand[2].pokervalue - 1) &&
        opponentHand[2].pokervalue == (opponentHand[3].pokervalue - 1) &&
        opponentHand[3].pokervalue == (opponentHand[4].pokervalue - 1)) ||
       (opponentHand[0].number == "Two" &&
        opponentHand[1].number == "Three" &&
        opponentHand[2].number == "Four" &&
        opponentHand[3].number == "Five" &&
        opponentHand[4].number == "Ace") &&
        opponentHand[0].suit == opponentHand[1].suit &&
        opponentHand[1].suit == opponentHand[2].suit &&
        opponentHand[2].suit == opponentHand[3].suit &&
        opponentHand[3].suit == opponentHand[4].suit) {
        opponentHandRanking = 2;
        std::cout << "Opponent got Straight Flush!!!\n";
    }
    else if ((opponentHand[0].pokervalue == opponentHand[1].pokervalue &&
        opponentHand[1].pokervalue == opponentHand[2].pokervalue &&
        opponentHand[2].pokervalue == opponentHand[3].pokervalue) ||
       (opponentHand[1].pokervalue == opponentHand[2].pokervalue &&
        opponentHand[2].pokervalue == opponentHand[3].pokervalue &&
        opponentHand[3].pokervalue == opponentHand[4].pokervalue)) {
        opponentHandRanking = 3;
        std::cout << "Opponent got Four of a Kind!!!\n";
    }
    else if (opponentHand[0].pokervalue == opponentHand[1].pokervalue &&
        opponentHand[1].pokervalue == opponentHand[2].pokervalue &&
        opponentHand[3].pokervalue == opponentHand[4].pokervalue ||
      ((opponentHand[0].pokervalue == opponentHand[1].pokervalue &&
        opponentHand[2].pokervalue == opponentHand[3].pokervalue) &&
        opponentHand[3].pokervalue == opponentHand[4].pokervalue)) {
        opponentHandRanking = 4;
        std::cout << "Opponent got Full House!!!\n";
    }
    else if (opponentHand[0].suit == opponentHand[1].suit &&
        opponentHand[1].suit == opponentHand[2].suit &&
        opponentHand[2].suit == opponentHand[3].suit &&
        opponentHand[3].suit == opponentHand[4].suit) {
        opponentHandRanking = 5;
        std::cout << "Opponent got Flush!!!\n";
    }
    else if ((opponentHand[0].pokervalue == (opponentHand[1].pokervalue - 1) &&
        opponentHand[1].pokervalue == (opponentHand[2].pokervalue - 1) &&
        opponentHand[2].pokervalue == (opponentHand[3].pokervalue - 1) &&
        opponentHand[3].pokervalue == (opponentHand[4].pokervalue - 1)) ||
       (opponentHand[0].number == "Two" &&
        opponentHand[1].number == "Three" &&
        opponentHand[2].number == "Four" &&
        opponentHand[3].number == "Five" &&
        opponentHand[4].number == "Ace")) {
        opponentHandRanking = 6;
        std::cout << "Opponent got Straight!!!\n";
    }
    else if (opponentHand[0].pokervalue == opponentHand[1].pokervalue &&
        opponentHand[1].pokervalue == opponentHand[2].pokervalue ||
      ((opponentHand[2].pokervalue == opponentHand[3].pokervalue) &&
        opponentHand[3].pokervalue == opponentHand[4].pokervalue) ||
      ((opponentHand[1].pokervalue == opponentHand[2].pokervalue) &&
        opponentHand[2].pokervalue == opponentHand[3].pokervalue)) {
        opponentHandRanking = 7;
        std::cout << "Opponent got Three of a Kind!!!\n";
    }
    else if (opponentHand[0].pokervalue == opponentHand[1].pokervalue &&
        opponentHand[2].pokervalue == opponentHand[3].pokervalue ||
      ((opponentHand[1].pokervalue == opponentHand[2].pokervalue) &&
        opponentHand[3].pokervalue == opponentHand[4].pokervalue) ||
      ((opponentHand[0].pokervalue == opponentHand[1].pokervalue && opponentHand[3].pokervalue == opponentHand[4].pokervalue))) {
        opponentHandRanking = 8;
        std::cout << "Opponent got Two Pair!!!\n";
    }
    else if (opponentHand[0].pokervalue == opponentHand[1].pokervalue ||
      ((opponentHand[1].pokervalue == opponentHand[2].pokervalue) ||
      ((opponentHand[2].pokervalue == opponentHand[3].pokervalue) ||
        opponentHand[3].pokervalue == opponentHand[4].pokervalue))) {
        opponentHandRanking = 9;
        std::cout << "Opponent got One Pair!!!\n";
    }
    else {
        opponentHandRanking = 10;
        opponentHighCard = opponentHand[4].pokervalue;
        std::cout << "Opponent got High Card!!!\n";

    }

    if (playerHandRanking < opponentHandRanking) {
        return 1;
    }
    else if (playerHandRanking > opponentHandRanking) {
        return -1;
    }
    else {
        if (playerHandRanking == 10 && opponentHandRanking == 10) {
            if (playerHand[4].pokervalue > opponentHand[4].pokervalue) {
                return 1;
            }
            else if (playerHand[4].pokervalue < opponentHand[4].pokervalue) {
                return -1;
            }
            else {
                return 0;
            }
        }
        else if (playerHandValue > opponentHandValue) {
            return 1;
        }
        else if (opponentHandValue > playerHandValue) {
            return -1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

void Deck::shuffle() {
    srand(time(NULL));
    std::random_shuffle(deckOfCards->begin(), deckOfCards->end());
}

Deck::~Deck() {
    delete deckOfCards;
}







int main() {
    srand(time(NULL));
    bool running = true;
    std::string response1 = "", diceoption2 = "", response2 = "";
    int playerroll = 0, dicesize = 4, players = 0, opposingroll = 0;
    int playerbal = 30, bet = 0;
    while (running) {
        std::cout << "Welcome to our Casino. \n Balance: " << playerbal << "\n 1. Dice Games \n 2. Card Games \n";
        std::cin >> response1;
        if (response1 == "1") {
            std::cout << "How many opposing players. \n";
            std::cin >> players;
            std::cout << "How many dice. \n";
            std::cin >> diceoption2;
            std::cout << "What size of die. \n";
            std::cin >> dicesize;
            std::cout << "Size of your bet. \n";
            std::cin >> bet;
            if (players <= 0 || dicesize <= 1 || bet <= 0 || bet > playerbal) {
                std::cout << "Invalid response. \n";
                continue;
            }
            playerbal -= bet;
            std::cout << "The game has started! \n";
            playerroll = rand() % dicesize;
            for (int i = 0; i < players; i++) {
                opposingroll = rand() % dicesize;
                if (opposingroll > playerroll) {
                    std::cout << "You lost \n";
                    continue;
                }
            }
            std::cout << "You won! \n";
            playerbal += (bet * players);
        }
        if (response1 == "2") {
            Deck d;
            d.shuffle();
            std::cout << "Which game would you like to play? \n 1. Blackjack \n 2. Poker \n";
            std::cin >> response2;
            if (response2 == "1") {
                std::cout << "Size of your bet. \n";
                std::cin >> bet;
                if (bet <= 0 || bet > playerbal) {
                    std::cout << "Invalid response. \n";
                    continue;
                }
                playerbal -= bet;
                std::cout << "The game has started! \n";
                int result = d.blackjack();
                if (result == -1) {
                    std::cout << "You lost your bet. \n";
                    continue;
                }
                else if (result == 1) {
                    std::cout << "You won!. \n";
                    playerbal += (bet * 2);
                    continue;
                }
                else if (result == 0) {
                    std::cout << "You tied. \n";
                    playerbal += (bet);
                    continue;
                }
            }
            if (response2 == "2") {
                std::cout << "Size of your bet. \n";
                std::cin >> bet;
                if (bet <= 0 || bet > playerbal) {
                    std::cout << "Invalid response. \n";
                    continue;
                }
                playerbal -= bet;
                std::cout << "The game has started! \n";
                int result = d.poker();
                if (result == -1) {
                    std::cout << "You lost your bet. \n";
                    continue;
                }
                else if (result == 1) {
                    std::cout << "You won!. \n";
                    playerbal += (bet * 2);
                    continue;
                }
                else if (result == 0) {
                    std::cout << "You tied. \n";
                    playerbal += (bet);
                    continue;
                }
                continue;
            }
            else if (response2 != "1" || response2 != "2") {
                std::cout << "Input not recognized. \n";
                continue;
            }
        }
    }
}
