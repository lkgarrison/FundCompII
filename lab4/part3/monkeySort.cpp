/* Luke Garrison, MonkeySort.cpp
 * This driver program will utilize the BJCardDeck class in order to 
 * Shuffle decks of 7, 8, and 9 cards, and report the number of times
 * the decks had to be shuffled until they were ordered again. 
*/

#include <iostream>
#include "BJCardDeck.h"
using namespace std;

int main() {
	int nShuffles = 1;		// keep track of the number of shuffles. Initialize to 1 because of initial shuffle

	// instantiate 3 decks, with 7, 8 and 9 cards
	BJCardDeck deckOf7(7);	// no cards are being dealt, so minNumCards will not be triggered anyway
 	BJCardDeck deckOf8(8);
	BJCardDeck deckOf9(9);

	// add each deck to an array of decks (smallest to largest)
	BJCardDeck decks [] = {deckOf9, deckOf8, deckOf7};	// array of decks to test
	int nCardsPerDeck [] = {9, 8, 7};		// array with number of cards/deck, to align with decks array

	cout << "Number of shuffles required to put the deck back in order after an initial shuffle:" << endl;
	for(int i = 0; i < 9; i++) {
		decks[i / 3].shuffle();				// initial shuffle
		while(!decks[i / 3].inOrder()) {	// shuffle deck until in order
			decks[i / 3].shuffle();		
			nShuffles++;					// tally nShuffles to get in order
		}
		
		cout << nCardsPerDeck[i / 3] << " card deck: " << nShuffles << endl;
		
		nShuffles = 1; 		// reset nShuffles for next deck
	}
	
	return 0;
}
