/* Luke Garrison, car.cpp
 *
 * Implementation (.cpp) file for Mortgage class
 * This file contains all of the same methods listed in the interface (.h) file,
 * But in this implementation (.cpp) file, the code is written for the methods.
 */

#include <iostream>
#include <iomanip>
#include "mortgage.h"    // reference to the class' interface file
using namespace std;

/* The constructor will provide input checking to ensure valid input */
Mortgage::Mortgage(double myPrincipal, double myRate, double myPayment) {
	principal = myPrincipal;   	// set private variables equal to constructor arguments
	rate = myRate;
	payment = myPayment;

	// validate constructor input	
	while(principal <= 0) {  // principal should be > $0
		cout << "Please enter a principal > $0: ";
		cin >> principal;
	}
	while(rate < 0) {
		cout << "Please enter a rate >= 0%: ";
		cin >> rate;
	}
	// guaranteed to have a good rate now:
	rate /= (100 * 12); // convert rate from % to decimal and from annual to monthly rate
	while(payment <= 0) {
			cout << "Please enter a payment > $0: ";
			cin >> payment;
	}
	while(principal * rate >= payment) { // check for payment too small
		cout << "This mortgage cannot be paid off with the selected payment." << endl;
		cout << fixed << setprecision(2) <<"Please enter a payment > $" << principal * rate << ": ";			
		cin >> payment;
	}
}

void Mortgage::credit(double payment) {
	principal -= payment;			// subtract payment from outstanding principal
}

double Mortgage::getPrincipal() {	// "getter" method, to get value of private variable
	return principal;
}

void Mortgage::amortize() {
	month = 1;
	printHeader(); // prints header row for amortization table
	while(principal > .001) {
		interest = principal * rate; // calculate interest
		principal += interest;		// add montly interst to payment BEFORE payment is made
		if(principal < payment) { 	// for the final payment to pay off 100%
			payment = principal;    // set payment to exactly the principal. 
		}
		principal -= payment;		// make payment on remaining principal
		cout << left << setw(7) << fixed << setprecision(2) << month <<
			setw(11) << payment <<
			setw(11) << interest <<
			setw(8) << principal << endl;	
		month++; 						// increment month
	}	
}

// private method will print out header row of amortization table
void Mortgage::printHeader() {
	cout << endl;	// give space before amortization table is printed
	cout << left << setw(7) << "Month" <<
		setw(11) << "Payment" <<
		setw(11) << "Interest" <<
		setw(8) << "Balance" << endl;
}	
