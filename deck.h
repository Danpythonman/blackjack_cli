#include <vector>
#include <string>

/**
 * Representation of a card as a struct with a member for the card's suit and
 * another for the card's rank.
 */
struct Card {
    char suit;
    char rank;
};

/**
 * A deck of cards.
 */
class Deck {
    std::vector<Card> deck;
    int size;

public:
    /**
     * Creates a new deck with 52 cards.
     */
    void new_deck();

    /**
     * Creates a deck containing multiple decks of 52 cards.
     * 
     * @param numberOfDecks The number of decks of 52 cards to include in the
     *                      deck.
     */
    void new_deck(int numberOfDecks);

    /**
     * Shuffles the deck of cards by randomly changing the order of cards in the
     * deck.
     */
    void shuffle();

    /**
     * Shuffles the deck of cards by randomly changing the order of cards in the
     * deck, and repeating this process multiple times.
     *
     * @param numberOfShuffles The number of times to shuffle through the deck,
     *                         changing the order of the cards each time.
     */
    void shuffle(int numberOfShuffles);

    /**
     * Return a card from the deck, removing it from the deck in the process.
     *
     * @return The card dealt from the deck.
     */
    const Card & deal_card();

    /**
     * Return the size of the deck (in cards) when it was created.
     *
     * @return The number of cards the deck was created with.
     */
    int deck_size();

    /**
     * Returns the number of cards remaining in the deck.
     *
     * @return The number of cards remaining in the deck.
     */
    int remaining();

    /**
     * Generates a string representation of the deck in its current state.
     * 
     * @return A representation of the deck in its current state as
     *                     a string.
     */
    std::string to_string();
};
