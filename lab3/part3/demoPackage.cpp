/* Luke Garrison, demoPackage.cpp
 * This is a driver class for part 3 of lab 3.
 * It will demo polymorphism by displaying information from multiple derived classes
 * of package.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include "Package.h"
#include "OvernightPackage.h"
#include "TwoDayPackage.h"
using namespace std;

int main() {
	//vector<Package> packages(6);	// create a vector of packages
	/*

	OvernightPackage test;
	packages.push_back(test);
	cout << packages[0].print() << endl;
*/
	double total = 0;	// total cost of sending all packages

	// instantiate 3 TwoDayPackages and 3 OvernightPackages
	OvernightPackage on1(.55, 7.2, .21);  // extra overnight fee per ounce, ounces, standard costPerOunce
	OvernightPackage on2(.77, 22.2, .23);
	OvernightPackage on3(.87, 48.1, .19);
	TwoDayPackage td1(4.99, 25.5, .25);		// flat fee, ounces, costPerOUnce
	TwoDayPackage td2(7.49, 40.3, .18);
	TwoDayPackage td3(6.55, 37.1, .33);

	// set name and address for recipient of each package
	on1.setName("Batman");
	on1.setAddress("The Bat Cave");
	on2.setName("Professor Emrich");
	on2.setAddress("University of Notre Dame");
	on3.setName("Luke Garrison");
	on3.setAddress("Duncan Hall");
	td1.setName("Drue Tranquil");
	td1.setAddress("Notre Dame Stadium");
	td2.setName("Men's Basketball Team");
	td2.setAddress("Purcell Pavillion");
	td3.setName("Fr. Hessburgh");
	td3.setAddress("Hessburgh Library");

	// add packages references to packages to packages array
	Package * packages[6];		// array of pointers to Packages
	packages[0] = &on1;			// each index is set to be a reference to a Package obj
	packages[1] = &on2;
	packages[2] = &on3;
	packages[3] = &td1;
	packages[4] = &td2;
	packages[5] = &td3;

	// loop thorugh packages array and display address information, as well as the total cost
	for(int i = 0; i < 6; i++) {
		cout << packages[i]->getName() << endl;		// display name
		cout << packages[i]->getAddress() << endl;	// display address
		cout << fixed << setprecision(2) << "$" << packages[i]->calculateCost() << endl << endl;
		total+= packages[i]->calculateCost();	// calculate cost of given package and add it to total var
	}

	cout << "Total cost to send all packages: $" << fixed << setprecision(2) << total << endl;	
	return 0;
}

