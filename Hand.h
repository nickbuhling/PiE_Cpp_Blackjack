/**
 * The Hand class represents a collection of playing cards (Card objects). It provides methods to manipulate and
 * interact with the hand of cards, such as adding and removing cards, emptying the hand, and retrieving information
 * about the cards in the hand. The class also has methods printing a graphical representation of the cards in the hand
 * vertically or horizontally.
 *
 * Please note that the functionality of this class depends on the Card class, and therefore needs to be included.
 */

#ifndef PIE_CPP_BLACKJACK_HAND_H
#define PIE_CPP_BLACKJACK_HAND_H

#include <string>
#include <vector>
// Including used elements from the std namespace to avoid having to write std:: a lot throughout the code
using std::string, std::vector;

#include "Card.h"

class Hand {
private:
    vector<Card> cardsInHand;
    const int MAX_CARDS_PER_PRINT_ROW = 6;

    // Defining the card symbol characters based on this online forum discussion:
    // https://www.daniweb.com/programming/software-development/threads/296311/can-i-get-the-cards-suit-symbols-as-a-character
    const char hearts = '\x03';  //♥
    const char diamonds = '\x04';  //♦
    const char clubs = '\x05';  //♣
    const char spades = '\x06';  //♠

    /**
     * This function is responsible for printing the horizontal border(s) of the graphical representations of a Card or
     * multiple cards. These are found at the top and bottom of a card. As input, it takes a vector of cards to be printed
     * and it then prints a border for every card in this vector.
     *
     * For example if 3 cards are to be printed, the output looks like this:
     * "+----------+    +----------+    +----------+"
     */
    void printHorizontalCardBorders(const vector<Card> cardsToPrint);

    /**
     * This function is responsible for printing the empty row(s) of the graphical representations of a Card or multiple
     * cards. These are found in the middle of a card. As input, it takes a vector of cards to be printed and it then
     * prints an empty row for every card in this vector.
     *
     * For example if 3 cards are to be printed, the output looks like this:
     * "|          |    |          |    |          |"
     */
    void printEmptyCardRow(const vector<Card> cardsToPrint);

    /**
     * This function is responsible for printing the value row(s) of the graphical representations of a Card or
     * multiple cards. These are found on the top left and bottom right of a card. As input, it takes a vector of cards
     * to be printed and the alignment of the value on the card. The alignment input can be "left" or "right". It then
     * prints a value row for every card in this vector, taking into consideration the desired alignment of the value on
     * the card.
     *
     * For example, 3 cards with left alignment could result in this output:
     * "| A        |    | 2        |    | 3        |"
     *
     * The same 3 cards with right alignment would result in this output:
     * "|        A |    |        2 |    |        3 |"
     */
    void printCardValueRow(const vector<Card> cardsToPrint, const string alignment);

    /**
     * This function is responsible for printing the symbol row(s) of the graphical representations of a Card or
     * multiple cards. These are found on the top left and bottom right of a card. As input, it takes a vector of cards
     * to be printed and the alignment of the symbol on the card. The alignment input can be "left" or "right". It then
     * prints a symbol row for every card in this vector, taking into consideration the desired alignment of the symbol
     * on the card.
     *
     * For example, 3 cards with left alignment could result in this output:
     * "| ♥        |    | ♠        |    | ♦        |"
     *
     * The same 3 cards with right alignment would result in this output:
     * "|        ♥ |    |        ♠ |    |        ♦ |"
     */
    void printCardSymbolRow(const vector<Card> cardsToPrint, const string alignment);

public:
    /**
     * Default constructor for an empty hand.
     */
    Hand();

    /**
     * This function adds a Card object to the hand of cards.
     */
    void addCard(const Card &cardToAdd);

    /**
     * This function adds an amount of randomly generated cards to the Hand object. It takes an integer value that
     * specifies how many cards need to be generated and added.
     */
    void addRandomCards(int amountOfCardsToAdd);

    /**
     * This function removes the lastly added Card object from a hand of cards.
     */
    void removeLastCard();

    /**
     * This function empties a Hand of cards by clearing the cardsInHand vector.
     */
    void emptyHand();

    /**
     * This function returns the amount of cards in the Hand by returning the size() of the cardsInHand vector.
     */
    int getSize();

    /**
     * This function returns the Card object stored in the cardsInHand vector at the index corresponding with the input
     * parameter "index". Note that this refers to the cards using indices (where card 1 is index 0), and not the natural
     * physical way of addressing physical cards where the first card would be called card 1.
     */
    Card getCardAtIndex(int index);

    /**
     * This function prints a hand of cards vertically, one after the other.
     */
    void printVertical();

    /**
     * This function prints a hand of cards in a horizontal layout using graphical representations of the card(s).
     *
     * The console can display a finite amount of cards next to each other before running out of space. The max amount
     * of cards will be determined by factors like the IDE and console settings. This value can be adjusted from the
     * private constant "MAX_CARDS_PER_PRINT_ROW" in this class. This function takes sections from the hand of cards that
     * don't contain more cards than this constant specifies. The rows of cards are then printed by combining 7 layers
     * of strings as defined by the sub-functions. If a full row of cards is printed, and there are more cards in the
     * hand, a new row is printed. This repeats until all cards have been printed to the console.
     *
     * Example for a hand of three cards:
     *  +----------+    +----------+    +----------+
     *  | A        |    | 2        |    | 3        |
     *  | ♥        |    | ♥        |    | ♥        |
     *  |          |    |          |    |          |
     *  |        ♥ |    |        ♥ |    |        ♥ |
     *  |        A |    |        2 |    |        3 |
     *  +----------+    +----------+    +----------+
     */
    void printHorizontal();

    /**
     * This function returns a section of a Hand of cards as a vector of Card objects. The section is defined by the
     * input integers start and end. The start and end values represent the actual positions of the cards as you would
     * naturally describe them in real life, not their index in the Hand vector. Both the cards at start and end are
     * included in the returned section. So, for example, start = 1 refers to the first card of the hand and end = 4
     * refers to the fourth card of the hand.
     *
     * As an example, getSectionOfHand(3, 6) returns a vector of Cards 3, 4, 5 and 6 of the Hand
     */
    vector<Card> getSectionOfHand(int start, int end);
};


#endif //PIE_CPP_BLACKJACK_HAND_H
