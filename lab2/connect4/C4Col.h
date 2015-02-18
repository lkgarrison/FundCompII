#ifndef C4COL_H
#define C4COL_H
/* Luke Garrison, C4Col.h
 *
 * This is the interface (.h) file for the C4Col class
 * As a note, a public method, getNumDiscs() has been added to return the number
 * of discs in teh column. This was very useful in helping determine what row the 
 * disc that was just dropped in the column is in (for the helper method hasWon()
 *
 */

#include <iostream>

class C4Col {
	public:
		C4Col();			// default constructor
		~C4Col();			// deconstructor
		C4Col(const C4Col & C4ColToCopy); // copy constructor		
		int isFull();		// determines if column is full
		char getDisc(int);	// returns the requested element of the priate char array
		int getMaxDiscs(); 	// returns the max number of discs (# rows)
		int getNumDiscs();	// returns nDiscs, the number of discs in the column
		void addDisc(char);	// adds the character representing a disc to the next open slot
		C4Col operator+=(char);	// overload += operator to make adding a disc simpler
		
	private:
		int nDiscs;		// stores number of discs in column
		int maxDiscs;	// max discs allowed in col (ie number of rows)
		char* discs;	// char array to store representation of each players' discs
};

#endif
