/* Luke Garrison, main.cpp
 * This program is used to demo the CreditCard and Savings classes, both of
 * which are derived from the base class BankAccount
*/

#include <iostream>
#include "CreditCard.h"
#include "Savings.h"
using namespace std;

int main() {
	cout << "Credit Card account:" << endl;
	CreditCard test;
	test.print();
	cout << "Add charge of $150.77" << endl;
	test.addCharge(150.77);
	test.setOwnerName("Luke");
	test.print();
	cout << "Make a despoit of $5.77 towards the charges" << endl;
	test.deposit(5.77);
	test.print();

	cout << endl << "Savings account:" << endl;
	Savings test2;
	test2.print();
	cout << "Deposit $100,000 into the savings account" << endl;
	test2.deposit(100000);
	test2.print();
	cout << "Withdraw $55.50 from the savings account" << endl;
	test2.withdraw(55.50);
	test2.print();
	cout << "Deposit $950,000 into the account, which will exceed maxSavings" << endl;
	test2.deposit(950000);	// deposit maxStorage. Special message expected
	test2.print();
	cout << "Account number: " << test2.getAccountNumber() << endl;	// display account number

	return 0;
}
