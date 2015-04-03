/* Luke Garrison, main.cpp
 * This is a driver program for the NDVector class
 */

#include <iostream>
#include "NDVector.h"
using namespace std;

int main() {
	NDVector<int> array(20);


	for(int i = 0; i < 12; i++) {
		array.push_back(i);		
		
		cout << array[i] << " ";
		if((i + 1) % 15 == 0) cout << endl;
	}
	cout << endl;

	

	NDVector<int> second;
	second.push_back(9);
	second.push_back(8);
	second = array;


//	cout << array.getFirst() << endl;
//	cout << array.getLast() << endl;



cout << "display array:";
		for(int j = 0; j < second.size(); j++) {
			cout << second[j] << " ";
		}
		cout << endl;



//	array.display();
}
