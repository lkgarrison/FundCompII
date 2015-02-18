/* Luke Garrison, demoCreditCard.cpp
 * This program will demo the composition version of the Credit Card class
 * It demonstrates the print, addCharge, setOwner, and deposit methods.
*/

#include <iostream>
#include "CreditCard.h"
using namespace std;

int main() {
	CreditCard test;
	test.print();
	cout << "Adding charge of $150.77" << endl;
	test.addCharge(150.77);
	cout << "Account owner name set to 'Luke'" << endl;
	test.setOwnerName("Luke");
	test.print();
	cout << "Deposit of $5.77 made" << endl;
	test.deposit(5.77);
	test.print();

	return 0;
}
