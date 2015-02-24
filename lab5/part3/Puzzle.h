#ifndef PUZZLE_H
#define PUZZLE_H

/* Luke Garrison, Puzzle.h 
 * Templated Puzzle class
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

template <typename T>
class Puzzle {
	public:
		Puzzle(int size = 9);	// constructor, size is the length of each side of the puzzle
		void play();			// play the puzzle
		void display();			// display puzzle

	private:
		void displayRowDashes();	// display a row of dashes to display puzzle nicely
		bool isValidRow(int row, T val);	// return true if row placement is valid
		bool isValidCol(int col, T val); 	// return true if col placement is valid
		bool isValidMiniGrid(int row, int col, T val);	// return true if minigrid placement is valid
		int countRemainingSpaces();			// number of remaining spaces. if == 0, player has won

		vector<vector <T> > originalPuzzle;	// original puzzle as specified by the input file
		vector<vector <T> > puzzle;			// 2D vector to store puzzle data
		int boardSize;						// size/length of each side of the board
};

#endif

/* Constructor
 * Sets boardSize and also prompts for a valid file name for puzzle data.
 * Processes the data in the file to create a 2D vector w/ the puzzle data
*/
template <typename T>
Puzzle<T>::Puzzle(int size) {
	boardSize = size;			// set private class variable
	string dataFile;			// file name of data file. must use c_str()
	T singlePuzzlePiece;		// store one piece before adding it to a row
	ifstream inFile;			// input file stream variable

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
			cout << singlePuzzlePiece << endl;
			row.push_back(singlePuzzlePiece);	// add piece to row
		}
		
		// add each row to the original 2-D puzzle board and the ongoing puzzle board
		originalPuzzle.push_back(row);
		puzzle.push_back(row);
	}

}

/* Allow user to play the puzzle game
*/
template <typename T>
void Puzzle<T>::play() {

	display();

	int row, col;
	T val;			// new value to place in specified cell
	int sentinel = -1;		// sentinel value to trigger doQuit flag
	bool doQuit = false;	// flag to quit if user desires (triggered by val of SENTINEL)

	cout << "Enter " << sentinel << " at any time to quit, and use a value of 0 to erase the specified cell" << endl;

	while(!doQuit) {
		// get valid row
		while(!doQuit) {				
			cout << "   Row: ";
			cin >> row;
			if(row == sentinel)	doQuit = true;	// check if user wants to quit
			row--;				// allow user to input rows 1 - n, instead of 0 - (n-1)
			if(row >= 0 && row < boardSize || doQuit) break;	// valid entry
			cout << "Please enter a valid row" << endl;
		}
		
		// get valid col
		while(!doQuit) { 
			cout << "   Col: ";
			cin >> col;
			if(col == sentinel) doQuit = true;	// check if user wants to quit
			col--;				// allow user to input cols 1 - n, instead of 0 - (n-1)
			if(col >= 0 && col < boardSize || doQuit) break;	// valid entry
			cout << "Please enter a valid column" << endl;
		}

		// check if specified piece can be changed (was it an original piece, part of data file?)
		if(!doQuit && (int)originalPuzzle[row][col] != 0) {
			cout << "You cannot change this puzzle piece because it is from the original puzzle." << endl;
			continue;
		}

		// get valid value
		while(!doQuit) {
			cout << "   New value: ";
			cin >> val;
			if(val == sentinel) doQuit = true;				// check if user wants to quit
			if(val >= 0 && val <= boardSize || doQuit) break;	// valid entry
			cout << "Please enter a valid value between from 0-" << boardSize << " or the sentinel value." << endl;
		}

		if(doQuit) break;	// if user entered sentinel value, quit
		
		// check if puzzle is done
		if(!isValidRow(row, val)) continue;		// check if entered value already exists in the row
		if(!isValidCol(col, val)) continue;		// check if entered value already exists in the column
		if(!isValidMiniGrid(row, col, val)) continue;	// check if entered value already exists in the mini-grid

		// at this point, location and value must be valid, so place the piece and redisplay board		
		puzzle[row][col] = val;
		display();
		if(countRemainingSpaces() == 0) break;	// player has won/finished puzzle
	}

	// check if player completed puzzle or not
	if(countRemainingSpaces() == 0) {
		cout << "You successfully completed the puzzle! Congratulations! Try a harder one next!" << endl;
	} else {
		cout << "You have given up. Try again later!" << endl;
	}
}

/* Checks to see if the value is valid in the specified row
*/
template <typename T>
bool Puzzle<T>::isValidRow(int row, T val) {
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	// for every element in row, check if it matches val. if any do, row is NOT valid
	for(int i = 0; i < boardSize; i++) {
		if(puzzle[row][i] == val) {
			cout << "Error: " << val << " already exists in row " << row + 1 << "." << endl;
			return false;
		}
	}
	return true;			// if none of the values in the row matched, it is a valid row
}

/* Checks to see if the value is valid in the specified column
*/
template <typename T>
bool Puzzle<T>::isValidCol(int col, T val) {
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	// for every element in col, check if it matches val. if any do, row is NOT valid
	for(int i = 0; i < boardSize; i++) {
		if(puzzle[i][col] == val) {
			cout << "Error: " << val << " already exists in column " << col + 1 << "." << endl;
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
	if((int)val == 0) return true;		// there can be multiple 0's (blanks)

	int topLeftX = row / 3 * 3;		// utilize integer division, truncation
	int topLeftY = col / 3 * 3;	

	// now that the top-left corner of the minigrid is known, check entire square
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(puzzle[topLeftX + i][topLeftY + j] == val) {
				cout << "Error: " << val << " already exists in that mini-grid." << endl;
				return false;
			}
		}
	}
	return true;		// if none of the values in the minigrid matched, it is a valid placement
}

/* Count remaining spaces in Puzzle. If there are 0, player has finished/won
 * Assumes an empty space == 0
*/
template <typename T>
int Puzzle<T>::countRemainingSpaces() {
	int nRemaining = 0;	// keep track of empty spaces

	// count all 0's (empty spaces) on board
	for(int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++) {
			if((int)puzzle[i][j] == 0) {
				nRemaining++;
			}
		}
	}
	return nRemaining;
}
	

/* Will display each value in the puzzle separated by a space
 * Similar to a real puzzle, every 
*/
template <typename T>
void Puzzle<T>::display() {
	system("clear");	// clear screen so puzzle is displayed at the top

	displayRowDashes();	// top boarder of puzzle		

	for(int i = 0; i < boardSize; i++) {	// iterate through every row

		// add a row of dashes every sqrt(boardSize) rows
		if(i % (int)sqrt(boardSize) == 0 && i != 0) {
			displayRowDashes();
		}

		// display each piece in the row
		for(int j = 0; j < boardSize; j++) {	// display each piece in the row
			if(j == 0) cout << "| ";			// display left boarder of puzzle
			if(j % (int)sqrt(boardSize) == 0 && j != 0) cout << "| ";	// |'s every sqrt(boardSize) cols
			if((int)puzzle[i][j] ==	0) {		// if puzzle value is a 0, display a blank space instead
				cout << "  ";					// display blank space since no piece yet
			} else {
				cout << puzzle[i][j] << " ";	// display piece followed by space
			}
			if(j == boardSize - 1) cout << "|";	// display right boarder of puzzle
		}
		cout << endl;	// add a newline after each row is displayed
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

/* backup
void Puzzle<T>::display() {
	for(int i = 0; i < boardSize; i++) {	// iterate through every row

		// add a row of dashes every sqrt(boardSize) rows
		if(i % (int)sqrt(boardSize) == 0 && i != 0) {
			for(int a = 0; a < boardSize + 2; a++) {
				cout << "- ";		// display a row of dashes
			}
			cout << endl;			// newline to prepare for next row
		}

		// display each piece in the row
		for(int j = 0; j < boardSize; j++) {	// display each piece in the row
			if(j % (int)sqrt(boardSize) == 0 && j != 0) cout << "| ";	// |'s every sqrt(boardSize) cols
			if((int)puzzle[i][j] ==	0) {		// if puzzle value is a 0, display a blank space instead
				cout << "  ";					// display blank space since no piece yet
			} else {
				cout << puzzle[i][j] << " ";	// display piece followed by space
			}
		}
		cout << endl;	// add a newline after each row is displayed
	}
}
*/
