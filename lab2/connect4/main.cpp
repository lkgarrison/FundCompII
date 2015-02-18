/* Luke Garrison, main.cpp 
 *
 * This driver program demonstrates the ability to play another user or the computer,
 * based on the user's choice. 
 */

#include <ctype.h>	// for tolower()
#include <iostream>
#include "C4Board.h"
#include "C4Col.h"
using namespace std;

int main() {
	char playComputer;		// y = yes, n = no
	C4Board c4;	// instantiate an instance of a C4Board
	cout << "Do you wish to play Connect4 against the computer? Enter y/n: ";
	while(1) {  // ensure valid input
		cin >> playComputer;
		playComputer = tolower(playComputer);   // tolower helps simplify input checking
		if(playComputer == 'y' || playComputer == 'n') break;
		cout << "Please enter y/n: ";
	}

	if(playComputer == 'y') {
		c4.playComputer(); // can you beat the computer?
	} else {
		c4.play();	// play the game!	
	}
	
	return 0;
}
