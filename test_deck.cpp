#include <iostream>
#include "deck.h"

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

    std::cout << deck1.remaining() << " out of "
        << deck1.deck_size() << " cards remaining" << std::endl;

    Card card;

    for (int i = 0; i < 3; i ++) {
        card = deck1.deal_card();
        std::cout << card.rank << card.suit << std::endl;
        std::cout << deck1.remaining() << " out of "
            << deck1.deck_size() << " cards remaining" << std::endl;
    }

    std::cout << "----- CURRENT DECK 1 -----" << std::endl;
    std::cout << deck1.to_string() << std::endl << std::endl;
    std::cout << "----------" << std::endl;

    Deck deck2;

    deck2.new_deck(4);

    std::cout << "----- DECK 2 -----" << std::endl;
    std::cout << deck2.to_string() << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << deck2.remaining() << " out of "
        << deck2.deck_size() << " cards remaining " << std::endl;

    deck2.shuffle(10);

    std::cout << "----- SHUFFLED DECK 2 -----" << std::endl;
    std::cout << deck2.to_string() << std::endl;
    std::cout << "----------" << std::endl;
}
