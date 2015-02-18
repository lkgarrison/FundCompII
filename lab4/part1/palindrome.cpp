/* Luke Garrison, palindrome.cpp
 * This program will check to see if a collection of integers is a palindrome.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

/* Takes a vector by reference. Displays the vector with a space between each element 
*/
void displayVector(vector<int> & intVec) {
	vector<int>::const_iterator i;							// forward iterator 
	for(i = intVec.begin(); i != intVec.end(); i++) {		// iterate from beginning to end of vector
		cout << *i << " ";
	}
}

/* Takes in a vector and checks to see if it is a palindrome by checking to see if 
 * the vector is equal to the itself reversed
*/
void checkPalindrome(vector<int> & intVec) {
	vector<int> reversedVec(intVec.rbegin(), intVec.rend());	// vector that is the reverse of the original vector
	displayVector(intVec);						// display the vector. no newline in function
	if(intVec == reversedVec) {					// it is a palindrome
		cout << "is a palindrome!" << endl;
	} else {
		cout << "is not a palindrome." << endl;
	}
}


int main() {
	vector<int> intVec;
	vector<int> intVec2;

	intVec.push_back(1);
	intVec.push_back(2);
	intVec.push_back(1);
	intVec.push_back(4);

	checkPalindrome(intVec);
	intVec2 = intVec;
	intVec2.pop_back();
	checkPalindrome(intVec2);
	
	return 0;
}


