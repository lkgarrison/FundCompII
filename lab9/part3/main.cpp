/* Luke Garrison, main.cpp
 * This program serves as a driver for the NDVector class.
 * This driver will demo the new methods and features in the 
 * NDVector class.
*/

#include <iostream>
#include "NDVector.h"
using namespace std;

// display an NDVector of type int
void display(NDVector<int> vec) {
	for(int i = 0; i < vec.size(); i++) {
		cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
	}
	cout << endl;
}

int main() {
	NDVector<int> vec(5);	
	NDVector<int> vec2(5);
	NDVector<int> vec3(5);

	// add a few elements to NDVectors
	vec.push_back(5);
	vec.push_back(9);
	vec.push_back(1);	

	vec2.push_back(6);
	vec2.push_back(7);

	vec3.push_front(7);	// make vec3 the same as vec2 to test equality
	vec3.push_front(6);
	
	// display initial values in NDVectors
	cout << endl << "Vectors:" << endl;
	cout << "--------" << endl;
	cout << "vec: ";
	display(vec);
	cout << "vec2: ";
	display(vec2);
	cout << "vec3: ";
	display(vec3);

	// test operator+=
	cout << endl << "Testing overloaded operators and extra methods:" << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "Calling vec+= vec2, vec = ";
	vec+= vec2;
	display(vec);

	// test operator==
	if(vec == vec2) cout << "vec and vec2 are equivalent" << endl;
	else cout << "vec and vec2 are not equivalent" << endl;

	if(vec2 == vec3) cout << "vec2 and vec3 are equivalent" << endl;
	else cout << "vec2 and vec3 are not equivalent" << endl;

	// test sort method
	cout << "vec before being sorted: ";
	display(vec);
	vec.sort();
	cout << "vec after being sorted: ";
	display(vec);

	// test erase method
	cout << "vec after removing 2nd element: ";
	vec.erase(1);
	display(vec);


	// exception handling
	cout << endl << "Exception Handling:" << endl;
	cout << "------------------" << endl;

	long failSize = 100000000000;
	cout << "Attempting to allocate an NDVector of size " << failSize << ":" << endl;
	NDVector<int> vec4(failSize);

	cout << endl << "Attempt to access a negative element of vec:" << endl;
	try {
	cout << vec[-5] << endl;
	}
	catch (const char* e) {
		cerr << "Error: " << e << endl;
	}
	
	cout << endl << "Attempt to access an element that exceeds the size of vec:" << endl;
	try {
	cout << vec[99] << endl;
	}
	catch (const char* e) {
		cerr << "Error: " << e << endl;
	}

	cout << endl << "Clear vec and then call member function 'pop_back' on the empty NDVector:" << endl;
	vec.clear();
	try {
		vec.pop_back();
	}
	catch (const char* e) {
		cerr << "Error: " << e << endl;
	}	


	return 0;
}
