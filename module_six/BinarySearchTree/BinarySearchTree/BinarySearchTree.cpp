//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Andrew Trick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
// Date        : 10.09.2018
//============================================================================

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>
#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);

// FIXME (1): Internal structure for tree node                                           --(done)
struct Node {
	Bid bid;
	Node *left, *right;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
* Define a class containing data members and methods to
* implement a binary search tree
*/
class BinarySearchTree {

private:
	Node* root;
	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	Node* removeNode(Node* node, string bidId);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Bid bid);
	void Remove(string bidId);
	Bid Search(string bidId);
};

/**
* Default constructor
*/
BinarySearchTree::BinarySearchTree() {
	// initialize housekeeping variables
	cout << "INITIALIZING" << endl;  
	Node* root = NULL;
}

/**
* Destructor
*/
BinarySearchTree::~BinarySearchTree() {
	// recurse from root deleting every node
}

/**
* Traverse the tree in order
*/
void BinarySearchTree::inOrder(Node* node) {   // iterate and print all nodes
	Node* current = node;
	Node* prev = NULL;

	// return if empty node
	if (current == NULL) {
		return;
	}
	//print out node
	displayBid(current->bid);
	//move down left then right branches
	if (current->left) { inOrder(current->left); }
	if (current->right) { inOrder(current->right); }

}	


void BinarySearchTree::InOrder() {    //set root as default search node
	inOrder(root);
}


/**
* Insert a bid
*/
void BinarySearchTree::Insert(Bid bid) {
	// FIXME (2a) Implement inserting a bid into the tree                                 --(done)
	Node *current = root;
	Node *prev = NULL;
	
	// Check for root
	if (root == NULL) {
		root = new Node;
		root->bid = bid;
		root->left = NULL;
		root->right = NULL;
		return;
	}

	//	iterate through tree until proper location found and insert
	while (current != NULL) {
		if (bid.bidId < current->bid.bidId)
		{
			prev = current;
			current = current->left;
		}
		else {
			prev = current;
			current = current->right;
		}
	}

	// Insert data 
	current = new Node;
	current->bid = bid;
	current->left = NULL;
	current->right = NULL;
	

	// update pointers
	if (current->bid.bidId < prev->bid.bidId) {
		prev->left = current;
	}
	else {
		prev->right = current;
	}
	return;
}

/**
* Remove a bid
*/
void BinarySearchTree::Remove(string bidId) {                         
	// FIXME (4a) Implement removing a bid from the tree                                    --(done)
	Node *current = root;
	Node *parent = NULL;
	
	while (current != NULL) {
		if (current->bid.bidId == bidId) {  // node found
			//leaf node w/ no children
			if (current->left == NULL && current->right == NULL) { 
				if (parent == NULL) {  //node is root
					root = NULL;
				}
				else if (parent->left == current) { //is a left node.
					parent->left = NULL;
				}
				else {  // is right node
					parent->right = NULL;
				}
			}

			// has only left child
			else if (current->left != NULL && current->right == NULL) { 
				if (parent == NULL) { //root node
					root = current->left;
				}
				else if (parent->left == current) { //is left node
					parent->left = current->left;
				}
				else { // right node
					parent->right = current->left;
				}
			}

			//has only right child
			else if (current->left == NULL && current->right != NULL) { 
				if (parent == NULL) { //root node
					root = current->right;
				}
				else if (parent->left == current) { //is left node
					parent->left = current->right;
				}
				else { // right node
					parent->right = current->right;
				}
			}

			// node w/ two children
			else {    
				// iterate to leftmost child of right subtree
				Node* successor = current->right;
				while (successor->left != NULL) {
					successor = successor->left;
				}
				// destroy replacement child
				Remove(successor->bid.bidId);
				// update node
				current->bid = successor->bid;
				current->left = successor->left;
				current->right = successor->right;
			}
			return;
		}
		else if (current->bid.bidId < bidId) {   // move down right branch
			parent = current;
			current = current->right;
		}
		else {   // move down left branch
			parent = current;
			current = current->left;
		}
	}
	return; // not found
}

/**
* Search for a bid
*/
Bid BinarySearchTree::Search(string bidId) {
	// FIXME (3) Implement searching the tree for a bid                                   --(done)
	Node *current = root; 
	// iterate until bidId is matched or null node is found
	while (current != NULL) {
		if (bidId == current->bid.bidId) {
			return current->bid;
		}
		else if (bidId < current->bid.bidId) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	// if Not found return empty bid
	Bid bid;
	return bid;
}

/**
* Add a bid to some node (recursive)
*
* @param node Current node in tree
* @param bid Bid to be added
*/
void BinarySearchTree::addNode(Node* node, Bid bid) {
	// FIXME (2b) Implement inserting a bid into the tree                                        --(done)
	Insert(bid);
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
* Display the bid information to the console (std::out)
*
* @param bid struct containing the bid info
*/
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}

/**
* Load a CSV file containing bids into a container
*
* @param csvPath the path to the CSV file to load
* @return a container holding all the bids read
*/
void loadBids(string csvPath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// read and display header row - optional
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bst->Insert(bid);
		}
	}
	catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
* Simple C function to convert a string to a double
* after stripping out unwanted char
*
* credit: http://stackoverflow.com/a/24875936
*
* @param ch The character to strip out
*/
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
* The one and only main() method
*/
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath, bidKey;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98109";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
		bidKey = "98109";
	}

	// Define a timer variable
	clock_t ticks;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			bst = new BinarySearchTree();

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bst);

			//cout << bst->Size() << " bids read" << endl;

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 2:
			bst->InOrder();
			break;

		case 3:
			ticks = clock();

			bid = bst->Search(bidKey);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			}
			else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 4:
			bst->Remove(bidKey);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
