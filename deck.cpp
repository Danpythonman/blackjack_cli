#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Card {
    char rank;
    char suit;
};

class Deck {
    std::vector<Card> deck;

public:
    void new_deck();
    void new_deck(int numberOfDecks);
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

    std::cout << deck1.to_string() << std::endl << std::endl;

    Deck deck2;

    deck2.new_deck(4);

    std::cout << deck2.to_string();

}
