/* Luke Garrison, blackjack.cpp
 * This program will utilize the BJCardDeck class to play blackjack
 * Simplifications are used such as ace = 11, dealer must hit until 17 or higher
 * A new deck will be used when the current deck reaches less than 15 cards
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include "BJCardDeck.h"

using namespace std;

int main() {
	srand(time(0));				// intialize random generator
	int minNumCards = 15;		// minumum number of cards in a deck before a new deck should be opened
	BJCardDeck deck(52);		// new deck of 52 cards
	int dealerWins = 0;
	int playerWins = 0;
	int dealerFirstCard;		// remember dealer's first card. This is what the player gets to see
	char playAgain = '\0';		// takes on values of y or n for yes or no, user's selection
	char selection = '\0';		// takes on values of s or h for hit or stand, user's selection	
	
	int dealerCard;


	while(1) {					// user can decide after each game to stop playing
		int dealerTotal = 0;
		int playerTotal = 0;
		bool playerIsDone = false;	// when true, player has won, gone over, or opted to stand
		bool dealerIsDone = false;	// when true, dealer has at least 17 or is over

		// give initial cards to dealer and player, dealer last
		for(int i = 0; i < 2; i++) {
			playerTotal+= deck.deal();
			dealerTotal+= deck.deal();
		}
		dealerFirstCard = dealerTotal;	// debugging purposes

		if(playerTotal > 21 && dealerTotal > 21) cout << "Push - you and the dealer were dealt to Aces" << endl;
		else if(playerTotal > 21) {
			cout << "You lost from the deal! Play again!" << endl;
			dealerWins++;
			playerIsDone = dealerIsDone = true;		// don't want to enter the while loops below. Winner is already set
		} else if(dealerTotal > 21) {
			cout << "The dealer lost from the deal! You win!" << endl;
			playerWins++;
			playerIsDone = dealerIsDone = true;		// winner is already determined
		}

		// after the deal, the player goes first
		while(playerIsDone == false) {
			do {						// prompt user for hit or stand 
				cout << "Dealer's First Card: " << dealerFirstCard << ".   You: " << playerTotal << endl;
				cout << "   h: Hit, s: Stand: ";
				cin >> selection;
				selection = tolower(selection);		// convert to lower case in case entered as UC
			} while(selection != 'h' && selection != 's');
			if(selection == 'h') {
				playerTotal+= deck.deal();		// give another card
/* new deck */	if(deck.getSize() < minNumCards); //
			}
			if(playerTotal >= 21 || selection == 's') playerIsDone = true;	// check if done
		}

		// after the player's turn, if the player hasn't busted, the dealer goes
		while(dealerIsDone == false && playerTotal <= 21) {   // dealer will draw a card until total is 17 or higher
/* new deck */if(deck.getSize() < minNumCards);
			dealerCard = deck.deal();
			cout << "New dealer card: " << dealerCard << endl;
			dealerTotal+= dealerCard;
			if(dealerTotal >= 17) dealerIsDone = true;	// dealer must be done
		}

		// check to see who won
		cout << "Dealer: " << dealerTotal << "  You: " << playerTotal << endl;	// display totals
		if(playerTotal > 21) {
			cout << "You went over 21! You lose this time." << endl;
			dealerWins++;
		} else if(dealerTotal > 21) {
			cout << "You win!" << endl;
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
	
	return 0;
}
