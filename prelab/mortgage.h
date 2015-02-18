/* 	Luke Garrison, mortgage.h
 *  Interface (.h) file for Mortgage class
 *
 *  This header file will list all of the public methods available,
 *  as well as the private variables. There is one private method,
 *  which is private because it is used internally in a member function,
 *  and has not use to a client. It is the printHeader method, used to print
 *  the first header line of the amortization table. 
 *
 *  Other methods include: credit, getPrincipal, and amortize 
 *
 *  */

#include <iostream>

class Mortgage {

	public:
		Mortgage(double=150000, double=4.0, double=600); // constructor w/ fallback values		
		void credit(double);   	// deducts value from the principal remaining
		double getPrincipal(); 	// returns the current principal remaining
		void amortize();		// calculates and displays a correct and clean 
									// amortization table.
		
	private:
		void printHeader(); // this private method is called to print the header row for the table
		double principal;	// remaining principal owed
		double rate;		// interest rate; taken in as a %, internally handled as a decimal`
		double payment; 	// desired monthly payment
		double interest;	// interest on principal per month
		int month;			// keeps track of month number
};
