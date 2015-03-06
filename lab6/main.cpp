/* Luke Garrison, main.cpp
 * This driver program will demo the Puzzle class with a 9x9 sudoku.
 * This class will also work with a 16x16 puzzle.
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



	// uncomment the code below the test a 16x16 puzzle
	// Puzzle<int> bigSudoku(16);	// 16x16 sudoku
	// bigSudoku.play();
}
