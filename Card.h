/**
 * The Card class defines a standard playing card in C++ along with some useful methods. It includes constructors for
 * creating instances with either random or specified face values and symbols. The class provides methods for setting
 * and retrieving these properties, checking if the card is an Ace, determining its game value, and printing a graphical
 * representation to the console. It also incorporates error-checking where needed to ensure the validity of provided
 * face values and symbols.
 */

#ifndef PIE_CPP_BLACKJACK_CARD_H
#define PIE_CPP_BLACKJACK_CARD_H

#include <string>
// Including used elements from the std namespace to avoid having to write std:: a lot throughout the code
using std::string;

class Card {
private:
    string faceValueString; // the face value is the value as printed on a card, being 2-10, A, J, Q or K
    string symbolString;

    // Defining the card symbol characters based on this online forum discussion:
    // https://www.daniweb.com/programming/software-development/threads/296311/can-i-get-the-cards-suit-symbols-as-a-character
    const char hearts = '\x03';  //♥
    const char diamonds = '\x04';  //♦
    const char clubs = '\x05';  //♣
    const char spades = '\x06';  //♠

    /**
     * This function returns a random card face value with type string. This can be 2-10, A, J, Q or K.
     */
    string generateRandomCardValueString();

    /**
     * This function returns a random card symbol with type string. This can be hearts, diamonds, clubs or spades.
     */
    string generateRandomCardSymbolString();

    /**
     * This function checks whether a card face value, provided as input string "faceValueStringToCheck", is reasonable.
     * To be reasonable, the face value string needs to be 2-10 or J, Q, K or A. Otherwise an error will be displayed
     * indicating the problem and the program will be exited.
     */
    void errorCheckCardValue(const string &faceValueStringToCheck);

    /**
     * This function checks whether a symbol string, provided as input string "symbolString", is reasonable. To be
     * reasonable, the string must be "hearts", "diamonds", "clubs" or "spades". Otherwise an error will be displayed
     * indicating the problem and the program will be exited.
     */
    void errorCheckCardSymbol(const string &symbolString);

public:
    /**
     * Default constructor: defines a Card object with random face value and symbol if no input parameters are provided
     */
    Card();

    /**
     * Constructor for a Card object with specified face value and symbol definitions.
     *
     * Valid input strings for the Card's face value string are:
     * "2"-"10", "A" (Ace), "J" (Jack), "Q" (Queen) and "K" (King).
     *
     * Valid input strings for the Card's symbol string are:
     * "hearts" (♥), "diamonds" (♦) "clubs" (♣) and  "spades" (♠)
     *
     * For example:
     * A 5 of hearts card would be specified as Card("5", "hearts");
     * A King of clubs card would be specified as Card("K", "clubs").
     */
    Card(string faceValueString_, string symbolString_);

    /**
     * This function sets or modifies the face value of a Card object to the input string "newFaceValue".
     */
    void setFaceValue(string newFaceValue);

    /**
     * This function returns the face value of a Card object.
     */
    string getFaceValue();

    /**
     * This function sets or modifies the symbol of a Card object to the input string "newSymbol".
     */
    void setSymbol(string newSymbol);

    /**
     * This function returns the symbol value of a Card object.
     */
    string getSymbol();

    /**
     * This function returns the corresponding char of a symbol based on the input string "stringCardSymbol". The
     * symbol characters are defined in the constant private variables of this class (♥, ♦, ♣, ♠).
     */
    char cardSymbolStringToIconChar(string stringCardSymbol);

    /**
     * This function returns an integer that represents the actual common game value of a card based on the face value,
     * which is specified using a string. This allows for logical operations with the card's value. Note that an Ace is
     * returned as gameValue 11, which is not always the case in a card game.
     */
    int getGameValue();

    /**
     * This function returns true if the Card object has Ace as value and false if it does not.
     */
    bool isAce();

    /**
     * This function prints a Card object to the console in a graphical way, based on its faceValueString and its
     * symbolString. This is an example of a printed card where faceValueString = "5" and symbolString = "hearts":
     *  +----------+
     *  | 5        |
     *  | ♥        |
     *  |          |
     *  |        ♥ |
     *  |        5 |
     *  +----------+
     */
    void printCard();
};


#endif //PIE_CPP_BLACKJACK_CARD_H
