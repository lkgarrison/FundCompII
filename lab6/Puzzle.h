#ifndef PUZZLE_H
#define PUZZLE_H

/* Luke Garrison, Puzzle.h 
 * Templated Puzzle class
 * The public methods are play() and display()
 * The constructor requires that a valid file be specified as a starter for the puzzle
 * 
 * The solve method will determine the puzzle's values via the singleton algorithm as well
 * as finding cells with only a single possible value. 
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

template <typename T>
class Puzzle {
	public:
		Puzzle(int size = 9);	// constructor, size is the length of each side of the puzzle
		void solve();			// solve the puzzle
		void display();			// display puzzle

	private:
		void displayRowDashes();	// display a row of dashes to display puzzle nicely
		bool isValidRow(int row, T val);	// return true if row placement is valid
		bool isValidCol(int col, T val); 	// return true if col placement is valid
		bool isValidMiniGrid(int row, int col, T val);	// return true if minigrid placement is valid
		int countRemainingSpaces();			// number of remaining spaces. if == 0, player has won

		// helper functions for solve()
		void getPossibles(int row, int col);	// get possible vals for specific row, col. update possibleVals
		void getCellVal(int row, int col);		// try to determine value of cell
		int getSumPossibles(int row, int col);	// returns sum of indicies 1-9 of possibleVals
		void markKnownCell(int row, int col, int val); // update possibleVals vector when a cell is known
		void checkSingletons(int row, int col);	// find singletons to determine puzzles' values

		vector<vector <vector <int> > > possibleVals;	// 3D vector for possible vals
		int boardSize;						// size/length of each side of the board

		// instance variables to refer to 0=value not possible and 1=value is possible
		int NOT_POSSIBLE;	// in reference to indices 1-boardSize of possibleVals
		int POSSIBLE;
		int KNOWN;		// in reference to first index of 3rd dim of possibleVals, KNOWN = 1
		int UNKNOWN;	// in reference to first index of 3rd dim of possibleVals, UNKNOWN = 0
};

#endif

/* Constructor
 * Sets boardSize and also prompts for a valid file name for puzzle data.
 * Processes the data in the file to create a 2D vector w/ the puzzle data
*/
template <typename T>
Puzzle<T>::Puzzle(int size) {
	NOT_POSSIBLE = 0;			// refer to "NOT_POSSIBLE" instead of hard coding 0
	POSSIBLE = 1;				// refer to "POSSIBLE" instead of hard coding 1
	KNOWN = 1;					// in reference to first index of 3rd dim of possibleVals
	UNKNOWN = 0;

	boardSize = size;			// set private class variable
	string dataFile;			// file name of data file. must use c_str()
	T singlePuzzlePiece;		// store one piece before adding it to a row
	ifstream inFile;			// input file stream variable
	vector<vector <T> > puzzle;	// 2D vector to store puzzle data. Makes building 3D vec easier

	// get a valid data file for puzzle data from the user 
	while(1) {
		cout << "Enter a valid file name for the puzzle data: ";
		cin >> dataFile;
	
		//inFile(dataFile.c_str());	// input file stream object
		inFile.open(dataFile.c_str(), ios::in);
		if(inFile.good()) break;			// valid file name specified
		else cout << dataFile << " does not exist. Please try again." << endl;
	}

	// process puzzle input data file to create puzzle
	while(!inFile.eof()) {

		vector<T> row;							// add one row at a time
		for(int i = 0; i < boardSize; i++) {	// create 1 vector per row
			inFile >> singlePuzzlePiece;		// store next puzzle piece
			row.push_back(singlePuzzlePiece);	// add piece to row
		}
		
		// add each row to the ongoing puzzle board
		puzzle.push_back(row);
	}

	// Using original puzzle, build possibleVals 3-D vector to track cell solutions

	// create a vector of size boardSize + 1 with all one's
	vector<int> zeroAndOnes;	// initialize a vec: [0 1 1 1 1 .... 1]
	zeroAndOnes.push_back(0);	// zeroAndOnes[0] == 0 to symbolize cell is undecided
	for(int i = 0; i < boardSize; i++) {
		zeroAndOnes.push_back(1);		// fill the rest of the vec with one's
	}

	// create a vector of vectors of ints. Building up to possibleValues
	vector<vector <int> > secondDim;
	for(int i = 0; i < boardSize; i++) {
		secondDim.push_back(zeroAndOnes);
	}

	// adds the second dimension to create possible values. 
	for(int i = 0; i < boardSize; i++) {
		possibleVals.push_back(secondDim);
	}

	/* account for initial values in the original puzzle in the possibleVals vec
	if the initial puzzle has a given value, say 4, then we want the 3rd dimension vector
	to appear: [4 0 0 0 1 0 0 0 0 0]. The 0th element specifies the value of the cell, 
	as well as the 1 in the 5th index
	*/
	for(int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++) {
			if(puzzle[i][j] != UNKNOWN) { 			// if puzzle cell has an initial value
				// update possibleVals vector to reflect cell's value being known
				markKnownCell(i, j, puzzle[i][j]);	
			}
		}
	}

}

/* Solve the puzzle
 * Each cell in the puzzle will correspond to a "bit vector"
*/
template <typename T>
void Puzzle<T>::solve() {
	while(countRemainingSpaces() != 0) {		   	// while puzzle is not solved
		/* 	iterate through puzzle and check for cells that are still unknown. If so, update
			possible values (3rd dimension). Then try to solve for cell
		*/
		for(int i = 0; i < boardSize; i++) {		
			for(int j = 0; j < boardSize; j++) {
				if(possibleVals[i][j][0] == UNKNOWN) {	// if cell is unknown
					getPossibles(i, j);				// update possibleVals
					getCellVal(i, j);				// try to solve for cell
					checkSingletons(i, j);			// try to determine cells using singleton method
				}
			}
		}
		/* display 3D vector *
		for(int i = 0; i < boardSize; i++) {
			for(int j = 0; j < boardSize; j++) {
				cout << i+1 << "," << j+1 << ": ";
				for(int k = 0; k < boardSize + 1; k++) {
					cout << possibleVals[i][j][k] << " ";
				}
				cout << endl;
			}
		}
	
		display();
*/
	}
	
}

/* Search for singletons of every value. Search for them in the row, column, and minigrid of
 * the specified cell.
*/
template <typename T>
void Puzzle<T>::checkSingletons(int row, int col) {
	int nOccurances = 0;	// num occurances of val being possible in row/col/mini-grid
	int singletonRow;	// store row of potential singleton (in case nOccurances == 1)
	int singletonCol;	// store col of potential singleton

	// for every valid puzzle value	
	for(int val = 1; val <= boardSize; val++) {
		
	/* row singletons */
		for(int i = 0; i < boardSize; i++) {
			// if cell is unknown and "val" is possible
			if(possibleVals[row][i][0] == UNKNOWN && possibleVals[row][i][val] == POSSIBLE) {
				nOccurances++;	// count number of cells where val is possible

				// store potential singleton's location if and in case nOccurances == 1
				if(nOccurances == 1) {		
					singletonRow = row;
					singletonCol = i;
				}
			}
		}

		// check if val is a singleton or not
		if(nOccurances == 1 && isValidRow(singletonRow, val) && isValidCol(singletonCol, val) 
			&& isValidMiniGrid(singletonRow, singletonCol, val)) {

			// update possibleVals vector to reflect cell's value
			markKnownCell(singletonRow, singletonCol, val);
		}
		nOccurances = 0; // reset to 0 for next check

	/* column singletons */
		for(int i = 0; i < boardSize; i++) {
			// if cell is unknown and "val" is possible
			if(possibleVals[i][col][0] == UNKNOWN && possibleVals[i][col][val] == POSSIBLE) {
				nOccurances++;	// count number of cells where val is possible

				// store potential singleton's location if and in case nOccurances == 1
				if(nOccurances == 1) {		
					singletonRow = i;
					singletonCol = col;
				}
			}
		}

		// check if val is a singleton or not
		if(nOccurances == 1 && isValidRow(singletonRow, val) && isValidCol(singletonCol, val) 
			&& isValidMiniGrid(singletonRow, singletonCol, val)) {

			// update possibleVals vector to reflect cell's value
			markKnownCell(singletonRow, singletonCol, val);
		}
		nOccurances = 0; // reset to 0 for next check

	/* mini-grid singletons *
		int sqrtBoardSize = sqrt(boardSize);
		int topLeftX = row / sqrtBoardSize * sqrtBoardSize;		// utilize integer division, truncation
		int topLeftY = col / sqrtBoardSize * sqrtBoardSize;	

		// now that the top-left corner of the minigrid is known, check entire square
		for(int i = 0; i < sqrtBoardSize; i++) {
			for(int j = 0; j < sqrtBoardSize; j++) {
				// if cell is unknown and "val" is possible
				if(possibleVals[i][j][0] == UNKNOWN && possibleVals[i][j][val] == POSSIBLE) {
					nOccurances++;	// count number of cells where val is possible

					// store potential singleton's location if and in case nOccurances == 1
					if(nOccurances == 1) {		
						singletonRow = i;
						singletonCol = j;
					}
				}
			}
		}

		// check if val is a singleton or not
		if(nOccurances == 1 && isValidRow(singletonRow, val) && isValidCol(singletonCol, val) 
			&& isValidMiniGrid(singletonRow, singletonCol, val)) {

			// update possibleVals vector to reflect cell's value
			markKnownCell(singletonRow, singletonCol, val);
		}
*/
	}

}

/* Update possibleVals to reflect a known cell:
 * Set index 0 of 3rd dimension to the value
 * set all indicies except the value's index to 0
*/
template <typename T>
void Puzzle<T>::markKnownCell(int row, int col, int val) {
	possibleVals[row][col][0] = val;	// first index should be the value of the cell unless unknown

	// set all indicies except index val to 0 to reflect that they are no longer possible values
	for(int i = 1; i <= boardSize; i++) {
		if(i != val) possibleVals[row][col][i] = NOT_POSSIBLE;
	}
}

/* Get possible values for specified row, col. Update possibleVals
*/
template <typename T>
void Puzzle<T>::getPossibles(int row, int col) {
	for(int val = 1; val <= boardSize; val++) {
		// if val forms a valid row, col, and minigrid, update possibleVals
		if(isValidRow(row, val) && isValidCol(col, val) && isValidMiniGrid(row, col, val)) {
			possibleVals[row][col][val] = POSSIBLE;	// val is possible in this cell
		} else {						
			possibleVals[row][col][val] = NOT_POSSIBLE;	// value is NOT possible in this cell
		}
	}
}

/* Try to get cell's value
 * This method will currently only be able to determine the cell's value if its possibleVals
 * has only one entry
*/
template <typename T>
void Puzzle<T>::getCellVal(int row, int col) {
	if(getSumPossibles(row, col) == 1) {	// if sum of possibleVals == 1, there is only 1 possible val
		// find which val is the only possible value by iterating thru 3rd dim of possibleVals		
		for(int i = 1; i <= boardSize; i++) {
			if(possibleVals[row][col][i] == POSSIBLE) {
				// update possibleVals vector to reflect cell's value
				markKnownCell(row, col, i);
			}
		}
	}
}

/* Returns the sum of indicies 1-9 in the 3rd dimension of possibleVals for the given row,col
 * Important if sum == 1 (then cell's value is known)
*/
template <typename T>
int Puzzle<T>::getSumPossibles(int row, int col) {
	int sum = 0;		// initialize to 0

	// sum possibleVals for indicies 1-9
	for(int i = 1; i <= boardSize; i++) {
		sum+= possibleVals[row][col][i];
	}
	return sum;
}

/* Checks to see if the value is valid in the specified row
*/
template <typename T>
bool Puzzle<T>::isValidRow(int row, T val) {
	if((int)val == UNKNOWN) return true;		// there can be multiple 0's (blanks)

	// for every element in row, check if it matches val. if any do, row is NOT valid
	for(int i = 0; i < boardSize; i++) {
		if(possibleVals[row][i][0] == val) {	// value already exists in row
			return false;
		}
	}
	return true;			// if none of the values in the row matched, it is a valid row
}

/* Checks to see if the value is valid in the specified column
*/
template <typename T>
bool Puzzle<T>::isValidCol(int col, T val) {
	if((int)val == UNKNOWN) return true;		// there can be multiple 0's (blanks)

	// for every element in col, check if it matches val. if any do, row is NOT valid
	for(int i = 0; i < boardSize; i++) {
		if(possibleVals[i][col][0] == val) {	// value already exists in column
			return false;
		}
	}
	return true;		// if none of the values in the column matched, it is a valid row
}

/* Checks to see if the value is valid in the specified miniGrid
 * The key to this method is finding the row and col of the top left corner
 * of the minigrid that the (row,col) is in.
 * Then, every grid in the minigrid can be systematically checked against
 * the specified value to check if it is already in the minigrid
*/
template <typename T>
bool Puzzle<T>::isValidMiniGrid(int row, int col, T val) {
	if((int)val == UNKNOWN) return true;		// there can be multiple 0's (blanks)
	int sqrtBoardSize = sqrt(boardSize);
	int topLeftX = row / sqrtBoardSize * sqrtBoardSize;		// utilize integer division, truncation
	int topLeftY = col / sqrtBoardSize * sqrtBoardSize;	

	// now that the top-left corner of the minigrid is known, check entire square
	for(int i = 0; i < sqrtBoardSize; i++) {
		for(int j = 0; j < sqrtBoardSize; j++) {
			if(possibleVals[topLeftX + i][topLeftY + j][0] == val) {
				return false;	// value already exists in mini-grid
			}
		}
	}
	return true;		// if none of the values in the minigrid matched, it is a valid placement
}

/* Count remaining spaces in Puzzle. If there are 0, player has finished/won
 * Counts from the puzzle 3-D vector possibleVals
*/
template <typename T>
int Puzzle<T>::countRemainingSpaces() {
	int nRemaining = 0;	// keep track of empty spaces

	// count all 0's (empty spaces) on board
	for(int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++) {
			if((int)possibleVals[i][j][0] == NOT_POSSIBLE) {
				nRemaining++;
			}
		}
	}
	return nRemaining;
}
	

/* Will display each value in the puzzle separated by a space
 * Similar to a real puzzle, every mini-grid has a divider line 
*/
template <typename T>
void Puzzle<T>::display() {
	
	for(int i = 0; i < boardSize; i++) {	// iterate through every row

		// add a row of dashes every sqrt(boardSize) rows, including the top boarder 
		if(i % (int)sqrt(boardSize) == 0) {
			displayRowDashes();
		}

		// display each piece in the row
		for(int j = 0; j < boardSize; j++) {	// display each piece in the row
			if(j % (int)sqrt(boardSize) == 0) cout << "| ";	// |'s every sqrt(boardSize) cols, start at left
			if((int)possibleVals[i][j][0] == UNKNOWN) {	 // if puzzle value is a 0, display a blank space instead
				cout << "  ";					// display blank space since no piece yet
			} else {
				cout << possibleVals[i][j][0] << " ";	// display piece followed by space
			}
		}
		cout << "|" << endl;	// add right boarder and a newline after each row is displayed
	}
	displayRowDashes();		// bottom boarder of puzzle
}

/* display 1 row of dashes to make puzzle display look nicer
*/
template <typename T>
void Puzzle<T>::displayRowDashes() {
	int nExtras = sqrt(boardSize);	// beginning of board + each in-between vertical section
	for(int a = 0; a < boardSize + nExtras; a++) {
		cout << " -";		// display a row of dashes
	}
	cout << endl;			// newline to prepare for next row
}
