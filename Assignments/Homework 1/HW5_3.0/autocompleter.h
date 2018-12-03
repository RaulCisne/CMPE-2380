
#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <string>

using namespace std;

class Autocompleter
{
public:
	// Creates a new, empty autocompleter.
	Autocompleter();

	// Adds x to the list of potential results in the Autocompleter. 
	// If the word is already in the Autocompleter, does nothing.
	//
	// Must run in O(n) time.
	void insert(string x);

	// Returns the number of strings in the Autocompleter.
	int size();

	// Takes a string (named x) and 
			// a string array of length 3 (named results).
			//  
	// Sets the 3 elements of results equal to 
			// the smallest 3 strings in the Autocompleter that start with x.
	//
	// If there are less than 3 such strings, 
			// then the remaining entries of the results array are set to "".
	//
	// Must run in O(log(n)) time.
	void completions(string x, string* results);

private:
	// The data structure should consist of 
	// a dynamic array of sorted strings.
	string* A;
	int count;
	int capacity;
};

#endif


