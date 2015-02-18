/* Luke Garrison, TwoDayShipping.cpp
 * Implementation for TwoDayPackage class, derived from Package
*/

#include <iostream>
#include "TwoDayPackage.h"
using namespace std;

/* Non-default constructor with fallback values
 * args: flat fee, plus weight and cost per ounce which are passed to Package constructor
*/
TwoDayPackage::TwoDayPackage(double flatFee, double weight, double costPerOunce) : Package(weight, costPerOunce) {
	if(flatFee < 0) {					// cannot have a engative cost
		cout << "Flat two day shipping fee cannot be less than 0. Using positive form of the number instead." << endl;
		flatFee*= -1;					// use positive cost instead of negative
	}	
	twoDayShippingFee = flatFee;		// flat fee parameter is the 2 day shipping fee
}

/* CalculateCost() will use base class' definition in its calculation, adding on 
 * the flat fee for 2-day shipping
*/
double TwoDayPackage::calculateCost() {
	return (Package::calculateCost() + twoDayShippingFee); 	// utilize base class' calcCost method for base cost
}

