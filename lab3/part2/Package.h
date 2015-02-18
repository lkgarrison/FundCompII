#ifndef PACKAGE_H
#define PACKAGE_H

/* Luke Garrison, Package.h
 * Interface for Package class
*/

#include <string>
using namespace std;

class Package {
	public:
		Package(double weight=16, double costPerOunce=0.1);	// default weight=16 oz, cost= 10 cents
		double calculateCost();		// calculates cost to ship package
		void setWeight(double);		// set the weight of the package
		void setCostPerOunce(double);	// set the cost per ounce to ship the package
		double getCostPerOunce();	// getter method to get the cost per ounce (used by OvernightPackage)
		string getName();			// returns recipient's name
		string getAddress();		// returns string containing recipient address information
		void setName(string);		// set recipient name
		void setAddress(string);	// set recipient address

	private:
		string nameRecipient;		// name of recipient of package
		string addressRecipient;	// shipping address of recipient
		int zipCodeRecipient;		// zip code of recipient
		string nameSender;			
		string addressSender;		
		int zipCodeSender;

		double weight;				// weight of the package
		double costPerOunce;		// cost per ounce to ship package	
};

#endif
