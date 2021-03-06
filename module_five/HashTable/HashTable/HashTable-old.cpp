//============================================================================
// Name        : HashTable.cpp
// Author      : Andrew Trick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "stdafx.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

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

class Node {   
// Node class tooi fill and link list buckets of hashtable (storage elements)
public:
	Bid bid;
	int bucket;
	Node* next;

	int getBucket() {
		return bucket;
	}
	Bid getBid() {
		return bid;
	}
};

// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);
class HashTable;
HashTable *bidTable;

//============================================================================
// Hash Table class definition
//============================================================================

/**
* Define a class containing data members and methods to
* implement a hash table with chaining.
*/
class HashTable {

private:
	// Define structures to hold bids        <--------------------------------  (1)   DONE
	unsigned int hash(int key);
	Node *node;	

public:
	HashTable();
	virtual ~HashTable();
	void Insert(Bid bid);
	void PrintAll();
	void Remove(string bidId);
	Bid Search(string bidId);
	Node **table;
};

/**
* Default constructor
*/
HashTable::HashTable() {
	// Initialize the structures used to hold bids       <--------------------------------  (2)  DONE
	table = new Node * [DEFAULT_SIZE];
	for (int i = 0; i < DEFAULT_SIZE; i++) {
		table[i] = new Node();
	}
}

/**
* Destructor
*/

HashTable::~HashTable() {
	// Implement logic to free storage when class is destroyed    <--------------------------------  (3)   DONE
	// Remove all buckets and linked listed in order
	for (int i = 0; i < DEFAULT_SIZE; ++i) {
		Node *element = table[i];
		while (!element->bid.bidId.empty()) {
			Node *prev = element;
			element = element->next;
			delete prev;
		}
		table[i] = NULL;
	}
	// delete the table
	delete[] table;
}

/**
* Calculate the hash value of a given key.
* Note that key is specifically defined as
* unsigned int to prevent undefined results
* of a negative list index.
*
* @param key The key to hash
* @return The calculated hash
*/
unsigned int HashTable::hash(int key) {
	//  Implement logic to calculate a hash value    <--------------------------------  (4) MAKE MORE COMPLEX?
	return (key % DEFAULT_SIZE);
}

/** 
* Insert a bid
*
* @param bid The bid to insert
*/
void HashTable::Insert(Bid bid) {
	// Implement logic to insert a bid     <--------------------------------  (5)  DONE
	int bucket = hash(stoi(bid.bidId));   // stoi - string to int

	// if collision append to end of linked list
	if (!table[bucket]->bid.bidId.empty()) {
		Node *tmpCheck = table[bucket];
		Node *newTable = new Node();

		// iter to last in linked list
		while (!tmpCheck->next->bid.bidId.empty()) {
			tmpCheck = tmpCheck->next;
		}

		// Append new bid
		tmpCheck->next = newTable;
		newTable->bid = bid;
		newTable->next = new Node();
	}

	else {
		// Add bid to bucket (first entry)
		table[bucket] = new Node();
		table[bucket]->bid = bid;
		table[bucket]->next = new Node();
	}
}


/**
* Print all bids
*/
void HashTable::PrintAll() {
	// Implement logic to print all bids    <--------------------------------  (6) FIX 
	cout << "TEST" << endl;  //--------------------------------------------------------------------------------------------------------------------------------------------TEST
	for (int i = 0; i < DEFAULT_SIZE; i++) {
		cout << table[0]->bid.bidId << endl; //------------------------------------------------------------------------------------------------------------------------------TEST
	}
	cout << "SECOND" << endl; //-----------------------------------------------------------------------------------------------------------------------------TEST
	for (int i = 0; i < DEFAULT_SIZE; i++) {
		Node *temp = table[i];
		while (!temp->bid.bidId.empty()) {
			displayBid(temp->bid);
			temp = temp->next;
		}
	}
}

/**
* Remove a bid
*
* @param bidId The bid id to search for
*/
void HashTable::Remove(string bidId) {
	// Implement logic to remove a bid    <--------------------------------  (7) DONE
	int bucket = hash(stoi(bidId));   // stoi - string to int
	Node *temp = table[bucket];
	Node *prevTemp = table[bucket];

	// if first element in bucket remove it
	if (table[bucket]->bid.bidId == bidId) {
		table[bucket] = table[bucket]->next;
		return;
	}

	// If more than one element in bucket, iterate and drop one in question:
	temp = temp->next;
	while (!temp->bid.bidId.empty() && temp->bid.bidId != bidId) {
		prevTemp = temp;
		temp = temp->next;
		}

	// if found, remove
	if (temp->bid.bidId.empty()) {
		return;
	}
	// else remove current iter (temp)
	else {
		prevTemp->next = temp->next;
		return;
	}
}

/**
* Search for the specified bidId
*
* @param bidId The bid id to search for
*/
Bid HashTable::Search(string bidId) {
	Bid bid;

	// Implement logic to search for and return a bid   <--------------------------------  (8)  DONE
	int bucket = hash(stoi(bidId));   // stoi - string to int
	Node *temp = table[bucket];

	// iterate and return when found
	while (!temp->bid.bidId.empty()) {
		if (temp->bid.bidId == bidId) {
			bid = temp->bid;
			return bid;
		}
		temp = temp->next;
	}
	return bid;
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
void loadBids(string csvPath, HashTable* hashTable) {
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
			hashTable->Insert(bid);
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

	// Define a hash table to hold all the bids
	HashTable* bidTable;
	
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

		// initialize bidtable
		bidTable = new HashTable();

		switch (choice) {

		case 1:

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bidTable);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			cout << " TEST BELOW " << endl;   //---------------------------------------------------------------------------------------------------------TEST
			cout << bidTable->table[0]->bid.bidId<< endl; //------------------------------------------------------------------------------------------------------------------------------TEST
			break;

		case 2:
			bidTable->PrintAll();
			break;

		case 3:
			ticks = clock();

			bid = bidTable->Search(bidKey);

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
			bidTable->Remove(bidKey);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
