/* Luke Garrison, BJCardDeck.cpp
 * Implementation for BJCardDeck class
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>	// for srand
#include <ctime>	// for srand
#include "BJCardDeck.h"
using namespace std;

/* Overloaded output operator */
ostream & operator<<(ostream & output, const BJCardDeck & myDeck) {
	deque<int>::const_iterator i;	// create a forward iterator for the deck
  	for (i = myDeck.deck.begin(); i != myDeck.deck.end(); ++i) {
    	output << *i << ", ";		// display each value separated by a comma and space
	}
	output << endl;
	return output;
}

/* Non-default Constructor for BJCardDeck
 * Initialize deque, deck to hold cards
 * fill deque with values 0 to n, inclusive
 * BJCardDeck should be instantiated with a minimum deck size in mind
*/
BJCardDeck::BJCardDeck(int n, int minSize) {
	minDeckSize = minSize;			// miniumum deck size before a new deck is added
	originalDeckSize = n;			// used when adding another deck
  	for(int i = 0; i < n; ++i) {
		deck.push_back(i);
	}
	(*this).shuffle();				// shuffle card deck
}

/* Returns the size of the card deck */
int BJCardDeck::getSize() {
	return deck.size();
}

/* Shuffles the deck using STL's random_shuffle algorithm */
void BJCardDeck::shuffle() {
	random_shuffle(deck.begin(), deck.end());
}

/* Returns 1 if the deck is in order, 0 if not in order */
int BJCardDeck::inOrder() {
	// check and see if every value in deck is greater than the previous
	for(int i = 0; i < deck.size() - 1; i++) {
		if(deck[i] > deck[i+1]) {
			return 0;					// 0 for deck not in order
		}
	}
	return 1;	// deck is in order if every value was greater than the prev
}

/* Returns value of card from the deck that is randomly selected.
 * This card is also removed from the deck
 * The blackjack value of the card is then returned by this method
 * The mapping for the cards is as follows:
 * 	  0 1 2 3 4 5 6 7 8 9 10 11 12
 * 	  Q K 2 3 4 5 6 7 8 9 10 A  J
 * Thus, any card < 2 or > 11 will be a value of 10
*/
int BJCardDeck::deal() {
	int toRemove = rand() % getSize();		// designate an index of the deque to removedd
	int val = deck[toRemove] % 13;				// convert card to 0-12
	deck.erase(deck.begin() + toRemove);	// remove this random index from the deque
	if(deck.size() < minDeckSize) (*this).addDeck();	// add a new deck if it gets too low

	if(val < 2 | val > 11) {		// card is a Jack, Queen or King, ie = 10
		return 10;
	} else {						// card is 2 thru Ace, ie its number value
		return val;
	}
}	

/* Since this is a BlackJack CardDeck, 52 cards are assumed to be in a deck
 * 52 more cards, 0-51, are added to the existing deque
*/
void BJCardDeck::addDeck() {
	cout << "adding another deck" << endl;
	for(int i = 0; i < originalDeckSize; i++) {
		deck.push_back(i);
	}
	(*this).shuffle();
}

