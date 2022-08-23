#include <iostream>
#include <vector>
#include <string>
#include "deck.h"

void generateDeck(Deck & deck);

void dealCardToPlayer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

void dealFaceUpCardToDealer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

void dealFaceDownCardToDealer(Deck & deck, std::vector<Card> & DealerHand, int *playerScore);

void dealCardToDealer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

std::string generateCardString(Card & card);

int getRankFromCard(Card & card);

int main() {
    int dealerScore = 0, playerScore = 0;
    Deck deck;
    std::vector<Card> dealerHand, playerHand;

    std::cout << "Welcome to Blackjack!" << std::endl;

    generateDeck(deck);

    dealCardToPlayer(deck, playerHand, &playerScore);

    std::cout << "Your score is " << playerScore << "." << std::endl;

    dealFaceUpCardToDealer(deck, dealerHand, &dealerScore);
}

/**
 * Generates a deck by populating a Deck argument with Card objects.
 *
 * If the deck already has a value, it will be overriden, and if the deck does
 * not have a value, it will be given one.
 *
 * This also uses standard input and output for prompting the user for the
 * number of decks to include in the generated deck and the number of times to
 * shuffle the deck.
 *
 * @param deck The deck to be populated with cards.
 */
void generateDeck(Deck & deck) {
    int numberOfDecks, numberOfShuffles;

    std::cout << "How many decks would you like to use in the deck?" << std::endl;

    std::cin >> numberOfDecks;

    std::cout << "The deck will have " << numberOfDecks * 52 << " cards." << std::endl;

    deck.new_deck(numberOfDecks);

    std::cout << "How many times would you like to shuffle the deck?" << std::endl;

    std::cin >> numberOfShuffles;

    deck.shuffle(numberOfShuffles);

    std::cout << "The deck was shuffled " << numberOfShuffles << " times." << std::endl;
}

/**
 * Deals a card to a player, removing a card from the deck in the process.
 *
 * The card is given to the player's hand and the player's score is increased by
 * the proper amount.
 *
 * If the card is an ace, the user will be prompted to choose whether the it is
 * worth 1 or 11 points.
 *
 * @param deck        The deck from which the card is to be drawn from.
 * @param playerHand  The player's hand to which the drawn card is to be added.
 * @param playerScore A pointer to the player's score so that it can be
 *                    increased appropriately.
 */
void dealCardToPlayer(Deck & deck, std::vector<Card> & playerHand, int *playerScore) {
    int aceValue;

    Card currentCard = deck.deal_card();
    playerHand.push_back(currentCard);

    std::cout << "You were dealt " << generateCardString(currentCard) << "." << std::endl;

    if (currentCard.suit == 'A') {
        std::cout << "Is this ace worth 1 or 11?" << std::endl;

        while (1) {
            std::cin >> aceValue;

            if (aceValue == 1) {
                *playerScore += 1;
                break;
            } else if (aceValue == 11) {
                *playerScore += 11;
                break;
            } else {
                std::cout << "Please enter 1 or 11." << std::endl;
            }
        }
    } else {
        *playerScore += getRankFromCard(currentCard);
    }
}

/**
 * Deals a card to a dealer face-up, removing a card from the deck in the process.
 *
 * Sinc the card is drawn face-up, the card's suit and rank will be printed to
 * the console.
 *
 * The card is given to the dealer's hand and the dealer's score is increased by
 * the proper amount.
 *
 * If the card is an ace, the dealer will choose the card to be worth 11 points,
 * unless it would cause the dealer's score to go over 21 points, in which case
 * the dealer chooses 1 point.
 *
 * @param deck        The deck from which the card is to be drawn from.
 * @param dealerHand  The dealer's hand to which the drawn card is to be added.
 * @param dealerScore A pointer to the dealer's score so that it can be
 *                    increased appropriately.
 */
void dealFaceUpCardToDealer(Deck & deck, std::vector<Card> & dealerHand, int *dealerScore) {
    dealCardToDealer(deck, dealerHand, dealerScore);

    std::cout << "Dealer was dealt " << generateCardString(dealerHand.back()) << "." << std::endl;
}

/**
 * Deals a card to a dealer face-down, removing a card from the deck in the process.
 *
 * Sinc the card is drawn face-down, the card's suit and rank will not be
 * printed to the console, and instead the user will just be notified that the
 * dealer has drawn a card.
 *
 * The card is given to the dealer's hand and the dealer's score is increased by
 * the proper amount.
 *
 * If the card is an ace, the dealer will choose the card to be worth 11 points,
 * unless it would cause the dealer's score to go over 21 points, in which case
 * the dealer chooses 1 point.
 *
 * @param deck        The deck from which the card is to be drawn from.
 * @param dealerHand  The dealer's hand to which the drawn card is to be added.
 * @param dealerScore A pointer to the dealer's score so that it can be
 *                    increased appropriately.
 */
void dealFaceDownCardToDealer(Deck & deck, std::vector<Card> & dealerHand, int *dealerScore) {
    dealCardToDealer(deck, dealerHand, dealerScore);

    std::cout << "Dealer was dealt a face-down card." << std::endl;
}

/**
 * Deals a card to a dealer, removing a card from the deck in the process. No
 * message is printed to the console.
 *
 * The card is given to the dealer's hand and the dealer's score is increased by
 * the proper amount.
 *
 * If the card is an ace, the dealer will choose the card to be worth 11 points,
 * unless it would cause the dealer's score to go over 21 points, in which case
 * the dealer chooses 1 point.
 *
 * @param deck        The deck from which the card is to be drawn from.
 * @param dealerHand  The dealer's hand to which the drawn card is to be added.
 * @param dealerScore A pointer to the dealer's score so that it can be
 *                    increased appropriately.
 */
void dealCardToDealer(Deck & deck, std::vector<Card> & dealerHand, int *dealerScore) {
    Card currentCard = deck.deal_card();
    dealerHand.push_back(currentCard);

    if (currentCard.suit == 'A') {
        if (*dealerScore + 11 > 21) {
            *dealerScore += 1;
        } else {
            *dealerScore += 11;
        }
    } else {
        *dealerScore += getRankFromCard(currentCard);
    }
}

/**
 * Generates a string given a card.
 *
 * The string has the format "<rank> of <suit>".
 *
 * For example, "ace of hearts".
 *
 * @param card The card for which to generate the string.
 *
 * @return The string generated from the given card.
 */
std::string generateCardString(Card & card) {
    std::string cardString;

    switch (card.rank) {
        case 'A':
            cardString += "ace";
            break;
        case '2':
            cardString += "two";
            break;
        case '3':
            cardString += "three";
            break;
        case '4':
            cardString += "four";
            break;
        case '5':
            cardString += "five";
            break;
        case '6':
            cardString += "six";
            break;
        case '7':
            cardString += "seven";
            break;
        case '8':
            cardString += "eight";
            break;
        case '9':
            cardString += "nine";
            break;
        case 'T':
            cardString += "ten";
            break;
        case 'J':
            cardString += "jack";
            break;
        case 'Q':
            cardString += "queen";
            break;
        case 'K':
            cardString += "king";
            break;
    }

    cardString += " of ";

    switch (card.suit) {
        case 'c':
            cardString += "clubs";
            break;
        case 'd':
            cardString += "diamonds";
            break;
        case 'h':
            cardString += "hearts";
            break;
        case 's':
            cardString += "spades";
            break;
    }

    return cardString;
}

/**
 * Get the rank as an integer from a card.
 *
 * Do not use this function if the card is an ace.
 *
 * If the card's rank is anywhere from 2 to 10 (inclusive), the rank returned is
 * just the rank.
 *
 * If the rank is jack, queen, or king, the rank returned is 10.
 *
 * @param card The card for which to get the rank.
 *
 * @return The rank of the given card.
 */
int getRankFromCard(Card & card) {
    int cardRank;

    switch (card.rank) {
        case '2':
            cardRank = 2;
            break;
        case '3':
            cardRank = 3;
            break;
        case '4':
            cardRank = 4;
            break;
        case '5':
            cardRank = 5;
            break;
        case '6':
            cardRank = 6;
            break;
        case '7':
            cardRank = 7;
            break;
        case '8':
            cardRank = 8;
            break;
        case '9':
            cardRank = 9;
            break;
        case 'T':
            cardRank = 10;
            break;
        case 'J':
            cardRank = 10;
            break;
        case 'Q':
            cardRank = 10;
            break;
        case 'K':
            cardRank = 10;
            break;
    }

    return cardRank;
}
