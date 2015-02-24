/* Luke Garrison, main.cpp
 * This driver program will demonstrate the templated Puzzle class
 * The user will be prompted to provide a file with Sudoku data, the
 * sudoku will be displayed, and then a wordoku (using char's instead 
 * of int's) will be created and displayed from a wordoku data file.
 * 
*/

#include <iostream>
#include "Puzzle.h"
using namespace std;

int main() {
	cout << "Enter a file name for a sudoku puzzle:" << endl;
	Puzzle<int> sudoku;
	sudoku.display();
	
	cout << "Enter a file name for a wordoku puzzle:" << endl;	
	Puzzle<char> wordoku;
	wordoku.display();
}
