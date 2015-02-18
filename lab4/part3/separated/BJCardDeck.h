#ifndef CARDDECK_H
#define CARDDECK_H

/* Luke Garrison, BJCardDeck.h
 * Interface for BJCardDeck class
*/

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
using namespace std;

class BJCardDeck {

	friend ostream & operator<<(ostream & output, const BJCardDeck &);	// overload output operator	
	
	public:
		BJCardDeck(int n=52, int minSize=15);  // fallback value for number of cards in deck is 52, minDeckSize = 15
		int getSize();				// returns the size of the deck
		void shuffle();				// will shuffle the order of the deck
		int inOrder();				// returns 1 if the deck is in non-decreasing order, 0 otherwise
		int deal();					// remove one card from the deck at random and return its value
		void addDeck();	// add another deck of deckSize to the existing deck

	private:
		deque<int> deck;			// deque to store deck of cards
		int originalDeckSize;		// original size of the deck (know how many cards are in a "new" deck
		int minDeckSize;			// minimum # cards that must be in deck - less than this will trigger addDeck
};

#endif
