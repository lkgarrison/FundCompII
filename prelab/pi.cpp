/* pi.cpp
 * 
 * This program will ask the user how many terms should be used to 
 * estimate pi from an infinite series. 
 * The estimate of pi will be displayed for the given number of terms
 * for every number of terms up to the user specified number of terms.
 *
 * Luke Garrison 
 */

#include <iostream>
#include <cmath>        // pow()
#include <iomanip>      // setprecision()

using namespace std;

int main() {

  int n;          // n represents the number of terms to use in the estimate of pi
  double pi = 0;  // initial value for estimate of pi

  // this "infinite loop" will allow error message to display until valid input received
  while(1) { 
	cout << "Please enter the number of terms to use in the series to estimate pi: ";
	cin >> n;
	if(n < 2) cout << "Error! Provided value must be >= 2" << endl; // brackets are not necessary when there is only one command for an if statement
	else break; // exits the infinite loop if user enters valid value
  }

  for(int i = 1; i <= n; i++) {
	pi += (4. / (2 * i - 1)) * pow(-1, i + 1);  // formula for estimation. The power function is used to get the sign of the next term correct. First term should be positive 4.
	cout << fixed << setprecision(3) << "Estimate after " << i << " term(s): " << pi << endl; // first two commands to the stream allow 2 decimals to be displayed in the pi estimation
  }

  return 0;
}

