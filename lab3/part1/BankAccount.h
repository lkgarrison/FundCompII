#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

/* Luke Garrison, BankAccount.h
 * Interface for BankAccount class. This is an abstract class
*/
#include <string>
using namespace std;

class BankAccount {
	public:
		BankAccount();	// default constructor
		virtual void print() = 0;		// print function to print relevant account info. pure virtual function
		virtual void deposit(double) = 0;	// make a deposit on the account		
		void resetPin();				// allows account pin to be reset
		string getAccountNumber();		// returns account number
		void setOwnerName(string);		// allow account owner's name to be specified
		string getOwnerName();			// return owner's name

	private:
		string accountNumber;	// account number
		string ownerName;		// name of the owner of the account
		int pin;				// account pin to access account
};

#endif
