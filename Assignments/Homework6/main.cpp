//Andrew Silva
//December 4, 2018
//Homework 4: AutoCompleter BST
//CMPE 2380.03, Fall 2018, Eric Martinez

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include "autocompleter.h"

using namespace std;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


string random_string(int length)
{
	string s;
	for (int i = 0; i < length; ++i)
		s += 'a' + (rand() % 26);
	return s;
}

void interactive_mode()
{
	Autocompleter dictionary;

	// Fill autocompleter with words
	ifstream f;
	f.open("words2.txt");
	assert(f.is_open()); // If this fails, you're missing above file
	string line;
	while (getline(f, line))
		dictionary.insert(line);
	f.close();

	string results[3];
	while (cin)
	{
		string line;
		getline(cin, line);
		dictionary.completions(line, results);
		for (int i = 0; i < 3; ++i)
			if (results[i] != "")
				cout << "    " << results[i] << endl;
	}
	exit(0);
}

int main()
{
	srand(2018 + 'f'); // Initialize random number generation, e.g. rand()
	string results[3]; // Used to hold output suggestions in some tests


	// Uncomment line below to use your Autocompleter interactively.
	// Enter a string and press Enter - the autocompletions
	// results from 100000 common words are printed.
	//
	//interactive_mode();

	
	// Test a small Autocompleter with animal names
	Autocompleter animals;
	test(animals.size() == 0);
	animals.insert("aardvark");
	animals.insert("camel");
	animals.insert("giraffe");
	animals.insert("albatross");
	animals.insert("cat");
	animals.insert("goat");
	animals.insert("alpaca");
	animals.insert("crocodile");
	animals.insert("goose");
	animals.insert("armadillo");
	animals.insert("crow");
	animals.insert("gorilla");
	
	test(animals.size() == 12);
	
	animals.insert("gorilla"); // Already in the Autocompleter
	test(animals.size() == 12);

	
	// Create an autocompleter of 100000 common English words
	Autocompleter dictionary;

	// Fill autocompleter with words
	string* words = new string[100000];
	ifstream f;
	f.open("words2.txt");
	assert(f.is_open()); // If this fails, you're missing words.txt
	string line;
	int i = 0;
	while (getline(f, line))
	{
		words[i] = line;
		++i;
	}
	f.close();
	assert(i == 100000); // If this fails, words.txt is wrong
	
	for (int i = 0; i < 100000; ++i)
		dictionary.insert(words[i]);
	
	test(dictionary.size() == 100000);
	

	// Test completions() on animals Autocompleter already made.
	animals.completions("a", results);
	test(results[0] == "aardvark");
	test(results[1] == "albatross");
	test(results[2] == "alpaca");

	animals.completions("al", results);
	test(results[0] == "albatross");
	test(results[1] == "alpaca");
	test(results[2] == "");

	animals.completions("cro", results);
	test(results[0] == "crocodile");
	test(results[1] == "crow");
	test(results[2] == "");

	animals.completions("gir", results);
	test(results[0] == "giraffe");
	test(results[1] == "");
	test(results[2] == "");

	animals.completions("go", results);
	test(results[0] == "goat");
	test(results[1] == "goose");
	test(results[2] == "gorilla");

	animals.completions("", results);
	cout << results[1] << endl;
	test(results[0] == "aardvark");
	test(results[1] == "albatross");
	test(results[2] == "alpaca");

	animals.completions("an", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");

	animals.completions("q", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");

	animals.completions("goat-billed carp", results);
	test(results[0] == "");
	test(results[1] == "");
	test(results[2] == "");


	// Test completions() on dictionary Autocompleter already made.
	dictionary.completions("bir", results);
	test(results[0] == "bir");
	test(results[1] == "biracial");
	test(results[2] == "birch");

	dictionary.completions("hap", results);
	test(results[0] == "hap");
	test(results[1] == "haphazard");
	test(results[2] == "haphazardly");

	dictionary.completions("program", results);
	test(results[0] == "program");
	test(results[1] == "programa");
	test(results[2] == "programas");

	dictionary.completions("foo", results);
	test(results[0] == "foo");
	test(results[1] == "foobar");
	test(results[2] == "food");

	dictionary.completions("suggest", results);
	test(results[0] == "suggest");
	test(results[1] == "suggested");
	test(results[2] == "suggesting");


	// Test Autocompleter for completing 100000 words
	for (int i = 0; i < 100000; ++i) {
		dictionary.completions(random_string(5), results);
		cout << i << endl;
	}


	cout << "Assignment complete." << endl;
	system("pause");
}
