/* Luke Garrison, main.cpp
 *
 * This program will serve as a driver program for the Mortgage class. 
 * It will demonstrate the public methods of the Mortgage class, including
 * printing out an amortization table.
 *
 * This program intentionally initializes mortgages with invalid input to demo
 * the constructor's input validation steps.
 */

#include <iostream>
#include "mortgage.h"
using namespace std;

int main() {

	Mortgage first(10000, 5.0, 500);	// uses non-default initializeation; for 2b
	Mortgage second;					// uses default constructor, mortgage of $150k, for 2c
	cout << "DEMO: The following mortgage object has too small of a payment. It will need to be raised:" << endl;
	Mortgage third(150000, 5, 250);		// payment is too small - demo
	cout << "DEMO: The following mortgage object has intentionally been set with all invalid values for the principal, rate, and payment. Prompts will occur to adjust:" << endl;
	Mortgage fourth(-50000, -3, -500);  	// non-default; all values are invalid. prompts to correct will occur. doemo of error checking
	
	// demonstrate functions requested in 2d
	second.credit(10000); // credit 10,000
	cout << "Current balance after crediting second mortgage 10K: " << second.getPrincipal() << endl; // should be 140K
	
	cout << "Amortization schedule for first mortgage:" << endl;
	first.amortize(); 		// print the amortization schedule for the fist mortgage
	cout << endl << "Amortization schedule for fourth mortgage:" << endl;
	fourth.amortize();
	
	return 0;
}
