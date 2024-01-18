#include <stdlib.h>
#include <time.h>

// Including the Blackjack class, which includes the Hand class, which included the Card class
#include "Blackjack.h"

int main() {
    // Seeding the random number generator
    srand(time(0));

    // Launching a game of Blackjack defined by the Blackjack class
    Blackjack().launchGame();

    return 0;
}