#ifndef PUZZLE_H
#define PUZZLE_H

/* Luke Garrison, Puzzle.h 
 * Templated Puzzle class
 */

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

template <typename T>
class Puzzle {
	public:
		Puzzle(int size = 9);	// constructor, size is the length of each side of the puzzle
		void display();			// display puzzle

	private:
		vector<vector <T> > puzzle;		// 2D vector to store puzzle data
		int boardSize;					// size/length of each side of the board

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
			row.push_back(singlePuzzlePiece);	// add piece to row
		}
	
		puzzle.push_back(row);	// add each row to the 2D puzzle board
	}
}

/* Will display each value in the puzzle separated by a space
*/
template <typename T>
void Puzzle<T>::display() {
	for(int i = 0; i < boardSize; i++) {		// iterate through every row
		for(int j = 0; j < boardSize; j++) {	// display each piece in the row
			cout << puzzle[i][j] << " ";		// display piece followed by space
		}
		cout << endl;	// add a newline after each row is displayed
	}
}
	

