#ifndef CREDITCARD_H
#define CREDITCARD_H

/* Luke Garrison, CreditCard.h
 * Interface for CreditCard class, derived from BankAccount
*/
#include <string>
#include "BankAccount.h"
using namespace std;

class CreditCard {
	public:
		CreditCard();			// default constructor
		~CreditCard();			// deconstructor
		void print();			// display information about CreditCard Account
		void deposit(double);	// make a payment on credit card
		void addCharge(double);	// add a charge to the credit card
		void setOwnerName(string);	// set owner name of the account

	private:
		// one time specification
		BankAccount *creditCard;	// This is where composition comes in
		int monthlyPaymentDueDate;	// due date for payment each month (ie 12th of every month)
		double interestRate;		// interest rate for unpaid balance

		// change monthly
		double minPayment;			// required minimum payment on montly charges
		double amountOwed;			// money owed to credit card company
};

#endif
