#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "deck.h"

void Deck::new_deck() {
    std::string suitString = "cdhs";
    std::string rankString = "A23456789TJQK";

    size = 52;

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

    size = numberOfDecks * 52;
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

int Deck::deck_size() {
    return size;
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
