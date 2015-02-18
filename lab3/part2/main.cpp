/* Luke Garrison, main.cpp
 * This program serves to demo the Package, TwoDayPackage, and OvernightPackage classes.
 * The program will neatly display the weight and costs associated with each package
 * as well as the total cost for the package
*/

#include <iostream>
#include <iomanip>
#include "Package.h"
#include "TwoDayPackage.h"
#include "OvernightPackage.h"
using namespace std;

int main() {

	// initialize weight and cost per ounce variables used to demo the classes, as well as 2-day flat fee
	double packageWeight = 4.66;
	double packageCostPerOunce = .12;
	double twoDayPackageFlatFee = 3.75;
	double twoDayPackageWeight = 5.2;
	double twoDayPackageCostPerOunce = .14;
	double overnightPackageWeight = 7.7;
	double overnightPackageCostPerOunce = .15;
	double overnightPackageExtraCostPerOunce = .59;

	// create different package objects and compute and display their shipping costs
	Package std(packageWeight, packageCostPerOunce);
	cout << fixed << setprecision(2) << "Cost of a " << packageWeight << " ounce standard package at $"
		 << packageCostPerOunce << " per ounce: $" << std.calculateCost() << endl;	
	
	TwoDayPackage twoDay(twoDayPackageFlatFee, twoDayPackageWeight, twoDayPackageCostPerOunce);
	cout << fixed << setprecision(2) << "Cost of a " << twoDayPackageWeight << " ounce two day package at $"
		 << twoDayPackageCostPerOunce << " per ounce with a flat fee of $" << twoDayPackageFlatFee
		 << ": $" << twoDay.calculateCost() << endl;

	OvernightPackage overnight(overnightPackageExtraCostPerOunce, overnightPackageWeight, overnightPackageCostPerOunce);
	cout << fixed << setprecision(2) << "Cost of a " << overnightPackageWeight << " ounce overnight package at a standard $" 
		 << overnightPackageCostPerOunce << " per ounce plus an extra cost of $" << overnightPackageExtraCostPerOunce 
		 << " per ounce: $" << overnight.calculateCost() << endl;

	return 0;
}
