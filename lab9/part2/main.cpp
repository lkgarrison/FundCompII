/* Luke Garrison, main.cpp
 * This program is a driver program for the BJCardDeck class, which utilizes the NDVector class
 * This driver will instantiate a deck of size 52, ensure that it is in order, and 
 * then prints the deck before and after shuffling it.
*/

#include <iostream>
#include "BJCardDeck.h"
using namespace std;

int main() {
	BJCardDeck cardDeck(52);		// instantiate card deck with 52 cards
	if(cardDeck.inOrder())			// display a message of whether or not it is in order
		cout << "Card deck is in order" << endl;
	else 
		cout << "Card deck is not in order" << endl;

	cout << "Card deck before shuffling:" << endl;
	cout << cardDeck;				// display the deck before shuffling
	cardDeck.shuffle();				// shuffle card deck
	cout << "Card deck after shuffling:" << endl;
	cout << cardDeck;				// display the card deck after shuffling

	return 0;
}
