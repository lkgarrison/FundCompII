/* Luke Garrison, part2.cpp
 * Parse plain text or HTML files and count the number of unique words
 * Two files must be specified.
 * The sets of unique words from each doucment are displayed along with their size,
 * and the Jaccard similarity is printed by dividing the size of the intersection of
 * the two sets of unique words by the size of their union.
 * 
 * For HTML files, unique links collected into a set and displayed.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

int main() {
	int numFiles = 2;
	vector<set<string> > uniqueWordsVec;	// vector to store sets for both documents
	vector<set<string> > uniqueLinksVec;
	vector<string> filenames;			// vector of valid filenames

	// read in file names from user
	// valid file names are stored for later access
	for(int i = 0; i < numFiles; i++) {
		string filename;
		ifstream file;
		// prompt user for a valid file name until one is given
		do {
			cout << "Enter a file name to process for file " << i+1 << ": ";
			cin >> filename;
			file.open(filename.c_str());
			if(! file) cout << "Error opening file: " << filename << endl;
		} while(! file);
		filenames.push_back(filename);	// add the valid filename to the vector for later access
	}

	// parse all documents
	for(int i = 0; i < numFiles; i++) {
		set<string> uniqueWords;
		set<string> uniqueLinks;
		uniqueWordsVec.push_back(uniqueWords);
		uniqueLinksVec.push_back(uniqueLinks);

		string word;
		string link;				// holds string in <a href= tags
		char c;
		bool ignore = false;		// flag to ignore characters (if currently reading inside HTML tag)
		int ahrefTagIterator = 0;
		string ahrefTag = "a href=";	// a href tag string to match
		bool is_ahrefTag = false;		// flag to know if current tag is an a href
		bool possible_ahrefTag = true;	// determine if current tag could potentially be an "a href" tag
		ifstream file(filenames[i].c_str());	// open file using valid file string

		// iterate through each character in the file.
		while(! file.eof()) {
			file.get(c);	// get the next character in the stream
			// if currently reading characters between "<" and ">", ignore, unless a href tag
			if(ignore) {
				// capture link, insert into uniqueLinks set
				if(is_ahrefTag) {
					if(c == '"') continue; // don't capture quotes in the link
					else if(c == '>') {		// signals the end of a link
						uniqueLinksVec[i].insert(link);
						link = "";			// reset link string
						is_ahrefTag = false;	// reset flag
						continue;
					}
					else link.push_back(c);	// add any other character to link string
				}

				// detect "<a href=" tag
				if(possible_ahrefTag && c == ahrefTag[ahrefTagIterator]) {	// check and see if current character matches "a href"
					ahrefTagIterator++;
					//cout << "matched an a href char" << endl;
					if(ahrefTagIterator == ahrefTag.length()) { // if it is an ahref tag
						is_ahrefTag = true;
						possible_ahrefTag = false;	// avoid checking for "<a href=" after it is detected
					}
				} else {
					possible_ahrefTag = false;
				}
			
			}
		
			if(c == '<') {
				if(word != "") {	// "<" should also trigger end of a word
					uniqueWordsVec[i].insert(word);
					word = "";	
				}
				ignore = true;			// begin html tag. ignore unless "a href" tag
				ahrefTagIterator = 0;	// reset iterator to check for <a href= tag
				is_ahrefTag = false;
				possible_ahrefTag = true;
			} else if (c == '>') {
				ignore = false;			// html tag is done
			} else if(isalpha(c) && !ignore) {
				word.push_back(tolower(c));		// add LOWERCASE char to current word if it is a valid letter
			} else if (isspace(c)) {
				if(word != "") {
					//wordComplete = true;	 // only mark word as complete if it is not a null str
					uniqueWordsVec[i].insert(word);
					word = "";				// reset word
				}
			}
		}
		// display results
		cout << "Number of unique words in document " << i+1 << ": " << uniqueWordsVec[i].size() << endl;
		cout << "Set of unique words in document " << i+1 << ":" << endl;
		for(set<string>::iterator it = uniqueWordsVec[i].begin(); it != uniqueWordsVec[i].end(); it++) {
			cout << "\t" << *it << endl;
		}

		cout << "Number of unique links in document " << i+1 << ": " << uniqueLinksVec[i].size() << endl;
		if(uniqueLinksVec[i].size() > 0) {			
			cout << "Set of unique links in document " << i+1 << ":" << endl;
			for(set<string>::iterator it = uniqueLinksVec[i].begin(); it != uniqueLinksVec[i].end(); it++) {
				cout << "\t" << *it << endl;
			}
		}
	}

	set<string> intersection;
	set_intersection(uniqueWordsVec[0].begin(), uniqueWordsVec[0].end(), uniqueWordsVec[1].begin(), uniqueWordsVec[1].end(), inserter(intersection, intersection.begin())); 


	set<string> unionOfSets = uniqueWordsVec[0];	// add all words from file 1 to union, then all words from file 2
	for(set<string>::iterator it = uniqueWordsVec[1].begin(); it != uniqueWordsVec[1].end(); it++) {
		unionOfSets.insert(*it);
	}
	
	cout << "Jaccard similarity of file 1 and file 2: " << (double) intersection.size() / unionOfSets.size() << endl; 

	return 0;
}
