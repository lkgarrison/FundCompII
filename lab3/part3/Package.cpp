/* Luke Garrison, Package.cpp
 * Implementation for Package class
*/

#include <iostream>
#include "Package.h"
using namespace std;

/* Non-default constructor w/ fallback values. Utilizes set methods for weight and cost/ounce
*/
Package::Package(double myWeight, double myCost) {
	setWeight(myWeight);		// utilize setter for error checking
	setCostPerOunce(myCost);	
}

/* Returns the cost to ship the package: weight * costPerOunce
*/
double Package::calculateCost() {
	return (weight * costPerOunce);
}

/* Set weight to the myWeight. Perform error checking on argument myWeight
*/
void Package::setWeight(double myWeight) {
	if(myWeight < 0) {		// if myWeight is neg, display error msg and use positive form
		cout << "Package cannot have a negative weight. Using the specified weight as a positive number instead" << endl;
		myWeight*= -1;		// make weight positive
	}
	weight = myWeight;
}

/* Set the costPerCounce to cost parameter. Perform error checking on the argument
*/
void Package::setCostPerOunce(double cost) {
	if(cost < 0) { 			// if cost is neg, display error msg and use positive form
		cout << "Cost per ounce cannot be negative. Using the specified cost as a positive number instead" << endl;
		cost*= -1;			// make cost postive
	}
	costPerOunce = cost;
}

/* Simple getter method to return costPerOunce. Allows Overnight Package to adjust costPerOunce via setCostPerOunce
*/
double Package::getCostPerOunce() {
	return costPerOunce;
}

/* Returns the recipient's name
*/
string Package::getName() {
	return nameRecipient;
}

/* Return the shipping address of the package
*/
string Package::getAddress() {
	return addressRecipient;
}

/* Set the recipient name of the package
*/
void Package::setName(string name) {
	nameRecipient = name;
}

/* Set the address of the recipient of the package
*/
void Package::setAddress(string address) {
	addressRecipient = address;
}	







