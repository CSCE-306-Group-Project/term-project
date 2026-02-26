#include <iostream>
#include "customer.h"
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unordered_map>
using namespace std;

vector<Customer> customers;
unordered_map<int, Customer*> idIndex;
unordered_map<string, vector<Customer*>> lastNameIndex;

void addCustomer(Customer c){

    customers.push_back(c);

    Customer* ptr = &customers.back();

    idIndex[ptr->getID()] = ptr;
    lastNameIndex[ptr->getLastName()].push_back(ptr);
}

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

	int userInputMainMenu;
	cin >> userInputMainMenu;

	if(userInputMainMenu == 1){
		string fN;
		string lN;
		string a1;
		string a2;
		string a3;
		int postal;
		int phone;

		cout << endl << "[Add Customer] (1/7) Customer First Name:" << endl;
		cin >> fN;
		cout << "[Add Customer] (2/7) Customer Last Name:" << endl;
		cin >> lN;
		cout << "[Add Customer] (3/7) Customer Address Line 1:" << endl;
		cin >> a1;
		cout  << "[Add Customer] (4/7) Customer Address Line 2:" << endl;
		cin >> a2;
		cout << "[Add Customer] (5/7) Customer Address Line 3:" << endl;
		cin >> a3;
		cout << "[Add Customer] (6/7) Customer Postal Code:" << endl;
		cin >> postal;
		cout << "[Add Customer] (7/7) Customer Phone Number:" << endl;
		cin >> phone;

		// TODO
		Customer c(fN, lN, a1, a2, a3, postal, phone);

		addCustomer(c);

		cout << endl << "Customer added successfully.\n";
		return 0;

	} else if(userInputMainMenu == 2){
		int customerSearchInputInt;

		cout << endl << "[Lookup Customer] Enter an integer to select a search method:";
		cout << endl << "\t(1) Search By Last Name";
		cout << endl << "\t(2) Search By ID\n";

		cin >> customerSearchInputInt;

		if(customerSearchInputInt == 1){

		    string searchName;

		    cout << endl << "[Lookup Customer] Enter last name to search:";
		    cin >> searchName;

		    if(lastNameIndex.count(searchName)){

		        vector<Customer*> results = lastNameIndex[searchName];

		        for(Customer* c : results){

		            cout << "\nFound Customer:\n";
		            cout << c->getFirstName() << " "
		                 << c->getLastName() << endl;
		            cout << c->getFullAddress() << endl;
		            cout << "Phone: " << c->getPhone() << endl;
		        }

		    } else {
		        cout << "\nNo customer found.\n";
		    }

		    return 0;
		} else if(customerSearchInputInt == 2){
			int searchID;

			    cout << endl << "[Lookup Customer] Enter ID to search:";
			    cin >> searchID;

			    if(idIndex.count(searchID)){

			        Customer* c = idIndex[searchID];

			        cout << "\nFound Customer:\n";
			        cout << c->getFirstName() << " "
			             << c->getLastName() << endl;
			        cout << c->getFullAddress() << endl;
			        cout << "Phone: " << c->getPhone() << endl;

			    } else {
			        cout << "\nNo customer found.\n";
			    }

			    return 0;
		}

	} else if(userInputMainMenu == 3){
		cout << endl << "Goodbye";
		return 0;
	} else{
		cout << endl << "The input provided is not allowed. Terminating.";
	}

	return 0;

}
