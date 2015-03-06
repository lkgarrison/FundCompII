/* Luke Garrison, main.cpp
 * This driver program will demo the Puzzle class solving a 9x9 sudoku puzzle
*/

#include <iostream>
#include "Puzzle.h"
using namespace std;

int main() {
	cout << "Enter a file name for a sudoku puzzle:" << endl;
	Puzzle<int> sudoku;		// puzzle of int's = sudoku
	cout << "Initial Sudoku Puzzle:" << endl;	
	sudoku.display();

	cout << "Solved Sudoku Puzzle:" << endl;	
	sudoku.solve();
	sudoku.display();

}
