//Raul Cisneros
//Homework 6: AutoCompleter BST
//CMPE 2380.03, Fall 2018, Eric Martinez

#include <string>
#include <iostream>
#include "autocompleter.h"

using namespace std;

Autocompleter::Autocompleter(){
	root = nullptr;
}

void Autocompleter::insert(string x) {
	
	if (root == nullptr)
		root = new Node(x);

	else if(root != nullptr)
		insert_recurse(x, root);

	//cout << x << endl;
	/*if (x == "america")
		system("pause");*/
}

int Autocompleter::size(){
		return size_recurse(root);
}


void Autocompleter::completions(string x, string* suggestions) {
	for (int i = 0; i < 3; i++)
		suggestions[i] = "";

	completions_recurse(x, suggestions, root);

}


// Helper method for insert()
void Autocompleter::insert_recurse(string x, Node* &root) {
	
	if (root != nullptr) {
		
		if (x == root->s)
			return;
			
		if (root->left != nullptr && x < root->s)
				insert_recurse(x, root->left);

		if (root->right != nullptr && x > root->s)
				insert_recurse(x, root->right);

		if (root->right == nullptr && x > root->s)
				root->right = new Node(x);

		if (root->left == nullptr && x < root->s)
				root->left = new Node(x);
	}
}

// Helper method for size()
int Autocompleter::size_recurse(Node* root){
	
	if (root == nullptr)
		return 0;

	if (root->left != nullptr && root->right != nullptr)
		return 1 + size_recurse(root->left) + size_recurse(root->right);

	if (root->right != nullptr && root->left == nullptr)
		return 1 + size_recurse(root->right);

	if (root->left != nullptr && root->right == nullptr)
		return 1 + size_recurse(root->left);

	if (root->left == nullptr && root->right == nullptr)
		return 1;
}

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
// add root->s to first empty location in results.
// -If right subtree can contain strings that start with x,
//  recurse on right subtree.
void Autocompleter::completions_recurse(string x, string* results, Node* root) {
	
	int l = x.length();

	if (root != nullptr) {
		if (x.substr(0, l) == root->s.substr(0, l)) {
			if (results[0] == "")
				results[0] = root->s;
			else if (results[1] == "")
				results[1] = root->s;
			else if (results[2] == "")
				results[2] = root->s;
				
			for (int i = 0; i < 3; i++) {
				string temp = results[i];
				
				if (root->s < results[i]) {
					if (i == 0) {
						results[i] = root->s;
						results[i + 2] = results[i+1];
						results[i + 1] = temp;
						break;
					}
					if (i == 1) {
						results[i] = root->s;
						results[i + 1] = temp;
						break;
					}
					if (i == 2) {
						results[i] = root->s;
						break;
					}
				}
			}
		}
		if (root->right != nullptr && x >= root->s.substr(0,l))
			completions_recurse(x, results, root->right);
		
		if (root->left != nullptr && x <= root->s.substr(0,l))
			completions_recurse(x, results, root->left);
		
	}
}
		

