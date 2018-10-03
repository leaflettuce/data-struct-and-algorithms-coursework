//============================================================================
// Name        : HashTable.cpp
// Author      : John Watson
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

// forward declarations
double strToDouble(string str, char ch);

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

//============================================================================
// Hash Table class definition
//============================================================================

/**
* Define a class containing data members and methods to
* implement a hash table with chaining.
*/
class HashTable {

private:
	// Define structures to hold bids        <--------------------------------  (1)   DONE?
	Bid bid;
	unsigned int hash(int key);

	// next in linked list of bucket
	HashTable *next;

	//double pointer for hashtable storage
	HashTable **table;

public:
	HashTable();
	virtual ~HashTable();
	void Insert(Bid bid);
	void PrintAll();
	void Remove(string bidId);
	Bid Search(string bidId);
};

/**
* Default constructor
*/
HashTable::HashTable() {
	// Initialize the structures used to hold bids       <--------------------------------  (2)  DONE?
	table = new HashTable*[DEFAULT_SIZE];

	for (int i = 0; i < DEFAULT_SIZE; i++){   //iter and create empty buckets
		table[i] = NULL;
	};
}

/**
* Destructor
*/
HashTable::~HashTable() { 
	// Implement logic to free storage when class is destroyed    <--------------------------------  (3)   DONE?
	for (int i = 0; i < DEFAULT_SIZE; i++) {
		delete table[i];
	}
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
	//  Implement logic to calculate a hash value    <--------------------------------  (4) REVISIT?
	int squaredKey, hashValue;

	// Implement simple hashing function
	hashValue = key % DEFAULT_SIZE;

	return hashValue;
}

/**
* Insert a bid
*
* @param bid The bid to insert
*/
void HashTable::Insert(Bid bid) {
	// Implement logic to insert a bid     <--------------------------------  (5)
	int bucket = hash(stoi(bid.bidId));   // stoi - string to int

	if (table[bucket] != NULL) {
		table[bucket]->next = bid;
	}
	else {
		table[bucket]->bid = bid;
	}
}


/**
* Print all bids
*/
void HashTable::PrintAll() {
	// Implement logic to print all bids    <--------------------------------  (6)
}

/**
* Remove a bid
*
* @param bidId The bid id to search for
*/
void HashTable::Remove(string bidId) {
	// Implement logic to remove a bid    <--------------------------------  (7)
}

/**
* Search for the specified bidId
*
* @param bidId The bid id to search for
*/
Bid HashTable::Search(string bidId) {
	Bid bid;

	// Implement logic to search for and return a bid   <--------------------------------  (8)

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

		switch (choice) {

		case 1:
			bidTable = new HashTable();

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bidTable);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
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
