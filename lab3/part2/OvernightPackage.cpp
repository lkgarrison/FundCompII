/* Luke Garrison, OvernightPackage.cpp
 * Implementation for OvernightPackage class, derived from Package
*/

#include <iostream>
#include "OvernightPackage.h"
using namespace std;

/* Non-default constructor w/ fallback value. Takes in extraCostPerOunce
 * This method will set the cost per ounce of this package object to include
 * the extra costPerOunce for OvernightPackages
 *  * args: extraCostPerOunce, plus weight and costPerOunce which are passed to Package constructor
*/
OvernightPackage::OvernightPackage(double extraCostByWeight, double weight, double costPerOunce) : Package(weight, costPerOunce) {
	if(extraCostByWeight < 0) {				// check for negative cost
		cout << "Extra Cost Per Ounce cannot be less than 0. The positive form of the number will be used instead." << endl;
		extraCostByWeight*= -1; 			// make negative cost positive
	}		
	extraCostPerOunce = extraCostByWeight;	// set instance var extraCostPerOunce = arg
	double initialCost = Package::getCostPerOunce();	// get costPerOunce
	Package::setCostPerOunce(initialCost + extraCostPerOunce);	// set costPerOunce to be the same + the extra cost per ounce
}

/* Overrides the calculateCost() method of the base class to include the 
 * exta cost of overnight shipment. The costPerOunce is adjusted in the constructor, before the 
 * calculateCost() method is called. 
*/
double OvernightPackage::calculateCost() {
	return Package::calculateCost();
}
