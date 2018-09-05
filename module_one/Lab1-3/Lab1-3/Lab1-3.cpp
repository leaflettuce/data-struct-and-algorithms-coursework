//============================================================================
// Name        : Lab1-3.cpp
// Author      : Andrew Trick
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 1-3 Up to Speed in C++
//============================================================================

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// FIXME (1): Define a data structure to hold bid information together as a single unit of storage.
struct bidInfo {
	string title;
	string fund;
	string vehicleID;
	double bidAmount;
};

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

// FIXME (4): Display the bid values passed in data structure
/**
* Display the bid information
*
* @param ?type? data structure containing the bid info
*/
void displayBid(bidInfo bid) {
	cout << "Title: " << bid.title << endl;
	cout << "Fund: " << bid.fund << endl;
	cout << "Vehicle: " << bid.vehicleID << endl;
	cout << "Bid Amount: " << bid.bidAmount << endl;

	return;
}

// FIXME (3): Store input values in data structure
/**
* Prompt user for bid information
*
* @return data structure containing the bid info
*/
bidInfo getBid() {
	bidInfo newBid;

	cout << "Enter title: ";
	cin.ignore();
	getline(cin, newBid.title);

	cout << "Enter fund: ";
	cin >> newBid.fund;

	cout << "Enter vehicle: ";
	cin.ignore();
	getline(cin, newBid.vehicleID);

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	getline(cin, strAmount);
	newBid.bidAmount = strToDouble(strAmount, '$');

	return newBid;
}


/**
* The one and only main() method
*/
int main() {

	// FIXME (2): Declare instance of data structure to hold bid information
	bidInfo currentBid;

	// loop to display menu until exit chosen
	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Enter Bid" << endl;
		cout << "  2. Display Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		// FIXME (5): Complete the method calls then test the program
		switch (choice) {
		case 1:
			currentBid = getBid();
			break;
		case 2:
			displayBid(currentBid);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
