/**
 * The Hand class represents a collection of playing cards (Card objects). It provides methods to manipulate and
 * interact with the hand of cards, such as adding and removing cards, emptying the hand, and retrieving information
 * about the cards in the hand. The class also has methods printing a graphical representation of the cards in the hand
 * vertically or horizontally.
 *
 * Please note that the functionality of this class depends on the Card class, and therefore needs to be included.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// Including used elements from the std namespace to avoid having to write std:: a lot throughout the code
using std::cout, std::endl, std::cerr, std::cin, std::vector, std::string, std::left, std::right, std::to_string,
        std::setw, std::stoi;

// A little "library" by Vincent Godin that allows the use of color in cout:
// https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
// From the .h file, we can see that the available colors are blue, red, green, yellow and white
#include "ConsoleColor.h"

#include "Hand.h"

/**
 * This function is responsible for printing the horizontal border(s) of the graphical representations of a Card or
 * multiple cards. These are found at the top and bottom of a card. As input, it takes a vector of cards to be printed
 * and it then prints a border for every card in this vector.
 *
 * For example if 3 cards are to be printed, the output looks like this:
 * "+----------+    +----------+    +----------+"
 */
void Hand::printHorizontalCardBorders(const vector<Card> cardsToPrint) {
    // Printing the top borders
    for (Card cardToPrint: cardsToPrint) {
        cout << "+----------+" << '\t';
    }
    cout << endl;
}

/**
 * This function is responsible for printing the empty row(s) of the graphical representations of a Card or multiple
 * cards. These are found in the middle of a card. As input, it takes a vector of cards to be printed and it then
 * prints an empty row for every card in this vector.
 *
 * For example if 3 cards are to be printed, the output looks like this:
 * "|          |    |          |    |          |"
 */
void Hand::printEmptyCardRow(const vector<Card> cardsToPrint) {
    for (Card cardToPrint: cardsToPrint) {
        cout << "|          |" << '\t';
    }
    cout << endl;
}

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
void Hand::printCardValueRow(const vector<Card> cardsToPrint, const string alignment) {
    if (alignment == "left") { // The top position prints the values left aligned
        // Printing the top row(s) with value(s)
        for (Card cardToPrint: cardsToPrint) {
            cout << "| ";
            // The color is based on the symbol
            // if the symbol is red, then the text is printed in red, else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << left << setw(2) << cardToPrint.getFaceValue() << white << "       |" << '\t';
            } else {
                cout << left << setw(2) << cardToPrint.getFaceValue() << "       |" << '\t';
            }
        }
    } else if (alignment == "right") { // The same principle, but for the bottom row it is aligned on the right
        for (Card cardToPrint: cardsToPrint) {
            cout << "|       ";
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << right << setw(2) << cardToPrint.getFaceValue() << white;
            } else {
                cout << right << setw(2) << cardToPrint.getFaceValue();
            }
            cout << " |" << '\t';
        }
    } else {
        cerr << "Error in printCardValueRow: position not defined correctly" << endl;
    }
    cout << endl;
}

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
void Hand::printCardSymbolRow(const vector<Card> cardsToPrint, const string alignment) {
    // Printing the top row(s) with symbol(s)
    // Going through the vector starting at the 2nd value (i=1) and skipping every other value
    // in order to get to the symbols and not the card cardsData
    if (alignment == "left") { // The top position prints the symbols left aligned
        for (Card cardToPrint: cardsToPrint) {
            char symbol = cardToPrint.cardSymbolStringToIconChar(cardToPrint.getSymbol());

            // Printing the left border of the card in white/black
            cout << white << "| ";
            // If the symbol is hearts or diamonds, print it in red and else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << symbol << white;
            } else {
                cout << symbol;
            }
            // Printing the right border of the card in white/black
            cout << "        |" << '\t';
        }
    } else if (alignment == "right") { // The same principle, but for the bottom row it is aligned on the right
        for (Card cardToPrint: cardsToPrint) {
            char symbol = cardToPrint.cardSymbolStringToIconChar(cardToPrint.getSymbol());

            cout << white << "|        ";
            // if the symbol is hearts or diamonds, print it in red and else in white/black
            if (cardToPrint.getSymbol() == "hearts" || cardToPrint.getSymbol() == "diamonds") {
                cout << red << symbol << white;
            } else {
                cout << symbol;
            }
            cout << " |" << '\t';
        }
    } else {
        cerr << "Error in printCardValueRow: position not defined correctly" << endl;
    }
    cout << endl;
}

/**
 * Default constructor for an empty hand.
 */
Hand::Hand() {}

/**
 * This function adds a Card object to the hand of cards.
 */
void Hand::addCard(const Card &cardToAdd) {
    cardsInHand.push_back(cardToAdd);
}

/**
 * This function adds an amount of randomly generated cards to the Hand object. It takes an integer value that
 * specifies how many cards need to be generated and added.
 */
void Hand::addRandomCards(int amountOfCardsToAdd) {
    for (int i = 0; i < amountOfCardsToAdd; i++) {
        cardsInHand.push_back(Card());
    }
}

/**
 * This function removes the lastly added Card object from a hand of cards.
 */
void Hand::removeLastCard() {
    cardsInHand.pop_back();
}

/**
 * This function empties a Hand of cards by clearing the cardsInHand vector.
 */
void Hand::emptyHand() {
    cardsInHand.clear();
}

/**
 * This function returns the amount of cards in the Hand by returning the size() of the cardsInHand vector.
 */
int Hand::getSize() {
    return cardsInHand.size();
}

/**
 * This function returns the Card object stored in the cardsInHand vector at the index corresponding with the input
 * parameter "index". Note that this refers to the cards using indices (where card 1 is index 0), and not the natural
 * physical way of addressing physical cards where the first card would be called card 1.
 */
Card Hand::getCardAtIndex(int index) {
    return cardsInHand[index];
}

/**
 * This function prints a hand of cards vertically, one after the other.
 */
void Hand::printVertical() {
    // Ranged based for loop to go through the cards in the vector of the hand
    for (Card cardToPrint: cardsInHand) {
        cardToPrint.printCard();
    }
}

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
void Hand::printHorizontal() {
    // Calculating the amount of card rows based on the hand size and the maximum amount of cards per printing row
    int amountOfRows = ((cardsInHand.size() - 1) / MAX_CARDS_PER_PRINT_ROW) + 1;

    // Printing the rows of cards in the console one by one
    for (int rowOfCards = 1; rowOfCards <= amountOfRows; rowOfCards++) {
        // Extracting sections of the hand that are no longer than MAX_CARDS_PER_PRINT_ROW for printing individual
        // rows of cards
        vector<Card> cardsInThisRow = getSectionOfHand(
                ((MAX_CARDS_PER_PRINT_ROW * rowOfCards) - MAX_CARDS_PER_PRINT_ROW) + 1,
                MAX_CARDS_PER_PRINT_ROW * rowOfCards);

        // Printing the top borders of the cards ("+----------+")
        printHorizontalCardBorders(cardsInThisRow);
        // Printing the cards' top rows with values (e.g. "| 5        |")
        printCardValueRow(cardsInThisRow, "left");
        // Printing the cards' top rows with symbols (e.g. "| ♥        |")
        printCardSymbolRow(cardsInThisRow, "left");
        // Printing the empty middle rows of the cards ("|          |")
        printEmptyCardRow(cardsInThisRow);
        // Printing the cards' bottom rows with symbols (e.g. "|        ♥ |")
        printCardSymbolRow(cardsInThisRow, "right");
        // Printing the cards' bottom rows with values (e.g. "|        5 |")
        printCardValueRow(cardsInThisRow, "right");
        // Printing the bottom borders of the cards ("+----------+")
        printHorizontalCardBorders(cardsInThisRow);
    }
}

/**
 * This function returns a section of a Hand of cards as a vector of Card objects. The section is defined by the
 * input integers start and end. The start and end values represent the actual positions of the cards as you would
 * naturally describe them in real life, not their index in the Hand vector. Both the cards at start and end are
 * included in the returned section. So, for example, start = 1 refers to the first card of the hand and end = 4
 * refers to the fourth card of the hand.
 *
 * As an example, getSectionOfHand(3, 6) returns a vector of Cards 3, 4, 5 and 6 of the Hand
 */
vector<Card> Hand::getSectionOfHand(int start, int end) {
    vector<Card> partOfHand;
    for (int i = start; i <= end; ++i) {
        if (i <= cardsInHand.size()) {
            partOfHand.push_back(cardsInHand[i - 1]);
        }
    }
    return partOfHand;
}
