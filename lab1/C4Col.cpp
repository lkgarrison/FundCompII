/* Luke Garrison, C4Col.cpp
 *
 * Implementation (.cpp) for C4Col class
 * Notable public methods: isFull(), getDisc(),
 * getMaxDiscs(), addDisc()
 *
 */

#include <iostream>
#include "C4Col.h"
using namespace std;

// default constructor, intialize variables
C4Col::C4Col() {
	nDiscs = 0;
	maxDiscs = 6;
	discs = new char[maxDiscs];			// dynamic memory allocation
	for(int i = 0; i < maxDiscs; i++) {	// initialize col spaces to be blank
		discs[i] = ' ';
	}
}

C4Col::~C4Col() {			// deconstructor
	delete [] discs;		// free memory used by array
}

// basically a boolean function, returns 1 if the column is full, 0 if not
int C4Col::isFull() {
	if(nDiscs == maxDiscs) return 1;
	else return 0;
}

// returns the player's piece in the specified row. Has input checking
char C4Col::getDisc(int row) {
	if(row < 0 || row > maxDiscs) {		// check for invalid row
		cout << "Row " << row << " is invalid" << endl;	
		return ' ';
	}
	return discs[row];
}

// returns the maximum number of discs for the column
int C4Col::getMaxDiscs() {
	return maxDiscs;
}

// returns the number of discs in this column
int C4Col::getNumDiscs() {
	return nDiscs;
}

// adds a disc to this column. checks for the column being full
void C4Col::addDisc(char newDisc) {
	if(isFull() == 1) {
		cout << "This column is full. Please try another column." << endl;	
		return;
	}
	discs[nDiscs++] = newDisc;   		// increment nDiscs and place newDisc in array
}
