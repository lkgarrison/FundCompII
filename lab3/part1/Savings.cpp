/* Luke Garrison, Savings.cpp
 * Implementation for Savings class (derived from BankAccount)
*/

#include <iostream>
#include <iomanip>
#include "BankAccount.h"
#include "Savings.h"

/* Savings constructor. Also calls BankAccount constructor
*/
Savings::Savings(double initialSavings) : BankAccount() {	// call BankAccount constructor
	savings = initialSavings;
	maxSavings = 1000000;				// $1 million is the max amount a savings account can hold
}

/* Display basic account information
*/
void Savings::print() {
	cout << "You have saved " << fixed << setprecision(2) << savings << " dabloons in your savings account." << endl;
}

/* Make a depoist into the savings account
*/
void Savings::deposit(double amount) {
	if(amount >= 0) {	// check for valid deposit amount
		if((savings + amount) > maxSavings) { // if max storage is exceeded
			cout << "Ayy, ye remaining " << savings + amount - maxSavings << " dabloons could not be stored in this account. Ye savings have exceeded our holds. Ye have to open another account, or else ye can walk the plank." << endl;
			savings = maxSavings;
		} else savings+= amount;	
	} else cout << "You cannot deposit a negative number of dabloons!" << endl;
}

/* Withdraw from the savings account
*/
void Savings::withdraw(double amount) {
	if(amount > savings) { 	// if account has more savings than the requested withdrawal
		cout << "Avast! You do not have that many dabloons! Add more to your account, or else settle for less!" << endl;
	} else {
		savings -= amount;
	}
	return;
}
