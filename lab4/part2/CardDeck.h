#ifndef CARDDECK_H
#define CARDDECK_H

/* Luke Garrison, CardDeck.h
 * Interface for CardDeck class
*/

#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>
using namespace std;

class CardDeck {

	friend ostream & operator<<(ostream & output, const CardDeck &);	// overload output operator	
	
	public:
		CardDeck(int n = 52);		// fallback value for number of cards in deck is 52
		int getSize();				// returns the size of the deck
		void shuffle();				// will shuffle the order of the deck
		int inOrder();				// returns 1 if the deck is in non-decreasing order, 0 otherwise

	private:
		deque<int> deck;			// deque to store deck of cards
		
};

#endif
