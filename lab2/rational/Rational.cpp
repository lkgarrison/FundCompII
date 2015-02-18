/* Luke Garrison, Rational.cpp
 * Implementation for Rational class
 * Order of Code: Constructors, global overloaded output method, overloaded math operators,
 * and then private helper functions.
 * 
 */

#include <iostream>
#include "Rational.h"
using namespace std;

/* Constructor
*/
Rational::Rational(int myNum, int myDen) {
	num = myNum;
	if(myDen == 0) {		// error checking on specified denominator
		cout << "Cannot use 0 as the denominator...Using 1 instead." << endl;
		den = 1;			// set denominator to 1 if 0 was specified
	} else {
		den = myDen;		// if specified den was valid, use it
	}
	(*this).reduce();		// reduce rational, in case a non-simplified rational was specified
}

/* Copy Constructor 
 * The copy constructor could safely assume that all ratoinal objects that have been created have
 * a non-zero denominator. The constructor ensures the denominator != 0, and mathematical
 * functionals for the rational class will also ensure the denominator is != 0
 * However, in case this class were ever modified in the future, it is best to check for a 0
 * denominator here, in case another math method was added that did not check on the denominator
*/
Rational::Rational(const Rational & rationalToCopy) {
	num = rationalToCopy.num;
	if(rationalToCopy.den == 0) {	// if den of rationalToCopy is somehow 0
		cout << "0 is not a valid denominator...Using 1 instead." << endl;
		den = 1;
	} else {						// valid denominator 
		den = rationalToCopy.den;	// impossible for a rational object to have a denominator of 0
	}
}

/* overload the << operator to output the rational object as a fraction. 
 * enables cout << rationalObject instead of rationalObject.display()
 * Special cases: if den == 0, just display numerator
 */
ostream& operator<<(ostream & output, const Rational & myRational) {
	if(myRational.den == 1) {
		output << myRational.num;
	} else {
		output << myRational.num << "/" << myRational.den;
	}	
	return output;
}

/****** Addition	
 * Overload the + operator to enable addition of rational numbers
 * any variable with a 1 refers to this object, any variable with a 2 refers to rationalToAdd
*/
Rational Rational::operator+(const Rational & rationalToAdd) {
	Rational sum;		// temporary rational used to add 2 rationals together. it will be returned by the method

	int commonDen = lcm(den, rationalToAdd.den);	// find lcm of two rational's denominators. common denominator
	int multiplier1 = commonDen / den;		// find what multiple the new denominator is from current
	int multiplier2 = commonDen / rationalToAdd.den;
	
	sum.num = (num * multiplier1) + (rationalToAdd.num * multiplier2);	// adjust numerators to be proportional to common den
	sum.den = commonDen;					// set to common denominator
	sum.reduce();						// reduce fraction to lowest terms
	return sum;
}

/****** Subtraction
 * Overload the - operator to subtract two rationals
 * in use, the leftmost rational will be subtracted from the rightmost rational
 * multiplier 1 will refer to this object, while multiplier 2 refers to
 * rationalToSubtract. Multipliers are used to keep the fractions in proportion
*/
Rational Rational::operator-(const Rational & rationalToSubtract) {
	Rational difference;		// temp rational. This is the rational that will be returned
	int commonDen = lcm(den, rationalToSubtract.den); 	// find common denominator of the 2 rationals
	int multiplier1 = commonDen / den;					// find what multiple commonDen is of den
	int multiplier2 = commonDen / rationalToSubtract.den; 
	difference.num = (num * multiplier1) - (rationalToSubtract.num * multiplier2); 	// subtract numerators of common den's
	difference.den = commonDen;														// set to commonDen
	difference.reduce();				// simplify fraction
	return difference;				// return the resulting rational
}

/****** Multiplication
 * Overload the * operator to multiply two rationals
 * The numerators are both multiplied together, and the same with the denominators.
 * Then, the resulting product is simplified and returned
*/
Rational Rational::operator*(const Rational & rationalToMultiply) {
	Rational product;		// create new rational obj, will be returned as the product
	product.num = num * rationalToMultiply.num;	// multiply numerators
	product.den = den * rationalToMultiply.den;	// multiply denominators
	product.reduce();								// reduce product
	return product;
}

/****** Divison
 * Overload the / operator to divide two rationals. 
 * This method utilizes the overloaded multiplication method by multilying the dividend by
 * The inverse of the divisor. "inv" will hold the inverse of the divisor.
 * edge case: if the num of the divisor is 0 / anything, the 0 will flip to the bottom 
 * during multiplication, creating a quotient with 0 in the denominator. Combat this by
 * returning a rational that is equivalent to 0 (even though this is not mathematically correct)
*/
Rational Rational::operator/(const Rational & rationalDivisor) {
	Rational quotient;		// this rational will be hold the quotient of the division	
	Rational inv;			// this rational will be the inverse of the divisor to simplify 
	if(rationalDivisor.num == 0) {	// will cause a divide by 0
		cout << "Divide by 0 error. Divison operation not possible." << endl;	// print error message
		quotient.num = 0;		// create a rational object equivalent to 0
		quotient.den = 1;
	} else {						// valid division
		inv.num = rationalDivisor.den;		// invert the divisor
		inv.den = rationalDivisor.num;
		quotient = *this * inv;			// utilize overloaded = and + operators. *this = current rational
	}
	quotient.reduce();
	return quotient;
}

/****** Greater Than
 * Check to see if the numerator / denominator of the left rational is larger than num / den of the 
 * rational on the right (rationalToCompare). Returns true if the left rational is larger than the right
*/
bool Rational::operator>(const Rational & rationalToCompare) {
	if(((double) num / den) > ((double) rationalToCompare.num / rationalToCompare.den))	// if left is >
		return true;
	else
		return false;
}	

/****** Less Than
 * Check to see if the numerator / den of the left rational is less than the num / den of the rational 
 * on the right (rationalToCompare). Returns true if the left rational is smaller than the right
*/
bool Rational::operator<(const Rational & rationalToCompare) {
	if(((double) num / den) < ((double) rationalToCompare.num / rationalToCompare.den))
		return true;
	else
		return false;
}

/* simplifies rational to reduced form
 * the method finds the GCD of the rational's numerator and denominator, and then divides both the
 * numerator and denominator by this GCD. This puts the rational in reduced form and ensures that 
 * the denominator is never negative (makes numerator negative instead)
 */
void Rational::reduce() {
	int gcdRational = gcd(num, den);
	num /= gcdRational;
	den /= gcdRational;
	if(den < 0) {			// if den is negative
		den*= -1;			// negate numerator instead of denominator.
		num*= -1;
	}
}

/* private mathod to find the LCM of two numbers. Very useful for performing operations on rationals
 * This implementation of the LCM uses the GCD to find the LCM
*/
int Rational::lcm(int n1, int n2) {
	return (n1 * n2) / gcd(n1, n2);		// returns the LCM of n1 and n2
}

/* private mathod to find the GCD of two numbers. Very useful for performing operations on rationals
 * This method utillizes the Euclidian algorithm to find the GCD
 * rational 0 / 4 would work because 0 % 4 = 0, and thus r = 0, which exits the method
*/
int Rational::gcd(int x, int y) {
	int r;					// remainder
	while(1) {
		r = x % y;
		if(r == 0) return y;
		else {
			x = y;
			y = r;
		}
	}
}
