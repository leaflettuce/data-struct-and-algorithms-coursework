//============================================================================
// Name        : LinkedList.cpp
// Author      : Andrew Trick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
// Date		   : 09.18.2018
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

//============================================================================
// Linked-List class definition
//============================================================================

/**
* Define a class containing data members and methods to
* implement a linked-list.
*/
class LinkedList {

private:
	// Internal structure for list entries, housekeeping variables		<--- (1)
	struct Node {
		Bid bid;
		Node *next;
		};

	// Initilaize head and tail pointers & size int
	Node *head, *tail;
	int size;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append(Bid bid);
	void Prepend(Bid bid);
	void PrintList();
	void Remove(string bidId);
	Bid Search(string bidId);
	int Size();
};

/**
* Default constructor
*/
LinkedList::LinkedList() {
	// Initialize housekeeping variables		 <---- (2)
	head = NULL;
	tail = NULL;
	size = 0;
}

/**
* Destructor
*/
LinkedList::~LinkedList() {
}

/**
* Append a new bid to the end of the list
*/
void LinkedList::Append(Bid bid) {
	// Implement append logic			  <---- (3)
	Node *tmp = new Node;
	tmp->bid = bid;
	tmp->next = NULL;

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = tmp;
		tail = tmp;
	}
	size += 1;
	return;
}

/**
* Prepend a new bid to the start of the list
*/
void LinkedList::Prepend(Bid bid) {
	// Implement prepend logic			<------ (4)
	Node *tmp = new Node;
	tmp->bid = bid;
	tmp->next = head;

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		head = tmp;
	}

	size += 1;
	return;
}

/**
* Simple output of all bids in the list
*/
void LinkedList::PrintList() {
	// Implement print logic		   <-------- (5)
	Node *currObj = head;

	for (int i = 0; i < Size(); i++) {
		displayBid(currObj->bid);
		currObj = currObj->next;
	}
	return;
}

/**
* Remove a specified bid
*
* @param bidId The bid id to remove from the list
*/
void LinkedList::Remove(string bidId) {
	// Implement remove logic			 <------- (6)
	Node *currObj = head;
	Node *prevObj = NULL;

	for (int i = 0; i < Size(); i++) {
		if (currObj->bid.bidId == bidId) {
			// if head of list - drop it.
			if (currObj == head) {
				head = currObj->next;
			}
			// else link prev to next in list and drop
			else {
				prevObj->next = currObj->next;
			}
			size -= 1;
			return;
		}

		// Move to next nodes if no match
		prevObj = currObj;
		currObj = currObj->next;
	}

	// No match
	return;
}

/**
* Search for the specified bidId
*
* @param bidId The bid id to search for
*/
Bid LinkedList::Search(string bidId) {
	// Implement search logic       <------- (7)
	Node *currObj = head;

	for (int i = 0; i < Size(); i++) {
		if (currObj->bid.bidId == bidId) {
			return currObj->bid;
		}
		currObj = currObj->next;
	}
	Node *emptyBid = new Node;
	return emptyBid->bid;
}

/**
* Returns the current size (number of elements) in the list
*/
int LinkedList::Size() {
	return size;
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
* Display the bid information
*
* @param bid struct containing the bid info
*/
void displayBid(Bid bid) {

	cout << bid.bidId << ": " << bid.title << " | " << bid.amount
		<< " | " << bid.fund << endl;
	return;
}

/**
* Prompt user for bid information
*
* @return Bid struct containing the bid info
*/
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	cin.ignore();
	getline(cin, bid.bidId);

	cout << "Enter title: ";
	getline(cin, bid.title);

	cout << "Enter fund: ";
	cin >> bid.fund;

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/**
* Load a CSV file containing bids into a LinkedList
*
* @return a LinkedList containing all the bids read
*/
void loadBids(string csvPath, LinkedList *list) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (int i = 0; i < file.rowCount(); i++) {

			// initialize a bid using data from current row (i)
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

			// add this bid to the end
			list->Append(bid);
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
*
* @param arg[1] path to CSV file to load from (optional)
* @param arg[2] the bid Id to use when searching the list (optional)
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

	clock_t ticks;

	LinkedList bidList;

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Enter a Bid" << endl;
		cout << "  2. Load Bids" << endl;
		cout << "  3. Display All Bids" << endl;
		cout << "  4. Find Bid" << endl;
		cout << "  5. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			bid = getBid();
			bidList.Append(bid);
			displayBid(bid);

			break;

		case 2:
			ticks = clock();

			loadBids(csvPath, &bidList);

			cout << bidList.Size() << " bids read" << endl;

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " milliseconds" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 3:
			bidList.PrintList();

			break;

		case 4:
			ticks = clock();

			bid = bidList.Search(bidKey);

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

		case 5:
			bidList.Remove(bidKey);

			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
