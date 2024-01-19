/**
 * The Blackjack class defines a console-based casino card game of Blackjack. It defines the core logic of the game,
 * including managing rounds, player and dealer hands, card sums, and evaluating round outcomes. The methods provide the
 * dealer and player with random cards and prompts the user to hit or stand, handles dealer actions, and determines the
 * winner based on standard Blackjack rules. The class also includes methods for printing visual elements, such as the
 * opening title and round results. To mimic the experience of real Blackjack at a table, the code implements pauses
 * between draws to allow the user to take in the drawn cards. Users can start new rounds or quit the game after each round.
 *
 * Note this class depends on the Hand class, which depends on the Card class. Make sure both classes are available in
 * the project.
 */

#ifndef PIE_CPP_BLACKJACK_BLACKJACK_H
#define PIE_CPP_BLACKJACK_BLACKJACK_H

#include "Hand.h"

class Blackjack {
private:
    const int SECONDS_BETWEEN_DRAWS = 2;
    const double MONEY_AT_START = 10;

    double playerMoney = MONEY_AT_START;
    double thisRoundBet = 0;

    /**
     * This function manages a full round of Blackjack. To start the game, it draws the dealer a card and the player two
     * cards. In between draws, the cards are reprinted to the console and the program is paused to mimic the real world
     * dynamics of a dealer handing out cards. This gives the user time to process the information. Using a while-loop
     * and based on the user's entered response (gathered from calling requestHitOrStand()), the player is drawn another
     * card (hit) or they are not given cards anymore (stand). When the user stands, the dealer is dealt cards as long
     * as their sum of cards is below 17. After this process concludeRound() is called to decide the winner of the round.
     */
    void playRound();

    /**
     * This function concludes a round of Blackjack by determining the outcome of the round based on the final card sums.
     * It evaluates all possible scenarios such as busting (sum > 21), winning with a higher sum, having a tie and it
     * checks the presence of a blackjack (an Ace with a 10-value card) in the initial two cards.
     *
     * Using boolean states for who won, the function prints the result of the round using the ASCII by calling printYouWon()
     * and printYouLost(),as well as messages for winning with a blackjack or achieving a tie. Finally, based on user
     * input, a new round is started or the program is quit.
     */
    void concludeRound();

    /**
     * This function prints ASCII art for the opening title of the game made with: https://patorjk.com/software/taag/
     */
    void printOpeningTitle();

    /**
     * This function prints ASCII art "You won!" made with: https://patorjk.com/software/taag/
     */
    void printYouWon();

    /**
     * This function prints ASCII art "You lost..." made with: https://patorjk.com/software/taag/
     */
    void printYouLost();

    /**
     * This function prints a horizontal border with a line of '=' characters to visually separate console information
     */
    void printConsoleSeparationLine();

    /**
     * This function asks the player whether they want to hit (receive another card) or stand (stop receiving cards), and
     * expects a single character as input. When a valid character is entered, the function returns the player's decision
     * as a string "hit" or "stand".
     */
    string requestHitOrStand();

    /**
     * This function prints an overview of the hands of the dealer and the player. It calls the printHorizontal()
     * function to do the actual Hand printing. First the dealer's hand is printed (along with the current cards sum) and
     * underneath the player's hand is printed (also along with the current cards sum).
     */
    void printDealerAndPlayerHands();

    /**
     * This function calculates and returns the optimal sum of a hand of cards according to standard Blackjack rules.
     * It iterates through each card in the hand, adding their game values to the total sum. Additionally, it keeps track
     * of the number of Aces in the hand as they can have a flexible value of 1 or 11. In case the sum exceeds 21 (busting),
     * the function adjusts the value of Aces from 11 to 1 to minimize the total sum and avoid busting.
     */
    unsigned int sumOptimal(Hand &handToSum);

    /**
     * This function request the player to place a bet for the coming round. It shows the balance, so the player knows how
     * much they can spend. Then the player is asked to input an integer for how much they want to bet. The input is first
     * checked for being numerical (not a string with letters or symbols), whether it is at least 1, and whether the player
     * has enough money to place the bet. When all checks are passed, the bet is returned as an integer.
     */
    unsigned int requestBetAmount();

    /**
     * This function handles paying the player the right amount of money based on the conclusion of the round (see
     * concludeRound()). For a normal win, the factor is 1, so the player gets back twice their bet. In case of
     * winning with a Blackjack, the payout rate is 2:3, so the player gets back their bet times factor 1.5 + their bet.
     */
    void payout(double bet, double factor);

    /**
     * This function prints an overview of the player's remaining balance and the bet they placed.
     */
    void printBalanceAndBet();

    /**
     * This function uses thread and chrono to sleep the program for as many seconds as specified by the parameter
     * "secondsToWait". This can be used as a delay to add timed pauses within the program where necessary. This method
     * of pausing a program was learned from https://cplusplus.com/reference/thread/this_thread/sleep_for/.
     */
    void waitSeconds(int secondsToWait);

public:
    Hand playerHand;
    Hand dealerHand;

    /**
     * This function launches the game and takes the to sort of a 'main menu'. It welcomes the user and asks them
     * whether they want to start playing a round of Blackjack or want to quit the program. Based on the user's entered
     * response in the form of a letter, this function calls the playRound() or quitGame() functions.
     */
    void launchGame();

    /**
     * This function exits the program with code 0 (successful exit)
     */
    void quitGame();
};


#endif //PIE_CPP_BLACKJACK_BLACKJACK_H
