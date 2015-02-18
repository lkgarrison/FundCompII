/* Luke Garrison, blackjack.cpp
 * This program will utilize the BJCardDeck class to play blackjack
 * Simplifications are used such as ace = 11, dealer must hit until 17 or higher
 * A new deck will be used when the current deck reaches less than 15 cards. This is
 * handled internally inside the BJCardDeck class
*/

#include <iostream>
#include "BJCardDeck.h"

using namespace std;

int main() {

	int minNumCards = 15;		// minumum number of cards in a deck before a new deck should be opened
	int deckSize = 52;			// 52 cards in a deck for black jack
	BJCardDeck deck(deckSize, minNumCards);		// new deck of 52 cards
	deck.play();				// play blackjack

	return 0;
}
