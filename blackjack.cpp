#include <iostream>
#include "deck.h"

int main() {
    int numberOfDecks;
    Deck deck;

    std::cout << "Welcome to Blackjack!" << std::endl;

    std::cout << "How many decks would you like to use in the deck?"
        << std::endl;

    std::cin >> numberOfDecks;

    std::cout << "The deck will have " << numberOfDecks * 52 << " cards."
        << std::endl;

    deck.new_deck(numberOfDecks);
}
