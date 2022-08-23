#include <vector>
#include <string>

struct Card {
    char rank;
    char suit;
};

class Deck {
    std::vector<Card> deck;
    int size;

public:
    void new_deck();
    void new_deck(int numberOfDecks);
    void shuffle();
    void shuffle(int numberOfShuffles);
    const Card & deal_card();
    int deck_size();
    int remaining();
    std::string to_string();
};
