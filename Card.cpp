/**
 * The Card class defines a standard playing card in C++ along with some useful methods. It includes constructors for
 * creating instances with either random or specified face values and symbols. The class provides methods for setting
 * and retrieving these properties, checking if the card is an Ace, determining its game value, and printing a graphical
 * representation to the console. It also incorporates error-checking where needed to ensure the validity of provided
 * face values and symbols.
 */

#include "Card.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// A little "library" by Vincent Godin that allows the use of color in cout:
// https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
// From the .h file, we can see that the available colors are blue, red, green, yellow and white
#include "ConsoleColor.h"

// Including used elements from the std namespace to avoid having to write std:: a lot throughout the code
using std::cout, std::endl, std::cerr, std::cin, std::vector, std::string, std::left, std::right, std::to_string,
        std::setw, std::stoi;

/**
 * This function returns a random card face value with type string. This can be 2-10, A, J, Q or K.
 */
string Card::generateRandomCardValueString() {
    int randomValue = rand() % 13 + 1;

    if (randomValue == 1) {
        return "A";
    } else if (randomValue == 11) {
        return "J";
    } else if (randomValue == 12) {
        return "Q";
    } else if (randomValue == 13) {
        return "K";
    } else {
        return to_string(randomValue);
    }
}

/**
 * This function returns a random card symbol with type string. This can be hearts, diamonds, clubs or spades.
 */
string Card::generateRandomCardSymbolString() {
    int randomNumber = rand() % 4;
    if (randomNumber == 0)
        return "hearts";
    else if (randomNumber == 2)
        return "diamonds";
    else if (randomNumber == 3)
        return "clubs";
    else
        return "spades";
}

/**
 * This function checks whether a card face value, provided as input string "faceValueStringToCheck", is reasonable.
 * To be reasonable, the face value string needs to be 2-10 or J, Q, K or A. Otherwise an error will be displayed
 * indicating the problem and the program will be exited.
 */
void Card::errorCheckCardValue(const string &faceValueStringToCheck) {
    // Check if faceValueStringToCheck is between "2" and "10"
    if (faceValueStringToCheck < "2" || faceValueStringToCheck > "9" &&
                                        (faceValueStringToCheck != "10" && faceValueStringToCheck != "J" &&
                                         faceValueStringToCheck != "Q" && faceValueStringToCheck != "K" &&
                                         faceValueStringToCheck != "A")) {
        std::cerr << "Error: card value is not 2-10 or A, J, Q or K" << endl;
        exit(-1);
    }
}

/**
 * This function checks whether a symbol string, provided as input string "symbolString", is reasonable. To be
 * reasonable, the string must be "hearts", "diamonds", "clubs" or "spades". Otherwise an error will be displayed
 * indicating the problem and the program will be exited.
 */
void Card::errorCheckCardSymbol(const string &symbolString) {
    if (symbolString != "hearts" && symbolString != "diamonds" && symbolString != "clubs" &&
        symbolString != "spades") {
        // According to internet research, a " can be printed as a string by writing \" 'to escape the characters'
        std::cerr << "Error: the card symbol is not \"hearts\", \"diamonds\", \"clubs\" or \"spades\"" << endl;
        exit(-1);
    }
}

/**
 * Default constructor: defines a Card object with random face value and symbol if no input parameters are provided
 */
Card::Card() {
    faceValueString = generateRandomCardValueString();
    symbolString = generateRandomCardSymbolString();
}

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
Card::Card(string faceValueString_, string symbolString_) {
    errorCheckCardValue(faceValueString_);
    errorCheckCardSymbol(symbolString_);
    faceValueString = faceValueString_;
    symbolString = symbolString_;
}

/**
 * This function sets or modifies the face value of a Card object to the input string "newFaceValue".
 */
void Card::setFaceValue(string newFaceValue) {
    errorCheckCardValue(newFaceValue);
    faceValueString = newFaceValue;
}

/**
 * This function returns the face value of a Card object.
 */
string Card::getFaceValue() {
    return faceValueString;
}

/**
 * This function sets or modifies the symbol of a Card object to the input string "newSymbol".
 */
void Card::setSymbol(string newSymbol) {
    errorCheckCardSymbol(newSymbol);
    symbolString = newSymbol;
}

/**
 * This function returns the symbol value of a Card object.
 */
string Card::getSymbol() {
    return symbolString;
}

/**
 * This function returns the corresponding char of a symbol based on the input string "stringCardSymbol". The
 * symbol characters are defined in the constant private variables of this class (♥, ♦, ♣, ♠).
 */
char Card::cardSymbolStringToIconChar(string stringCardSymbol) {
    if (stringCardSymbol == "hearts") {
        return hearts; // ♥
    } else if (stringCardSymbol == "diamonds") {
        return diamonds; // ♦
    } else if (stringCardSymbol == "clubs") {
        return clubs; // ♣
    } else if (stringCardSymbol == "spades") {
        return spades; // ♠
    }
}

/**
 * This function returns an integer that represents the actual common game value of a card based on the face value,
 * which is specified using a string. This allows for logical operations with the card's value. Note that an Ace is
 * returned as gameValue 11, which is not always the case in a card game.
 */
int Card::getGameValue() {
    // Check if  faceValueString is between "2" and "10"
    if (faceValueString >= "2" && faceValueString <= "9") {
        // Using string to int (stoi) to convert the 1-digit number in the string to an int
        // Function found on https://cplusplus.com/reference/string/stoi/
        return stoi(faceValueString);
    } else if (faceValueString == "10" || faceValueString == "J" ||
               faceValueString == "Q" ||
               faceValueString == "K") {
        return 10;
    } else if (faceValueString == "A") {
        return 11;
    } else {
        return 0;
    }
}

/**
 * This function returns true if the Card object has Ace as value and false if it does not.
 */
bool Card::isAce() {
    if (faceValueString == "A") {
        return true;
    } else {
        return false;
    }
}

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
void Card::printCard() {
    cout << "+----------+" << endl;

    // Printing the top row with value
    cout << "| ";
    // The color is based on the symbol
    // if the symbol is red, then the text is printed in red, else in white/black
    if (symbolString == "hearts" || symbolString == "diamonds") {
        cout << red << left << setw(2) << faceValueString << white << "       |";
    } else {
        cout << left << setw(2) << faceValueString << "       |";
    }
    cout << endl;

    // Printing the top row with symbol
    // in order to get to the symbols and not the card cardsData
    char symbolIcon = cardSymbolStringToIconChar(symbolString);

    // Printing the left border of the card in white/black
    cout << "| ";
    // If the symbol is hearts or diamonds, print it in red and else in white/black
    if (symbolString == "hearts" || symbolString == "diamonds") {
        cout << red << symbolIcon << white;
    } else {
        cout << symbolIcon;
    }
    // Printing the right border of the card in white/black
    cout << "        |" << endl;

    // Printing the empty middle row of a card
    cout << "|          |" << endl;

    // Printing the bottom row with symbol
    cout << "|        ";
    // if the symbol is hearts or diamonds, print it in red and else in white/black
    if (symbolString == "hearts" || symbolString == "diamonds") {
        cout << red << symbolIcon << white;
    } else {
        cout << symbolIcon;
    }
    cout << " |" << endl;

    // Printing the bottom row(s) with value(s)
    cout << "|       ";
    // The color is based on the symbol, which is i+1 in the vector
    // If the symbol is red, then the text is printed in red, else in white/black
    if (symbolString == "hearts" || symbolString == "diamonds") {
        cout << red << right << setw(2) << faceValueString << white;
    } else {
        cout << right << setw(2) << faceValueString;
    }
    cout << " |" << endl;

    // Printing the bottom border
    cout << "+----------+" << endl;
}
