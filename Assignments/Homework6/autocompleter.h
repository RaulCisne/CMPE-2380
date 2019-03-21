//Raul Cisneros
//Homework 6: AutoCompleter BST
//CMPE 2380.03, Fall 2018, Eric Martinez

#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <string>

using namespace std;

class Autocompleter
{
public:
	// Same as hwAC1
	Autocompleter();
	void insert(string x);
	int size();
	void completions(string x, string* suggestions);

	//private:
		// A helper class that implements
		// a basic binary search tree node.
	class Node
	{
	public:
		Node(string s)
		{
			this->s = s;
			left = right = nullptr;
		}

		string s;
		Node* left;
		Node* right;
	};

	// Helper method for insert()
	void insert_recurse(string x, Node* &root);

	// Helper method for size()
	int size_recurse(Node* root);

	// Helper method for completions().
	//
	// Suggested base cases:
	// If root is nullptr, return.
	// If the last entry of the suggestions array is not "", return.
	// (since completions() has already found 3 suggestions).
	//
	// Suggested recursive case:
	// -If left subtree can contain strings that start with x,
	//  recurse on left subtree.
	// -If root's string starts with x,
	//  add root->s to first empty location in results.
	// -If right subtree can contain strings that start with x,
	//  recurse on right subtree.
	void completions_recurse(string x, string* results, Node* root);

	// The data structure should be a binary search tree
	Node* root;
};

#endif
