//============================================================================
// Name        : Lab1-3.cpp
// Author      : Andrew Trick
// Course      : CS - 260  Data Structures and Algorithms
// Date		   : 09.06.2018
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


// Data structure to hold bid information together
struct bidInfo {
	string title;
	string fund;
	string vehicleID;
	double bidAmount;
};


/**
* Helper function to convert a string to a double
* after stripping out unwanted char
*
* credit: http://stackoverflow.com/a/24875936
*
* @param ch - The character to strip out
*/
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}


/**
* Display the bid information
*
* @param bid - The structure containing the bid info
*/
void displayBid(bidInfo bid) {
	cout << "Title: " << bid.title << endl;
	cout << "Fund: " << bid.fund << endl;
	cout << "Vehicle: " << bid.vehicleID << endl;
	cout << "Bid Amount: " << bid.bidAmount << endl;

	return;
}


/**
* Prompt user for bid information
*
* @return newBid - Data structure containing the bid info
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

	// Declare struct to hold bid information
	bidInfo currentBid;

	// loop to display menu until exit chosen
	int choice = 0;
	while (choice != 9) {		      // 9 ends loop
		cout << "Menu:" << endl;
		cout << "  1. Enter Bid" << endl;
		cout << "  2. Display Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		// Check for user input and run sought function
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

	return 0;	    // Ends CLI program
}
