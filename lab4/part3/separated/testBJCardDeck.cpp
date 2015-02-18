/* Luke Garrison, testCardDeck.cpp
 * This program is designed to test the deal() method in the CardDeck class
 * This program will create a new deck, and deal out all of its cards. It will 
 * keep track of what values of the cards are returned.
 * 
 * For example, when a 52 card deck is created, it is expected that 4 2-9's will appear,
 * and 4 10,s 4 jacks, 4 queens, and 4 kings (each worth 10) (a total of 16 10's) as
 * well as 4 aces (11's).
 *
 * This program is simply to verifiy that the deal method works as expected
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CardDeck.h"

#include <vector>

using namespace std;

int main() {
	srand(time(0));				// intialize random generator

	int deckSize = 52;

	CardDeck deck(deckSize);			// new deck of 52 cards
	
	int dealerTotal = 0;
	int playerTotal = 0;

	
	int val;						// store value returned by deal()
	vector<int> test;
	for(int j = 0; j <= 11; j++) {	// initialize a vector to count values
		test.push_back(0);
	}

	for(int i = 0; i < deckSize; i++) {	// deal out every card, and keep track of how many cards
 										// are dealt with each value, 2-11
		val = deck.deal();		
		test[val] = test[val] + 1;
	}

	// display how many of each card value were returned by dealing the whole deck
	for(int j = 0; j <= 11; j++) {
		cout << test[j] << " ";
	}
	cout << endl;

	return 0;
}
