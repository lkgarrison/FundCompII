/* Luke Garrison, BJCardDeck.cpp
 * Implementation for BJCardDeck class
 * Contains a method to play BlackJack
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>	// for srand
#include <ctime>	// for srand
#include <ctype.h>
#include "BJCardDeck.h"
using namespace std;

/* Overloaded output operator */
ostream & operator<<(ostream & output, const BJCardDeck & myDeck) {
	for(int i = 0; i < myDeck.getSize(); i++) {
		output << myDeck.deck[i] << (i == myDeck.getSize() -1 ? "" : ", ");
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
	srand(time(0));				// intialize random generator
	minDeckSize = minSize;			// miniumum deck size before a new deck is added
	originalDeckSize = n;			// used when adding another deck
  	for(int i = 0; i < n; ++i) {
		deck.push_back(i);
	}
	//(*this).shuffle();				// shuffle card deck
}

/* Returns the size of the card deck */
int BJCardDeck::getSize() const {
	return deck.size();
}

/* Shuffles the deck using Knuth's method */
void BJCardDeck::shuffle() {
	for(int i = 1; i < deck.size(); i++) {
		int k = rand() % i;		// select a random previous random element
		deck.swap(i, k);		// swap elements at indicies i and k of NDVector
	}
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

/* Returns value of card from the top of the deck
 * This card is also removed from the deck
 * The blackjack value of the card is then returned by this method
 * The mapping for the cards is as follows:
 * 	  0 1 2 3 4 5 6 7 8 9 10 11 12
 * 	  Q K 2 3 4 5 6 7 8 9 10 A  J
 * Thus, any card < 2 or > 11 will be a value of 10
*/
int BJCardDeck::deal() {
	int toRemove = deck.size();						// always remove top card 
	int val = deck[toRemove] % 13;			// convert card to 0-12
	deck.pop_back();						// remove this random value from the deck
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
	for(int i = 0; i < originalDeckSize; i++) {
		deck.push_back(i);
	}
	(*this).shuffle();
}

/* This method will play blackjack
 * Simplifications are used such as ace = 11, dealer must hit until 17 or higher
 * A new deck will be used when the current deck reaches less than 15 cards. This is
 * handled internally inside the BJCardDeck class
*/
void BJCardDeck::play() {
	int dealerWins = 0;
	int playerWins = 0;
	int dealerFirstCard;		// remember dealer's first card. This is what the player gets to see
	char playAgain = '\0';		// takes on values of y or n for yes or no, user's selection
	char selection = '\0';		// takes on values of s or h for hit or stand, user's selection	

	while(1) {					// user can decide after each game to stop playing
		int dealerTotal = 0;
		int playerTotal = 0;
		bool playerIsDone = false;	// when true, player has won, gone over, or opted to stand
		bool dealerIsDone = false;	// when true, dealer has at least 17 or is over

		// give initial cards to dealer and player, dealer last
		for(int i = 0; i < 2; i++) {
			playerTotal+= deal();
			dealerTotal+= deal();
			if(i == 0) dealerFirstCard = dealerTotal;	// remember dealer's first card (flipped up)
		}

		// check the status of the initial deal in case either the dealer or player get 2 Aces
		if(playerTotal > 21 && dealerTotal > 21) cout << "Push - you and the dealer were dealt to Aces" << endl;
		else {
			if(playerTotal > 21) {
				cout << "You lost from the deal! Play again!" << endl;
				playerIsDone = dealerIsDone = true;		// don't want to enter the while loops below. Winner is already set
			} 
			if(dealerTotal >= 17) {		// check if dealer is already at/over 17
				dealerIsDone = true;
			}
			if(playerTotal == 21) {
				playerIsDone = true;	// check for natural
				cout << "You got a natural Blackjack!" << endl;
			}
		}

		// after the deal, the player goes first
		while(playerIsDone == false) {
			do {						// prompt user for hit or stand 
				cout << "Dealer's First Card: " << dealerFirstCard << ".   You: " << playerTotal << endl;
				cout << "   h: Hit, s: Stand: ";
				cin >> selection;
				selection = tolower(selection);		// convert to lower case in case entered as UC
				if(selection != 'h' && selection != 's') cout << "   Please enter 'h' or 's'" << endl;
			} while(selection != 'h' && selection != 's');
			if(selection == 'h') {
				playerTotal+= deal();		// give another card
			}
			if(playerTotal >= 21 || selection == 's') playerIsDone = true;	// check if done
		}

		// after the player's turn, if the player hasn't busted, the dealer goes
		while(dealerIsDone == false && playerTotal <= 21) {   // dealer will draw a card until total is 17 or higher
			dealerTotal+= deal();
			if(dealerTotal >= 17) dealerIsDone = true;	// dealer must be done
		}

		// check to see who won
		cout << "Dealer: " << dealerTotal << "  You: " << playerTotal << endl;	// display totals
		if(playerTotal > 21) {
			cout << "You went over 21! You lose this time." << endl;
			dealerWins++;
		} else if(dealerTotal > 21) {
			cout << "You win! The dealer went over 21!" << endl;
			playerWins++;
		} else if(dealerTotal == playerTotal) {
			cout << "It's a push...until next time!" << endl;
		} else if(playerTotal > dealerTotal) {
			cout << "You beat the dealer!" << endl;
			playerWins++;
		} else if(dealerTotal > playerTotal) {
			cout << "The dealer beat you! Try again." << endl;
			dealerWins++;	
		}

		// report scoring tallies and prompt user to play again
		cout << "SERIES: You: " << playerWins << ". Dealer: " << dealerWins << "." << endl;
		do {
			cout << "Would you like to play again? y:Yes   n:No: ";
			cin >> playAgain;
			playAgain = tolower(playAgain);
			if(playAgain != 'y' && playAgain != 'n') cout << "   Please enter 'y' or 'n'" << endl;
		} while(playAgain != 'y' && playAgain != 'n');

		// if player is done playing, display summary of game series
		if(playAgain == 'n') {
			cout << "SUMMARY: ";
			if(playerWins > dealerWins) cout << "You won the series ";
			else if(playerWins == dealerWins) cout << "You tied the series ";
			else cout << "You lost the series ";
			cout << playerWins << "-" << dealerWins << endl;	// in common with all scenarios
			break;						// quit
		}
	}
}
