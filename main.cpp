#include <iostream>
#include <iomanip>

#include <vector>
#include <string>

// Including <chrono> and <thread> in order to be able to add timed pauses to the code according to:
// https://cplusplus.com/reference/thread/this_thread/sleep_for/
#include <chrono>
#include <thread>

// A little "library" by Vincent Godin that allows the use of color in cout:
// https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
// From the .h file, we can see that the available colors are blue, red, green, yellow and white
#include "ConsoleColor.h"

// Including the custom classes that were written for this course
#include "Card.h"
#include "Hand.h"

// Including used elements from the std namespace to avoid having to write std:: a lot throughout the code
using std::cout, std::endl, std::cerr, std::cin, std::vector, std::string, std::left, std::right, std::to_string,
        std::setw, std::stoi;


class Blackjack {
private:
    const int SECONDS_BETWEEN_DRAWS = 2;

    /**
     * This function manages a full round of Blackjack. To start the game, it draws the dealer a card and the player two
     * cards. In between draws, the cards are reprinted to the console and the program is paused to mimic the real world
     * dynamics of a dealer handing out cards. This gives the user time to process the information. Using a while-loop
     * and based on the user's entered response (gathered from calling requestHitOrStand()), the player is drawn another
     * card (hit) or they are not given cards anymore (stand). When the user stands, the dealer is dealt cards as long
     * as their sum of cards is below 17. After this process concludeRound() is called to decide the winner of the round.
     */
    void playRound() {
        playerHand.emptyHand();
        dealerHand.emptyHand();

        // To start the game, the dealer gets one open card
        dealerHand.addRandomCards(1);
        printDealerAndPlayerHands();

        // Adding a pause to allow the user time to comprehend which card the dealer drew
        waitSeconds(SECONDS_BETWEEN_DRAWS);

        // After the dealer's card is shown, the player gets 2 cards, one by one with a pause in between to mimic real life
        playerHand.addRandomCards(1);
        printDealerAndPlayerHands();
        waitSeconds(SECONDS_BETWEEN_DRAWS);
        playerHand.addRandomCards(1);
        printDealerAndPlayerHands();
        waitSeconds(SECONDS_BETWEEN_DRAWS);

        // If the player is dealt 21 (blackjack) straight away, go straight to concluding the round without asking
        // whether the user wants another card or not
        if (sumOptimal(playerHand) == 21) {
            concludeRound();
        }

        // Asking whether the player wants to hit (get new card) or stand (let the dealer draw cards and check who won)
        // This while loop will keep running as long as the user chooses to hit
        while (requestHitOrStand() == "hit" && sumOptimal(playerHand) < 21) {
            playerHand.addRandomCards(1);
            printDealerAndPlayerHands();
            waitSeconds(SECONDS_BETWEEN_DRAWS);
            // If the sum goes over 21, the player has busted and the round needs to be concluded
            if (sumOptimal(playerHand) >= 21) {
                concludeRound();
            }
        }

        // At this point, the user has decided to stand because the while condition is no longer true

        // As long as the sum of the dealers' cards are below 17, the dealer has to hit. If it is above 17, the dealer
        // has to stand. If the dealer has an ace, and counting it as 11 would bring the total to 17 or more (but not
        // over 21), the dealer must count the ace as 11 and stand. This while loop keeps adding cards until the sum is
        // above 17:
        while (sumOptimal(dealerHand) < 17) {
            dealerHand.addRandomCards(1);
            printDealerAndPlayerHands();
            // Adding a timed pause to allow the user time to comprehend which card(s) the dealer is drawing. This
            // method was learned from: https://cplusplus.com/reference/thread/this_thread/sleep_for/
            std::this_thread::sleep_for(std::chrono::seconds(SECONDS_BETWEEN_DRAWS));
        }

        concludeRound();
    }

    /**
     * This function concludes a round of Blackjack by determining the outcome of the round based on the final card sums.
     * It evaluates all possible scenarios such as busting (sum > 21), winning with a higher sum, having a tie and it
     * checks the presence of a blackjack (an Ace with a 10-value card) in the initial two cards.
     *
     * Using boolean states for who won, the function prints the result of the round using the ASCII by calling printYouWon()
     * and printYouLost(),as well as messages for winning with a blackjack or achieving a tie. Finally, based on user
     * input, a new round is started or the program is quit.
     */
    void concludeRound() {
        boolean playerWon = false;
        boolean dealerWon = false;
        boolean wonWithBlackjack = false;

        // Storing the player and dealer sums to make the below if-statements easier to read
        int dealerSum = sumOptimal(dealerHand);
        int playerSum = sumOptimal(playerHand);

        // Determining who won by going over all the possible situations:
        if (playerSum > 21) { // Player busted, dealer wins
            dealerWon = true;
        } else if (dealerSum > 21) { // Dealer busted, player wins
            playerWon = true;
        } else if (playerSum > dealerSum && playerSum < 21) { // Player has higher sum w/o busting, but no blackjack
            playerWon = true;
        } else if (dealerSum > playerSum && dealerSum < 21) { // Dealer has higher sum w/o busting, but no blackjack
            dealerWon = true;
        } else if (playerSum == 21 && dealerSum != 21) { // Player wins with 21
            playerWon = true;
            if (playerHand.getSize() == 2) { // Player has BLACKJACK!
                wonWithBlackjack = true;
            }
        } else if (dealerSum == 21 && playerSum != 21) { // Dealer wins with 21
            dealerWon = true;
            if (dealerHand.getSize() == 2) { // Dealer has BLACKJACK!
                wonWithBlackjack = true;
            }
        } else if (dealerSum == 21 && playerSum == 21) {
            if (playerHand.getSize() == 2 && dealerHand.getSize() != 2) { // Player has won with BLACKJACK!
                playerWon = true;
                wonWithBlackjack = true;
            } else if (playerHand.getSize() != 2 && dealerHand.getSize() == 2) { // Dealer has won with BLACKJACK!
                dealerWon = true;
                wonWithBlackjack = true;
            } else { // A tie, no one wins
                // All booleans can remain false
            }
        } else if (dealerSum == playerSum) { // A tie, no one wins
            // All booleans can remain false
        } else {
            cerr << "Not defined who won, check code" << endl;
        }


        // Printing who won the round
        if (wonWithBlackjack == true) {
            cout << "BLACKJACK!" << endl;
        }
        if (playerWon == true) {
            printYouWon();
        } else if (dealerWon == true) {
            printYouLost();
        } else {
            cout << "It's a tie. No one won." << endl << endl;
        }

        // Asking whether the user wants to play a new round
        string userInput;
        cout << "Enter 's' to start a new round or 'q' to quit the game: " <<
             endl;
        while (true) {
            cin >> userInput;
            if (userInput == "s" || userInput == "S") {
                playRound();
                break;
            } else if (userInput == "q" || userInput == "Q") {
                quitGame();
                break;
            } else {
                cout << "Invalid input, please try again. Enter 's' to start or 'q' to quit the game" << endl;
            }
        }
    }

    /**
     * This function prints ASCII art for the opening title of the game made with: https://patorjk.com/software/taag/
     */
    void printOpeningTitle() {
        // printing the opening title "Casino++ Blackjack" using https://patorjk.com/software/taag/ to create ASCII Art
        cout << "  ____          _                           ____  _            _     _            _    " << endl;
        cout << " / ___|__ _ ___(_)_ __   ___    _     _    | __ )| | __ _  ___| | __(_) __ _  ___| | __" << endl;
        cout << "| |   / _` / __| | '_ \\ / _ \\ _| |_ _| |_  |  _ \\| |/ _` |/ __| |/ /| |/ _` |/ __| |/ /" << endl;
        cout << "| |__| (_| \\__ \\ | | | | (_) |_   _|_   _| | |_) | | (_| | (__|   < | | (_| | (__|   < " << endl;
        cout << " \\____\\__,_|___/_|_| |_|\\___/  |_|   |_|   |____/|_|\\__,_|\\___|_|\\_\\/ |\\__,_|\\___|_|\\_\\"
             << endl;
        cout << "                                                                  |__/                 " << endl;
    }

    /**
     * This function prints ASCII art "You won!" made with: https://patorjk.com/software/taag/
     */
    void printYouWon() {
        // printing "You won!" using https://patorjk.com/software/taag/ to create ASCII Art
        cout << " __   __                                       _ " << endl;
        cout << " \\ \\ / /___   _   _    __      __ ___   _ __  | |" << endl;
        cout << "  \\ V // _ \\ | | | |   \\ \\ /\\ / // _ \\ | '_ \\ | |" << endl;
        cout << "   | || (_) || |_| |    \\ V  V /| (_) || | | ||_|" << endl;
        cout << "   |_| \\___/  \\__,_|     \\_/\\_/  \\___/ |_| |_|(_)" << endl;
        cout << endl;
    }

    /**
     * This function prints ASCII art "You lost..." made with: https://patorjk.com/software/taag/
     */
    void printYouLost() {
        cout << " __   __                _              _            " << endl;
        cout << " \\ \\ / /___   _   _    | |  ___   ___ | |_          " << endl;
        cout << "  \\ V // _ \\ | | | |   | | / _ \\ / __|| __|         " << endl;
        cout << "   | || (_) || |_| |   | || (_) |\\__ \\| |_  _  _  _ " << endl;
        cout << "   |_| \\___/  \\__,_|   |_| \\___/ |___/ \\__|(_)(_)(_)" << endl;
        cout << endl;
    }

    /**
     * This function prints a horizontal border with a line of '=' characters to visually separate console information
     */
    void printConsoleSeparationLine() {
        cout << "===================================================================" << endl << endl;
    }

    /**
     * This function asks the player whether they want to hit (receive another card) or stand (stop receiving cards), and
     * expects a single character as input. When a valid character is entered, the function returns the player's decision
     * as a string "hit" or "stand".
     */
    string requestHitOrStand() {
        cout << "Enter 'h' to hit or 's' to stand:" << endl;

        string userInput;
        while (true) {
            cin >> userInput;
            if (userInput == "h" || userInput == "H") {
                return "hit";
            } else if (userInput == "s" || userInput == "S") {
                return "stand";
            } else {
                cout << "Invalid input, please try again. Enter 'h' to hit or 's' to stand:" << endl;
            }
        }
    }

    /**
     * This function prints an overview of the hands of the dealer and the player. It calls the printHorizontal()
     * function to do the actual Hand printing. First the dealer's hand is printed (along with the current cards sum) and
     * underneath the player's hand is printed (also along with the current cards sum).
     */
    void printDealerAndPlayerHands() {
        printConsoleSeparationLine(); // ===========

        cout << "Dealer " << "(" << sumOptimal(dealerHand) << "):" << endl;
        dealerHand.printHorizontal();

        cout << "You " << "(" << sumOptimal(playerHand) << "):" << endl;
        playerHand.printHorizontal();

        cout << endl;
    }

    /**
     * This function calculates and returns the optimal sum of a hand of cards according to standard Blackjack rules.
     * It iterates through each card in the hand, adding their game values to the total sum. Additionally, it keeps track
     * of the number of Aces in the hand as they can have a flexible value of 1 or 11. In case the sum exceeds 21 (busting),
     * the function adjusts the value of Aces from 11 to 1 to minimize the total sum and avoid busting.
     */
    int sumOptimal(Hand &handToSum) {
        int sum = 0;
        int numberOfAcesInHand = 0;

        // Using an index-based for loop
        for (int i = 0; i < handToSum.getSize(); ++i) {
            Card cardToSum = handToSum.getCardAtIndex(i);

            sum += cardToSum.getGameValue();

            // Count the amount of aces, in case of going over 21. If the sum is more than 21 (busting/game over),
            // their values can later be reduced from 11 to 1 to reduce the sum.
            if (cardToSum.isAce()) {
                numberOfAcesInHand++;
            }
        }

        // While the sum is more than 21, reduce the sum by 10 for every ace in the hand to avoid busting if possible
        while (sum > 21 && numberOfAcesInHand > 0) {
            sum -= 10;
            numberOfAcesInHand--;
        }

        return sum;
    }

    /**
     * This function uses thread and chrono to sleep the program for as many seconds as specified by the parameter
     * "secondsToWait". This can be used as a delay to add timed pauses within the program where necessary. This method
     * of pausing a program was learned from https://cplusplus.com/reference/thread/this_thread/sleep_for/.
     */
    void waitSeconds(int secondsToWait) {
        // Delaying the program for a "secondsToWait" amount of seconds. method was learned from:
        // https://cplusplus.com/reference/thread/this_thread/sleep_for/
        std::this_thread::sleep_for(std::chrono::seconds(secondsToWait));
    }

public:
    Hand playerHand = Hand();
    Hand dealerHand = Hand();

    /**
     * This function launches the game and takes the to sort of a 'main menu'. It welcomes the user and asks them
     * whether they want to start playing a round of Blackjack or want to quit the program. Based on the user's entered
     * response in the form of a letter, this function calls the playRound() or quitGame() functions.
     */
    void launchGame() {
        cout << endl << "Welcome to:" << endl;
        printOpeningTitle(); // Printing the title of the game in large ASCII art graphics
        cout << "Enter 's' to start or 'q' to quit the game: " << endl;

        string userInput;
        while (true) {
            cin >> userInput;
            if (userInput == "s" || userInput == "S") {
                playRound();
                break;
            } else if (userInput == "q" || userInput == "Q") {
                quitGame();
                break;
            } else {
                cout << "Invalid input, please try again. Enter 's' to start or 'q' to quit the game" << endl;
            }
        }
    }

    /**
     * This function exits the program with code 0 (successful exit)
     */
    void quitGame() {
        cout << "Thank you for playing Casino++ Blackjack. Goodbye!" << endl;
        exit(0); // Exit code 0 for successful exit
    }
};

int main() {
    // Seeding the random number generator
    srand(time(0));

    // Launching a game of Blackjack defined by the Blackjack class
    Blackjack().launchGame();

    return 0;
}