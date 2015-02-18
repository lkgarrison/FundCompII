#ifndef SAVINGS_H
#define SAVINGS_H

/* Luke Garrison, Savings.h
 * Interface for derived class Savings (inherited from BankAccount)
*/

#include "BankAccount.h"
using namespace std;

class Savings : public BankAccount {
	public:
		Savings(double = 0);		// nondefault constructor w/ fallback value of 0
		virtual void print();		// print a summary of the savings account
		virtual void deposit(double);	// deposit money into the account
		void withdraw(double);		// withdraw an amount from you account
			
	private:
		double savings;				// amount of money saved in account
		double maxSavings;			// max amount of money the savings account can hold
		
};

#endif
