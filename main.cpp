
#include <iostream>
#include "customer.h"
#include <cstring>
#include <conio.h>

using namespace std;

int main(){
	// create empty associated array, Cust

	// pull from customers.txt
	// split by line
		// move each line into a new Customer object saved within Cust
		// Cust[somevalue] = memaddr for object


	cout << "Welcome. Enter an integer to select a menu option." << endl;
	cout << "\t(1) Add Customer\n";
	cout << "\t(2) Lookup Customer\n";
	cout << "\t(3) Exit Program\n";

	int userInput;
	cin >> userInput;

	if(userInput == 1){
		clrscr();

	}

	return 0;

}
