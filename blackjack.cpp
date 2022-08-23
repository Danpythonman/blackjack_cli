#include <iostream>
#include <vector>
#include <string>
#include "deck.h"

std::string generateCardString(Card & card);

int getRankFromCard(Card & card);

int main() {
    int numberOfDecks, numberOfShuffles, aceValue, dealerScore = 0, playerScore = 0;
    Deck deck;
    Card currentCard;
    std::vector<Card> dealerHand, playerHand;

    std::cout << "Welcome to Blackjack!" << std::endl;

    std::cout << "How many decks would you like to use in the deck?" << std::endl;

    std::cin >> numberOfDecks;

    std::cout << "The deck will have " << numberOfDecks * 52 << " cards." << std::endl;

    deck.new_deck(numberOfDecks);

    std::cout << "How many times would you like to shuffle the deck?" << std::endl;

    std::cin >> numberOfShuffles;

    deck.shuffle(numberOfShuffles);

    std::cout << "The deck was shuffled " << numberOfShuffles << " times." << std::endl;

    currentCard = deck.deal_card();
    playerHand.push_back(currentCard);

    std::cout << "You were dealt " << generateCardString(currentCard) << "." << std::endl;

    if (currentCard.suit == 'A') {
        std::cout << "Is this ace worth 1 or 11?" << std::endl;

        while (1) {
            std::cin >> aceValue;

            if (aceValue == 1) {
                playerScore += 1;
                break;
            } else if (aceValue == 11) {
                playerScore += 11;
                break;
            } else {
                std::cout << "Please enter 1 or 11." << std::endl;
            }
        }
    } else {
        playerScore += getRankFromCard(currentCard);
    }

    std::cout << "Your score is " << playerScore << "." << std::endl;

    currentCard = deck.deal_card();
    playerHand.push_back(currentCard);

    std::cout << "Dealer wes dealt " << generateCardString(currentCard) << "." << std::endl;

}

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