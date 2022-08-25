#include <iostream>
#include <vector>
#include <string>
#include "deck.h"

#ifdef _WIN32
    #include <windows.h>

    /**
     * Pauses execution for the specified amount of time in milliseconds.
     *
     * @param seconds The number of milliseconds to pause execution.
     */
    void sleep(unsigned int milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    /**
     * Pauses execution for the specified amount of time in milliseconds.
     *
     * @param seconds The number of milliseconds to pause execution.
     */
    void sleep(unsigned int milliseconds) {
        usleep(milliseconds * 1000);
    }
#endif

/**
 * The amount of time in milliseconds whenever we need to pause between console messages.
 */
const int sleepTime = 500;

void generateDeck(Deck & deck);

void dealCardToPlayer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

void dealFaceUpCardToDealer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

void dealFaceDownCardToDealer(Deck & deck, std::vector<Card> & DealerHand, int *playerScore);

void dealCardToDealer(Deck & deck, std::vector<Card> & playerHand, int *playerScore);

std::string generateCardString(Card & card);

int getRankFromCard(Card & card);

char getPlayerIntention();

int main() {
    int dealerScore = 0, playerScore = 0;
    Deck deck;
    std::vector<Card> dealerHand, playerHand;
    char dealerIntention, playerIntention;

    std::cout << "Welcome to Blackjack!" << std::endl;

    sleep(sleepTime);

    generateDeck(deck);

    sleep(sleepTime);

    // Deal first card to player
    dealCardToPlayer(deck, playerHand, &playerScore);

    sleep(sleepTime * 2);

    std::cout << "Your score is " << playerScore << "." << std::endl;

    sleep(sleepTime * 2);

    // Deal first card to dealer (face-up)
    dealFaceUpCardToDealer(deck, dealerHand, &dealerScore);

    sleep(sleepTime * 2);

    // Deal second card to player
    dealCardToPlayer(deck, playerHand, &playerScore);

    sleep(sleepTime * 2);

    std::cout << "Your score is " << playerScore << "." << std::endl;

    sleep(sleepTime * 2);

    // Deal second card to dealer (face-down)
    dealFaceDownCardToDealer(deck, dealerHand, &dealerScore);

    sleep(sleepTime * 2);

    // Check for initial blackjack
    if (playerScore == 21)
    {
        // If dealer also has blackjack, then it is a tie
        if (dealerScore == 21)
        {
            std::cout << "You and the dealer both have 21! Tie!";
        }
        else
        {
            // If player has a blackjack and dealer does not, then player wins
            std::cout << "You have 21 points! You win!" << std::endl;
        }
    }
    else
    {
        while (1) {
            sleep(sleepTime);

            // Player decides whether to hit or stand
            playerIntention = getPlayerIntention();

            // If player chooses hit, deal card
            if (playerIntention == 'h')
            {
                sleep(sleepTime);
                dealCardToPlayer(deck, playerHand, &playerScore);
                sleep(sleepTime);
                std::cout << "Your score is " << playerScore << "." << std::endl;
            }
            else
            {
                // If player chooses stand, stop dealing cards
                break;
            }

            // If player goes over 21 points, they lose
            if (playerScore > 21)
            {
                sleep(sleepTime);
                std::cout << "You went over 21, the dealer wins!" << std::endl;
                break;
            }

            // If player gets exactly 21 points, they win
            if (playerScore == 21)
            {
                sleep(sleepTime);
                std::cout << "You have 21 points! You win!" << std::endl;
                break;
            }
        }

        // At this point, the player has finished drawing cards, either because
        // they won or lost, or because they stood.
        //
        // If at this point the player intention is hit, then they must have won
        // or lost. If it is stand, then they are still in the game.
        if (playerIntention == 's')
        {
            sleep(sleepTime);

            // Dealer flips over their face-down card
            std::cout << "The dealer flips over their face-down card. It was a "
                << generateCardString(dealerHand.back()) << "." << std::endl;

            std::cout << "The dealer has " << dealerScore << " points." << std::endl;

            while (1) {
                // If the dealer's score is 16 or less, they must draw a card,
                // otherwise they stand.
                dealerIntention = dealerScore <= 16 ? 'h' : 's';

                if (dealerIntention == 'h')
                {
                    sleep(sleepTime);

                    dealFaceUpCardToDealer(deck, dealerHand, &dealerScore);

                    std::cout << "The dealer has " << dealerScore << " points." << std::endl;
                }
                else
                {
                    sleep(sleepTime);
                    std::cout << "The dealer is at " << dealerScore << ". The dealer stands." << std::endl;
                    break;
                }

                // If at this point the dealer goes over 21 points, they lose
                // (because if this point is reached the player is has not lost yet).
                if (dealerScore > 21)
                {
                    sleep(sleepTime);
                    std::cout << "The dealer went over 21, you win!" << std::endl;
                    break;
                }

                // If at this point the dealer gets exactly 21 points, they win
                // (because if this point is reached the player has not won yet).
                if (dealerScore == 21)
                {
                    sleep(sleepTime);
                    std::cout << "The dealer has 21 points! The dealer wins!" << std::endl;
                    break;
                }
            }

            // At this point, the dealer has finished drawing cards, either because
            // they won or lost, or because they stood.
            //
            // If at this point the dealer intention is hit, then they must have won
            // or lost. If it is stand, then they are still in the game.
            //
            // So, at this point, both the player and the dealer are under 21 points.
            if (dealerIntention == 's')
            {
                sleep(sleepTime);

                std::cout << "You have " << playerScore << " points and the dealer has "
                    << dealerScore << " points. ";

                if (playerScore > dealerScore)
                {
                    // If the player has a higher score then the dealer, the player wins
                    std::cout << "You win!";
                }
                else if (dealerScore > playerScore)
                {
                    // If the player has a higher score then the dealer, the player wins
                    std::cout << "The dealer wins!";
                }
                else
                {
                    // If the player and the dealer have the same score, then it is a tie
                    std::cout << "Tie!";
                }

                std::cout << std::endl;
            }
        }
    }

    std::cout << "Thanks for playing!" << std::endl;
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

    sleep(sleepTime);

    std::cout << "The deck will have " << numberOfDecks * 52 << " cards." << std::endl;

    sleep(sleepTime);

    deck.new_deck(numberOfDecks);

    std::cout << "How many times would you like to shuffle the deck?" << std::endl;

    std::cin >> numberOfShuffles;

    deck.shuffle(numberOfShuffles);

    sleep(sleepTime);

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
        sleep(sleepTime);

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

/**
 * Prompts the user, asking whether they would like to hit (draw another card),
 * or stand (stop drawing cards).
 *
 * User can enter 'hit' or 'h' for hit, and 'stand' or 's' for stand.
 *
 * If the user enters an invalid input, they will be prompted until they enter
 * 'hit', 'h', 'stand', or 's'.
 *
 * If the user chooses hit, 'h' will be returned. If the user chooses stand, 's'
 * will be returned.
 *
 * @return 'h' if the user chooses hit, or 's' if the user chooses stand.
 */
char getPlayerIntention() {
    std::string playerIntention;

    std::cout << "Would you like to hit or stand?" << std::endl;

    while (1) {
        std::cin >> playerIntention;

        if (playerIntention == "hit" || playerIntention == "h") {
            return 'h';
        } else if (playerIntention == "stand" || playerIntention == "s") {
            return 's';
        } else {
            std::cout << "Please enter 'hit', 'h', 'stand', or 's'." << std::endl;
        }
    }
}
