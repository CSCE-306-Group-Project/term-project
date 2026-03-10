#include <iostream>
#include "customer.h"
#include <cstring>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <limits>
#include <fstream>
#include <sstream>
#include <deque>
#include <chrono>
#include <thread>

#include "shop.h"

using namespace std;

deque<Customer> customers;
unordered_map<int, Customer*> idIndex;
unordered_map<string, vector<Customer*>> lastNameIndex;

void addCustomer(Customer c) {

	customers.push_back(c);

	Customer *ptr = &customers.back();

	idIndex[ptr->getID()] = ptr;
	lastNameIndex[ptr->getLastName()].push_back(ptr);
}

//Code for progress bar found on https://www.geeksforgeeks.org/cpp/sleep-function-in-cpp/
void verifyAddressCASS(string a1, string a2, string a3, int pbar, int processDelay){
	 cout << "Please wait a moment. Processing: [";
	 for (int i = 0; i < pbar; i++) {
	         // Print one character of progress
	         cout << "#";
	         cout.flush();
	         this_thread::sleep_for(chrono::milliseconds(processDelay));
	 }
	 cout << "] \nAddress verified :)" << endl;
}

int main() {
	// create empty associated array, Cust
	Shop shop;
	// pull from customers.txt
	// split by line
	// move each line into a new Customer object saved within Cust
	// Cust[somevalue] = memaddr for object

	// Get customers file
	ifstream inputFile("customers.txt");
	if (!inputFile.is_open()) {
		cout << "File customers.txt not found on disk. Program terminated.";
		return 1;
	}

	string customerdata;

	// loop through each line in the input file
	while (getline(inputFile, customerdata)) {

		// Create a string stream with the line from the input file
		stringstream ss(customerdata);
		string parts, fname, lname, a1, a2, a3;
		int postal, id;
		int inputSectionNumber = 0;

		// For each section of the user input
		// Split the input by semi-colon
		while (getline(ss, parts, ';')) {

			/*
			 * inputSectionNumber meaning:
			 * 0 = ID
			 * 1 = first name
			 * 2 = last name
			 * 3 = street
			 * 4 = city
			 * 5 = state
			 * 6 = zip code
			 */
			if (inputSectionNumber == 0) {
				id = stoi(parts);
			} else if (inputSectionNumber == 1) {
				fname = parts;
			} else if (inputSectionNumber == 2) {
				lname = parts;
			} else if (inputSectionNumber == 3) {
				a1 = parts;
			} else if (inputSectionNumber == 4) {
				a2 = parts;
			} else if (inputSectionNumber == 5) {
				a3 = parts;
			} else if (inputSectionNumber == 6) {
				postal = stoi(parts);
			} else {
				cout << "Invalid Input in customers.txt. Program Terminated";
				return 1;
			}

			// Cycle to next section
			inputSectionNumber++;
		}

		Customer c(fname, lname, a1, a2, a3, postal, 0, id);
		addCustomer(c);
	}

	inputFile.close();

	bool doMenu = true;
	int userInputMainMenu = 0;
	cout << "Welcome! ";

	while (doMenu) {

		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		cout << "\tEnter an integer to select a menu option." << endl;
		cout << "\t(1) Add Customer\n";
		cout << "\t(2) Lookup Customer\n";
		cout << "\t(3) Buy Tribble\n";
		cout << "\t(4) Get placed on the waiting list for the elusive Rainbow Tribble\n";
		cout << "\t(5) Exit Program\n";

		userInputMainMenu = 0;
		cin >> userInputMainMenu;

		if (userInputMainMenu == 1) {
			string fN;
			string lN;
			string a1;
			string a2;
			string a3;
			int postal;
			int phone;

			cout << endl << "[Add Customer] (1/7) Customer First Name:" << endl;
			getline(cin, fN);
			cout << "[Add Customer] (2/7) Customer Last Name:" << endl;
			getline(cin, lN);
			cout << "[Add Customer] (3/7) Customer Address Line 1 (Street):" << endl;
			getline(cin, a1);
			cout << "[Add Customer] (4/7) Customer Address Line 2 (City/Locality):" << endl;
			getline(cin, a2);
			cout << "[Add Customer] (5/7) Customer Address Line 3 (State/Providence):" << endl;
			getline(cin, a3);
			cout << "[Add Customer] (6/7) Customer Postal Code:" << endl;
			cin >> postal;

			cout << "Verifying address through Coding Accuracy Support System."<< endl;
			verifyAddressCASS(a1, a2, a3, 20, 100);
			//To simulate sending the address data out to an external database that checks addresses.

			cout << "[Add Customer] (7/7) Customer Phone Number:" << endl;
			cin >> phone;

			// TODO
			Customer c(fN, lN, a1, a2, a3, postal, phone);

			addCustomer(c);

			cout << endl << "Customer added successfully.\n";

		} else if (userInputMainMenu == 2) {
			int customerSearchInputInt = 0;

			cout << endl
					<< "[Lookup Customer] Enter an integer to select a search method:";
			cout << endl << "\t(1) Search By Last Name";
			cout << endl << "\t(2) Search By ID\n";
			cout << endl << "\t(3) Search by Order #\n";

			cin >> customerSearchInputInt;

			if (customerSearchInputInt == 1) {

				string searchName;

				cout << endl << "[Lookup Customer] Enter last name to search:";
				getline(cin, searchName);

				if (lastNameIndex.count(searchName)) {

					vector<Customer*> results = lastNameIndex[searchName];

					if(results.size() == 1){

		            //if we only have one then just show it
		            Customer* c = results[0];

		            cout << "\nFound Customer:\n";
		            cout << c->getFirstName() << " "
		                 << c->getLastName() << endl;
		            cout << c->getFullAddress() << endl;
		            cout << "Phone: " << c->getPhone() << endl;

		        } else {

		            // when we have multiple last name we can let user to select
		            cout << "\nMultiple customers found:\n";

		            for (size_t i = 0; i < results.size(); ++i) {
		                cout << "(" << i + 1 << ") "
		                     << results[i]->getFirstName() << " "
		                     << results[i]->getLastName()
		                     << " (ID: " << results[i]->getID() << ")"
		                     << endl;
		            }

		            cout << "\nSelect a customer by number: ";
		            int choice;
		            cin >> choice;

		            if (choice > 0 && static_cast<size_t>(choice) <= results.size()) {

		                Customer* selected = results[static_cast<size_t>(choice) - 1];

		                cout << "\nSelected Customer:\n";
		                cout << selected->getFirstName() << " "
		                     << selected->getLastName() << endl;
		                cout << selected->getFullAddress() << endl;
		                cout << "Phone: " << selected->getPhone() << endl;

		            } else {
		                cout << "\nInvalid selection.\n";
		            }
		        }

		    } else {
		        cout << "\nNo customer found.\n";
		    }

			} else if (customerSearchInputInt == 2) {
				int searchID;

				cout << endl << "[Lookup Customer] Enter ID to search:";
				cin >> searchID;

				if (idIndex.count(searchID)) {

					Customer *c = idIndex[searchID];

					cout << "\nFound Customer:\n";
					cout << c->getFirstName() << " " << c->getLastName()
							<< endl;
					cout << c->getFullAddress() << endl;
					cout << "Phone: " << c->getPhone() << endl;

				} else {
					cout << "\nNo customer found.\n";
				}

			} else if (customerSearchInputInt == 3) {
			    int searchOrderID;
			    cout << endl << "[Lookup Customer] Enter Order #: ";
			    cin >> searchOrderID;

			    // Ask Shop to find the order — returns nullptr if it doesn't exist
			    Order* foundOrder = shop.getOrderByID(searchOrderID);

			    if (foundOrder == nullptr) {
			        cout << "\nNo order found with that ID.\n";
			    } else {
			        // Now find the customer who placed this order
			        int custID = shop.getCustomerIDByOrderID(searchOrderID);
			        Customer* c = idIndex[custID];

			        cout << "\nOrder Found:\n";
			        cout << foundOrder->to_string() << "\n";
			        cout << "Placed by: " << c->getFirstName() << " " << c->getLastName() << "\n";
			        cout << c->getFullAddress() << "\n";
			        cout << "Phone: " << c->getPhone() << "\n";
			    }
			}

		} else if (userInputMainMenu == 3) {
			//This one leads to the tribble buying menu
			int custID, qty;

			    cout << "\nEnter Customer ID: ";
			    cin >> custID;

			    // Verify the customer actually exists before proceeding
			    if (!idIndex.count(custID)) {
			        cout << "\nNo customer found with that ID.\n";
			    } else {
			        Customer* c = idIndex[custID];
			        cout << "\nWelcome to the Tribble Store, " << c->getFirstName() << "!\n";
			        cout << "Enter the number of Tribbles you wish to purchase:\n";
			        cout << "\t(1) $9.50\n";
			        cout << "\t(2) $16.15\n";
			        cout << "\t(3) $25.88\n";
			        cout << "\t(4) $28.15\n";
			        cout << "\t(5) $30.00\n";
			        cout << "\t(6) Exit store\n";
			        cin >> qty;

			        if (qty >= 1 && qty <= 5) {
			            Order* o = shop.processSale(custID, qty);
			            cout << "\n--- Receipt ---\n";
			            cout << "Customer: " << c->getFirstName() << " " << c->getLastName() << "\n";
			            cout << "You have purchased " << o->getQuantity() << " Tribble(s) for $"
			                 << fixed << setprecision(2) << o->getPrice() << "\n";
			            cout << "Order ID: " << o->getOrderID() << "\n";
			            cout << "---------------\n";
			        } else if (qty == 6) {
			            cout << "\nReturning to main menu.\n";
			        } else {
			            cout << "\nInvalid selection.\n";
			        }
			    }
			} else if (userInputMainMenu == 4) {
			//This one leads to the elusive rainbow tribble waiting list
			doMenu = false;
		} else if (userInputMainMenu == 5) {
			//This one stops the function
			doMenu = false;
		} else {
			cout << endl << "The input provided is not allowed.";
		}

	}

	cout << endl << "Goodbye";
	return 0;

}
