/* Luke Garrison, main.cpp
 * This is a driver program used to demonstrate the 
 * CardDeck class
*/

#include <iostream>
#include "CardDeck.h"
#include <iterator>
#include <deque>

using namespace std;

int main() {
	CardDeck myDeck(10);		// create a deck with 10 cards
	cout << "size of deck: " << myDeck.getSize() << endl;

	cout << myDeck;				// display deck
	if(myDeck.inOrder() == 1) 	// display if deck is in order or not
		cout << "Deck is in order" << endl;
	else cout << "Deck is not in order" << endl;
	
	myDeck.shuffle();			// randomly shuffle the deck
	cout << myDeck;				
	if(myDeck.inOrder() == 1) 
		cout << "Deck is in order" << endl;
	else cout << "Deck is not in order" << endl;	

	return 0;
}
