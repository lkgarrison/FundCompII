#ifndef C4BOARD_H
#define C4BOARD_H
/* Luke Garrison, C4Board.h
 * 
 * This is the interface for the Board class
 * Note: there are added helper functions, such as
 * getColumn(), isInBounds(). 
 */

#include "C4Col.h"

class C4Board {
	public: 
		C4Board();				// default constructor
		~C4Board();				// deconstructor
		void display();			// display the current board in text
		void play(); 			// allow 2 players to play a game
		void playComputer();	// allows a single player to play against the computer	
		

	private:
		int hasWon(char, int, int);	// private (helper) method to determine if either player has won.
							// return values: 1 = p1 won, 2 = p2 won, 0 = neither player has won
		bool isInBounds(int row, int col); 	// checks to see if specified row and col position is 
											// in bounds on board 
		void getColumn();	// helper function to get valid col selection from user for turn

		int numToWin;	 	// initialized to 4 for connect4		
		char p1Piece;		// will be set to 'X' in constructor
		char p2Piece;		// will be set to 'O' in constructor
		int turn;			// keeps track of turn number - ie whose turn it is
		int nCol;    		// number of columns on board
		int nFullCol;		// number of columns that are full. check when nFullCol == nCol
		int colDrop; 		// user's choice of column
		C4Col* board;		// array of C4Col columns that will comprise the board
};

#endif	
