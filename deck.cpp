#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

struct Card {
    char rank;
    char suit;
};

class Deck {
    std::vector<Card> deck;

public:
    void new_deck();
    void new_deck(int numberOfDecks);
    void shuffle();
    void shuffle(int numberOfShuffles);
    const Card & deal_card();
    int remaining();
    std::string to_string();
};

void Deck::new_deck() {
    std::string suitString = "cdhs";
    std::string rankString = "A23456789TJQK";

    for (char suit : suitString) {
        for (char rank : rankString) {
            deck.push_back({suit, rank});
        }
    }
}

void Deck::new_deck(int numberOfDecks) {
    for (int i = 0; i < numberOfDecks; i++) {
        new_deck();
    }
}

void Deck::shuffle() {
    int randomIndex;
    int numberOfCards = deck.size();
    Card temp;

    // Seed the random number generator
    srand((unsigned) time(nullptr));

    // Throw away the first random number because on some systems the first
    // random number may have a pattern to it.
    rand();

    for (int i = 0; i < numberOfCards; i++) {
        temp = deck[i];

        randomIndex = rand() % numberOfCards;

        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
    }
}

void Deck::shuffle(int numberOfShuffles) {
    for (int i = 0; i < numberOfShuffles; i++) {
        shuffle();
    }
}

const Card & Deck::deal_card() {
    Card & card = deck.back();

    deck.pop_back();

    return card;
}

int Deck::remaining() {
    return deck.size();
}

std::string Deck::to_string() {
    std::string deckString = "[";

    for (Card card : deck) {
        deckString.push_back(card.rank);
        deckString.push_back(card.suit);
        deckString += ", ";
    }

    // Remove trailing comma and space
    deckString.pop_back();
    deckString.pop_back();

    deckString += "]";

    return deckString;
}

int main() {

    Deck deck1;

    deck1.new_deck();

    std::cout << "----- DECK 1 -----" << std::endl;
    std::cout << deck1.to_string() << std::endl << std::endl;
    std::cout << "----------" << std::endl;

    deck1.shuffle();

    std::cout << "----- SHUFFLED DECK 1 -----" << std::endl;
    std::cout << deck1.to_string() << std::endl << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << deck1.remaining() << " cards remaining" << std::endl;

    Card card = deck1.deal_card();
    std::cout << card.rank << card.suit << std::endl;
    std::cout << deck1.remaining() << " cards remaining" << std::endl;

    card = deck1.deal_card();
    std::cout << card.rank << card.suit << std::endl;
    std::cout << deck1.remaining() << " cards remaining" << std::endl;

    card = deck1.deal_card();
    std::cout << card.rank << card.suit << std::endl;
    std::cout << deck1.remaining() << " cards remaining" << std::endl;

    std::cout << "----- CURRENT DECK 1 -----" << std::endl;
    std::cout << deck1.to_string() << std::endl << std::endl;
    std::cout << "----------" << std::endl;

    Deck deck2;

    deck2.new_deck(4);

    std::cout << "----- DECK 2 -----" << std::endl;
    std::cout << deck2.to_string();
    std::cout << "----------" << std::endl;

    deck2.shuffle(10);

    std::cout << "----- SHUFFLED DECK 2 -----" << std::endl;
    std::cout << deck2.to_string();
    std::cout << "----------" << std::endl;

}
