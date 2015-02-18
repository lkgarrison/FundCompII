/* Luke Garrison, CardDeck.cpp
 * Implementation for CardDeck class
 */

#include <iostream>
#include <cstdlib>	// for srand
#include <ctime>	// for srand
#include "CardDeck.h"
using namespace std;

/* Overloaded output operator */
ostream & operator<<(ostream & output, const CardDeck & myDeck) {
	srand(time(0));				// seed the random generator	
	deque<int>::const_iterator i;	// create a forward iterator for the deck
  	for (i = myDeck.deck.begin(); i != myDeck.deck.end(); ++i) {
    	output << *i << ", ";		// display each value separated by a comma and space
	}
	output << endl;
	return output;
}


/* Constructor for CardDeck
 * Initialize deque, deck to hold cards
 * fill deque with values 0 to n, inclusive
*/
CardDeck::CardDeck(int n) {
  	for(int i = 0; i < n; ++i) {
		deck.push_back(i);
	}
}

/* Returns the size of the card deck */
int CardDeck::getSize() {
	return deck.size();
}

/* Shuffles the deck using STL's random_shuffle algorithm */
void CardDeck::shuffle() {
	random_shuffle(deck.begin(), deck.end());

}

/* Returns 1 if the deck is in order, 0 if not in order */
int CardDeck::inOrder() {
	// check and see if every value in deck is greater than the previous
	for(int i = 0; i < deck.size() - 1; i++) {
		if(deck[i] > deck[i+1]) {
			return 0;					// 0 for deck not in order
		}
	}
	return 1;	// deck is in order if every value was greater than the prev
}

