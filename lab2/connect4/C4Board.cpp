/* Luke Garrison, C4Board.cpp
 * 
 * This is the implementation for the C4Board Class
 * The notable public methods are:
 * 		play() and display()
 * It uses 3 (private) helper functions: 
 * 		isInBounds(), getColumn() and hasWon()
 *
 */
#include <iostream>
#include <iomanip>
#include <stdlib.h>			// used to clear screen (system("clear"))
#include <stdlib.h>			// for srand
#include <time.h>			// for srand
#include "C4Board.h"
#include "C4Col.h"
using namespace std;

C4Board::C4Board() {
	nCol = 7;		// standard for Connect4 board
	nFullCol = 0; 	// intialized to 0
	turn = 1; 		// start with player 1 being first
	numToWin = 4;	// it is connect 4, after all
	p1Piece = 'X'; 
	p2Piece = 'O';
	board = new C4Col[nCol]; // set size of dynamically allocated array
}

C4Board::~C4Board() {		// deconstructor
	delete [] board; 		// free memory allocated via new when creating board
}

// copy constructor, because of new/delete
C4Board::C4Board(const C4Board & C4BoardToCopy) {
	nCol = C4BoardToCopy.nCol;
	nFullCol = C4BoardToCopy.nFullCol;
	turn = C4BoardToCopy.turn;
	numToWin = C4BoardToCopy.numToWin;
	p1Piece = C4BoardToCopy.p1Piece;
	p2Piece = C4BoardToCopy.p2Piece;
	board = new C4Col[nCol];
}

/* overloaded << operator to enable "cout << *this << endl;"
 Will display the contents of each row, from the top of the board downward, left --> right
*/
ostream &operator<<( ostream & output, const C4Board & myBoard) {
	for(int h = 0; h < myBoard.nCol; h++) output << " " << h << "  "; // print col #'s
	output << endl; // newline

	// iterate accross hole board, from top left to bottom right
	for(int i = myBoard.board[0].getMaxDiscs() - 1; i >= 0; i--) { // top of cols, downward
		for(int j = 0; j < myBoard.nCol; j++) {		// for each disc space in each row
			output << " " << myBoard.board[j].getDisc(i);
			if(j < myBoard.nCol - 1) output << " |";	// only place |'s btwn columns
		}
		output << endl;
	}
	return (output);
}


/* function to get valid column selection from either p1 or p2, depending on turn 
 */
void C4Board::getColumn() {
	while(1) {			// ensure valid user input
		cout << (turn % 2 == 1 ? "p1(X)" : "p2(O)")<< ": "; 	// display player's turn at bottom
		cin >> colDrop;											// take in column to drop 
		if(colDrop >= -1 && colDrop < nCol) {	// valid column entered
			if(colDrop != -1 && board[colDrop].isFull() == 1) {
				cout << "This column is full. Please select another column." << endl;
				continue;	// this way, turn won't be incremented
			}
			break;   	// -1 is also valid because it ends game
		}			
		cout << "Please enter a valid column:" << endl; // non-existant column entered if here
	}
}

/* ensures valid column selection, checks user's choice, and if choice is not to quit,
 drops disc in column. Then calls hasWon() to check if player has won or not.
*/
void C4Board::play() {
	int winner = 0;			// stores 1 if p1 wins, 2 if p2 wins
	int curPiece;			// stores 'X' or 'O', depending on turn
	int nDiscsInCol;		// stores number of discs in the column, sent to hasWon()

	system("clear");		// clear screen
	cout << "Select a column number to place a disc. Enter -1 to end the game" << endl;
	cout << *this << endl;
	while(1) {	
		getColumn();			// gets valid column selection, stored in colDrop
		if(colDrop == -1) {   	// user ended game
			cout << "Game ended" << endl;
			break;		
		} else {				// valid col entered, drop disc
			system("clear");								// clear screen
			curPiece = (turn % 2 == 1) ? p1Piece : p2Piece;	// current piece set based on turn
			board[colDrop]+=curPiece;		  				// X for p1, 0 for p2
			if(board[colDrop].isFull() == 1) {				// if recent drop made column full
				nFullCol++;									// incrememnt full column counter
				if(nFullCol == nCol) {						// check for full board
					cout << *this << endl;
					cout << "It's a draw!" << endl;
					return;
				}
			}
			turn++;			// effectively switches whose turn it is
			winner = hasWon(curPiece, board[colDrop].getNumDiscs() - 1, colDrop);	// pass which player, and what row and col piece went in
			cout << *this << endl;
			if(winner == 1) cout << "Player 1, congratulations, you win!" << endl;
			else if(winner == 2) cout << "Player 2, congratulations, you win!" << endl;
			if(winner != 0) return;							// game over. either p1 or p2 won
		}		
	}
}

/* similar to play() method
 * when it is p2's turn, the computer will randomly choose a non-full column
 * to drop a disc into
 */
void C4Board::playComputer() {
	int winner = 0;			// stores 1 if p1 wins, 2 if p2 wins
	int curPiece;			// stores 'X' or 'O', depending on turn
	int nDiscsInCol;		// stores number of discs in the column, sent to hasWon()
	srand(time(NULL));		// initialize random number generator

	system("clear");
	cout << "Select a column number to place a disc. Enter -1 to end the game" << endl;
	cout << *this << endl;
	while(1) {	
		if(turn % 2 == 0) {			// computer's turn
			curPiece = p2Piece;
			do {
				colDrop = rand() % 7; 	// choose a random column
			} while(board[colDrop].isFull() == 1);	// ensure column is not full
		} else {					// user's turn
			getColumn();				// gets valid column, placed in private variable colDrop
			if(colDrop == -1) {   		// user ended game
				cout << "Game ended" << endl;
				break;		
			} else {					// valid col entered, drop disc
				curPiece = p1Piece;		// current piece set based on turn
			}
		}

		// for both user and computer's turn:
		system("clear");										// clear screen
		board[colDrop]+=curPiece;	  							// X for p1, 0 for p2
		if(board[colDrop].isFull() == 1) {						// if this col is now full after dropping
			nFullCol++;											// incrememnt nFullCol
			if(nFullCol == nCol) {								// check for full board
				cout << *this << endl;
				cout << "It's a draw!" << endl;
				return;
			}
		}
		turn++;					// effectively switches whose turn it is
		winner = hasWon(curPiece, board[colDrop].getNumDiscs() - 1, colDrop);	// pass which player, and what row and col piece went in
		cout << *this << endl;
		if(winner == 1) cout << "Player 1, congratulations, you win!" << endl;
		else if(winner == 2) cout << "The computer wins...Try again!" << endl;
		if(winner != 0) return;									// game over. either p1 or computer won
	}
}


/* private (helper) method to determine if either player has won.
 return values: 1 = p1 won, 2 = p2 won, 0 = neither player has won
 Will check horizontally, then vertically, then diagonally
 checks only the player that just played (curPiece)
 */ 
int C4Board::hasWon(char curPiece, int row, int col) {
	int tempRow;				// temporary row location. used in traversing a line of 4 spaces on board
	int tempCol;				// used in traversing a line of 4 spaces on board
	int curTally = 0;			// keeps track of whether or not there are 4 in a row for curPiece
	
	/* check horizontally, only around the newly placed piece
	 idea: start at offset left of added piece. check to see if 4 in a row are for the player.
	 if not, start one closer to new piece, and repeat until you start at new piece and not 4 in a row
	*/
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	// horizontal offset from col of disc drop
		curTally = 0;												// then reset tally		
		for(int i = 0; i < numToWin; i++) {							// check all 4 in line starting w/ offset
			tempCol = col + offset + i;								// "curCol" being checked
			if(isInBounds(row, tempCol) == false) break; 	// avoid out of bounds array access
			
			if(board[tempCol].getDisc(row) == curPiece) {  // if player has piece here, tally it
		  		if(++curTally == numToWin) {			// check if player has 4 in a row
					if(curPiece == p1Piece) return 1;	// return which player has 4 in a row
					else return 2;
		  		} 
			} else {									// if current piece isn't a match for playe
				break;			
			}
		}
	}
	
	// check vertically, only around the newly placed piece
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	// vertical offset from row of disc drop
		curTally = 0;												// ensure counter reset
		for(int i = 0; i < numToWin; i++) {							// check all 4 in line starting w/ offset
			tempRow = row + offset + i;						 	// reduce repetive code. "curRow"
			if(isInBounds(tempRow, col) == false) break; 		// avoid out of bounds array access
			
			if(board[col].getDisc(tempRow) == curPiece) {		// if player has piece here, tally it
				if(++curTally == numToWin) {					// check if player has 4 in a row
					if(curPiece == p1Piece) return 1;			// return which player has 4 in a row
					else return 2;
				}
			} else {
				break;
			}
		}
	}

	// check diagonlly, only around the newly placed piece
	// first: lower left to upper right diagonal
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	// vertical offset from row of disc drop
		curTally = 0;												// for reset of tally
		for(int i = 0; i < numToWin; i++) {							// check all 4 in line starting w/ offset
			tempRow = row + offset + i;							// reduce repetive code. "curCol/Row"
			tempCol = col + offset + i;
			if(isInBounds(tempRow, tempCol) == false) break; 	// avoid out of bounds array access
			if(board[tempCol].getDisc(tempRow) == curPiece) {	// if player has piece here, tally it
				if(++curTally == numToWin) {					// check if player has 4 in a row
					if(curPiece == p1Piece) return 1;			// return which player has 4 in a row
					else return 2;
				}
			} else {
				break;
			}
		}
	}

	// diagonal check #2
	// next: lower right to upper left (opposite diagonal)
	for(int offset = -1 * numToWin + 1; offset <= 0; offset++) {	// vertical offset from row of disc drop
		curTally = 0;												// force reset of tally	
		for(int i = 0; i < numToWin; i++) {							// check all 4 in line starting w/ offset
			tempRow = row + offset + i;							// reduce repetive code. "curCol/Row"
			tempCol = col - offset - i;
			if(isInBounds(tempRow, tempCol) == false) break; 	// avoid out of bounds array access
			if(board[tempCol].getDisc(tempRow) == curPiece) {	// if player has piece here, tally it
				if(++curTally == numToWin) {					// check if player has 4 in a row
					if(curPiece == p1Piece) return 1;			// return which player has 4 in a row
					else return 2;
				}
			} else {
				break;
			}
		}
	}
	return 0;										// if no winner yet
}


/* checks to see if specified row and col position is in bounds on board */
bool C4Board::isInBounds(int row, int col) {
	if(row >= 0 && row < board[0].getMaxDiscs() && col >= 0 && col < nCol) return true;
	else return false;
}


