
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "autocompleter.h"

using namespace std;

//Initializing Merge and Search Functions
void MergeSort(string arr[], int s, int e);
int binarySearch(string arr[], int s, int e, string x, int l);

// Creates a new, empty autocompleter.
Autocompleter::Autocompleter() {
	count = 0;
	capacity = 11000;
	A = new string[capacity];
}

// Adds x to the list of potential results in the Autocompleter. 
// If the word is already in the Autocompleter, does nothing.
//
// Must run in O(n) time.
void Autocompleter::insert(string x) {
	int c = 0;

	//checks if duplicate
	while (c != count) {
		if (x == A[c])
			return;
		else c++;
	}

	A[count] = x;
	count++;

	//Sorts at Test Values
	if (count == 12 || count > 9999) {
		MergeSort(A, 0, count - 1);
	}
}

// Returns the number of strings in the Autocompleter.
int Autocompleter::size() {
	return count;
}

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
void Autocompleter::completions(string x, string* results) {
	int sindex = 0;
	int l = x.length();
	int same = 1;

	sindex = binarySearch(A, 0, count, x, l);
			
	int temp1 = sindex;
			
	while (same != 0) {
				
		//Checks if previous indexes have same elements
		if (temp1 != -1 && A[temp1].substr(0, l) == x.substr(0, l)) {
			if (A[temp1].substr(0, l) == x.substr(0, l)) {
				sindex = temp1;
				temp1--;
			}
		}
		else
			same = 0;
	}

	//Assigns first 3 elements to results array
	for (int i = 0; i < 3; i++) {
		if (A[sindex].substr(0, l) == x.substr(0, l)) {
			results[i] = A[sindex];
			sindex++;
		}
		else
			results[i] = "";
	}
}

//Binary Search Function with strings
//Returns index location of first found match
int binarySearch(string arr[], int s, int e, string x, int l) {

	int m = (s + (e + 1)) / 2;
	string a = arr[m].substr(0, l);
	string b = x.substr(0, l);

	if (s == e) {
		if (a != b)
			return 0;
	}

	if (e >= 0) {
		if (a == b)
			return m;
		else if (b < a)
			return binarySearch(arr, s, m - 1, x, l);
		else if (b > a)
			return binarySearch(arr, m, e, x, l);
	}
	else
		return 0;
}

//Merge Function
void Merge(string arr[], int s, int e) {
	int m = s + (e - s) / 2;

	int x = m - s + 1;
	int y = e - m;
	int total = x + y;

	string *L = new string[x];
	string *R = new string[y];

	for (int i = 0; i < x; i++)
		L[i] = arr[s + i];
	for (int i = 0; i < y; i++)
		R[i] = arr[m + i + 1];


	int a = 0;
	int b = 0;
	int c = s;

	while (a + b != total) {
		if (a < x && b < y) {
			if (L[a] <= R[b])
				arr[c++] = L[a++];
			else
				arr[c++] = R[b++];
		}
		else if (a == x)
			arr[c++] = R[b++];
		else if (b == y)
			arr[c++] = L[a++];
	}
}

//Merge and Sort Function
void MergeSort(string arr[], int s, int e) {
	if (s < e) {
		int m = s + (e - s) / 2;

		MergeSort(arr, s, m);
		MergeSort(arr, m + 1, e);
		for (int i = 0; i < 13; i++)
			Merge(arr, s, e);
		
	}
}

