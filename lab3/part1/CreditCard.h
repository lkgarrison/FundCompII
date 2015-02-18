#ifndef CREDITCARD_H
#define CREDITCARD_H

/* Luke Garrison, CreditCard.h
 * Interface for CreditCard class, derived from BankAccount
*/
#include <string>
#include "BankAccount.h"
using namespace std;

class CreditCard : public BankAccount {
	public:
		CreditCard();
		virtual void print();		// display information about CreditCard Account
		virtual void deposit(double);	// make a payment on credit card
		void addCharge(double);

	private:
		// one time specification
		int monthlyPaymentDueDate;	// due date for payment each month (ie 12th of every month)
		double interestRate;		// interest rate for unpaid balance

		// change monthly
		double minPayment;			// required minimum payment on montly charges
		double amountOwed;			// money owed to credit card company
};

#endif
