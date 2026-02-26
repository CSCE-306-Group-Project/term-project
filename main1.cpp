#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "customer.h1"

using namespace std;

// using unique_ptr so vector reallocation does NOT break our pointers
vector<unique_ptr<Customer>> customers;

// index for fast lookup by ID
unordered_map<string, Customer*> idIndex;

// index for fast lookup by last name
unordered_map<string, vector<Customer*>> lastNameIndex;


// adds a customer to all data structures
void addCustomer(unique_ptr<Customer> c) {

    Customer* ptr = c.get(); // raw pointer used only for indexing

    // storing in main vector
    customers.push_back(move(c));
    // index by ID
    idIndex[ptr->getID()] = ptr;
    // index by last name
    lastNameIndex[ptr->getLastName()].push_back(ptr);
}


// loads customers.txt file at program start
void loadCustomers(const string& filename) {

    ifstream file(filename);

    if (!file) {
        cout << "Error opening customers.txt\n";
        return;
    }

    string line;

    while (getline(file, line)) {

        if (line.empty()) continue;

        stringstream ss(line);

        string id, fN, lN, addr, city, state, zip;

        //split by semicolon
        getline(ss, id, ';');
        getline(ss, fN, ';');
        getline(ss, lN, ';');
        getline(ss, addr, ';');
        getline(ss, city, ';');
        getline(ss, state, ';');
        getline(ss, zip, ';');

        // create customer object from file data
        auto customerPtr = make_unique<Customer>(id, fN, lN, addr, city, state, zip);

        addCustomer(move(customerPtr));
    }

    cout << "Customers loaded successfully.\n";
}


int main() {

    // Load file at startup (Part 1 requirement demo)
    loadCustomers("customers.txt");

    cout << "\nWelcome. Enter an integer to select a menu option.\n";
    cout << "\t(1) Lookup Customer\n";
    cout << "\t(2) Exit Program\n";

    int userInput;
    cin >> userInput;

    if (userInput == 1) {

        cout << "\nSearch method:\n";
        cout << "\t(1) Search By Last Name\n";
        cout << "\t(2) Search By ID\n";

        int searchChoice;
        cin >> searchChoice;

        // ===============================
        // SEARCH BY LAST NAME
        // ===============================
        if (searchChoice == 1) {

            string searchName;
            cout << "\nEnter last name: ";
            cin >> searchName;

            auto it = lastNameIndex.find(searchName);

            if (it == lastNameIndex.end()) {
                cout << "\nNo customers found.\n";
                return 0;
            }

            vector<Customer*>& results = it->second;

            // If multiple customers have same last name
            cout << "\nMatches found:\n";

            for (int i = 0; i < results.size(); i++) {
                cout << "(" << i + 1 << ") "
                     << results[i]->getFirstName()
                     << " | ID: "
                     << results[i]->getID()
                     << endl;
            }

            cout << "Select a customer: ";
            int selection;
            cin >> selection;

            if (selection < 1 || selection > results.size()) {
                cout << "Invalid selection.\n";
                return 0;
            }

            Customer* chosen = results[selection - 1];

            cout << "\nCustomer Details:\n";
            cout << chosen->getFirstName() << " "
                 << chosen->getLastName() << endl;
            cout << chosen->getFullAddress() << endl;
        }

        // ===============================
        // SEARCH BY ID
        // ===============================
        else if (searchChoice == 2) {

            string searchID;
            cout << "\nEnter ID: ";
            cin >> searchID;

            auto it = idIndex.find(searchID);

            if (it == idIndex.end()) {
                cout << "\nNo customer found.\n";
                return 0;
            }

            Customer* c = it->second;

            cout << "\nCustomer Details:\n";
            cout << c->getFirstName() << " "
                 << c->getLastName() << endl;
            cout << c->getFullAddress() << endl;
        }
    }

    cout << "\nGoodbye.\n";
    return 0;
}