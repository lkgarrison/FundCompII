/* Luke Garrison, part1.cpp
 * Computes the number of possible 7 letter word combinations in which
 * There are not 3 or more consecutive letters
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {

	int alphabetSize = 26;	// decrease the amount of hard-coding
	long long count = 0;	// set a counter to count matches
	for(int a = 0; a < alphabetSize; a++) {
		for(int b = 0; b < alphabetSize; b++) {
			for(int c = 0; c < alphabetSize; c++) {
				for(int d = 0; d < alphabetSize; d++) {
					for(int e = 0; e < alphabetSize; e++) {
						for(int f = 0; f < alphabetSize; f++) {
							for(int g = 0; g < alphabetSize; g++) {
								if(a==b && a==c && b==c) continue;
								else if(b==c && b==d && c==d) continue;
								else if(c==d && c==e && d==e) continue;
								else if(d==e && d==f && e==f) continue;
								else if(e==f && e==g && f==g) continue;
								
								count++;
							}
						}
					}
				}
			}
		}
	}
	cout << "Count: " << count << endl;


	return 0;
}		
