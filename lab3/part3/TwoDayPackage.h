#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H

/* Luke Garrison, TwoDayPackage.h
 * Interface for TwoDayPackage.h, derived class of Package
*/

#include "Package.h"

using namespace std;

class TwoDayPackage : public Package {
	public:
		// non-default constructor w/ fallback value of 2 for flat fee, same defaults as Package for weight and cost/ounce
		TwoDayPackage(double flatFee=2, double weight=16, double costPerOunce=0.1);
		double calculateCost();		// calculate cost of shipping a two day package

	private:
		double twoDayShippingFee; 	// flat fee for 2 day shipping

};

#endif
