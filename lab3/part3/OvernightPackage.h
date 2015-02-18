#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H

/* Luke Garrison, OvernightPackage.h
 * Interface for OvernightPackage class, derviced from Package
*/

#include "Package.h"
using namespace std;

class OvernightPackage : public Package {
	public:
		/* non-default constructor w/ fallback values. weight and costPerOunce are passed to Package constructor
		*  unless specified, extraCostPerOunce = 20 cents. weight and costPerOunce are same as Package fallback values */
		OvernightPackage(double myExtraCostPerOunce=.2, double weight=16, double costPerOunce=.1);	
		double calculateCost();		// return the cost of shipping an overnight package

	private:
		double extraCostPerOunce;	// extra cost per ounce to ship package overnight
};

#endif
