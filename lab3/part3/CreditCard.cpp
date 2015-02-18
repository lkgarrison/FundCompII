/* Luke Garrison, CreditCard.cpp 
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "BankAccount.h"
#include "CreditCard.h"

using namespace std;

/* constructor. creates a new BankAccount object
*/
CreditCard::CreditCard() {
	creditCard = new BankAccount();		// composition. Create a BankAccount object within CreditCard class
	srand(time(NULL));		// initialize random num generator
	monthlyPaymentDueDate = rand() % 29;	// max date = 28th, b/c of Feb. Returns 0-28. Can't be 0 though
	if(monthlyPaymentDueDate == 0) monthlyPaymentDueDate++;	// don't let due date be the 0th of the month
	interestRate = .16;
	amountOwed = 0;			// start with a clean slate
}

/* Deconstructor. Frees memory used to create BankAccount object
*/
CreditCard::~CreditCard() {
	delete creditCard;
}

/* displays general account information
*/
void CreditCard::print() {
	if(((*creditCard).getOwnerName()).length() > 0)
		cout << (*creditCard).getOwnerName() << ", you ";
	else cout << "You ";

	cout << "must pay a minimum of " << fixed << setprecision(2) << minPayment 
		 << " dabloons on your " << amountOwed << " dabloon remaining balance " << monthlyPaymentDueDate 
		 << " days after the next month begins." << endl;
}

/* Make deposit on credit card monthly bill
*/
void CreditCard::deposit(double payment) {
	if(payment < 0) {			// check for negative payment amoutn
		cout << "Cannot make a payment with a negative number of dabloons" << endl;
		return;
	}
	amountOwed -= payment;		// make payment on amount owed. Could make amount owed negative (surplus)
	minPayment = .25 * amountOwed;	// adjust minPayment based on amountOwed
}

/* Add charge to amountOwed
*/
void CreditCard::addCharge(double charge) {
	if(charge < 0) { 			// check for negative charge
		cout << "Cannot add a charge for a negative number of dabloons" << endl;
		return;
	}
	amountOwed += charge;		// add charge to amount owed
	minPayment = .25 * amountOwed;	// adjust minPayment based on amountOwed
}

/* Set owner's name through BankAccount setter method
*/
void CreditCard::setOwnerName(string name) {
	(*creditCard).setOwnerName(name);	// call setter for BankAccount
}





