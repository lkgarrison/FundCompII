/* Luke Garrison, BankAccount.cpp
 * Implementation for BankAccount class
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "BankAccount.h"
using namespace std;

/* Constructor
 * Create a random account number
*/
BankAccount::BankAccount() {		
	srand(time(NULL)); 	// initialize random number generator
	char numbers[] = "0123456789";	// string of possible digits
	int accountNumberLength = 9;	// number of digits in account number
	for(int i = 0; i < accountNumberLength; i++) {		// do the following accountNumberLength num times
		accountNumber.push_back(numbers[rand() % 10]);	// adds a random # to account #
	}
	setOwnerName("");
}

/* Print method. This is a pure virtual function, so it has limited functionality 
*/
void BankAccount::print() {
	//cout << "This account is valued at: $" << fixed << setprecision(2) << total << << "." << endlendl;
}

void BankAccount::deposit(double) {
	
}

/* Allows user to reset BankAccount pin
*/
void BankAccount::resetPin() {
	cout << "Please enter a new account PIN: ";
	cin >> pin;
}

/* Return account number
*/
string BankAccount::getAccountNumber() {
	return accountNumber;
}

/* Sets the name of the owner of the account 
*/
void BankAccount::setOwnerName(string name) {
	ownerName = name;
}

/* Gets the name of the owner of the account
*/
string BankAccount::getOwnerName() {
	return ownerName;
}
