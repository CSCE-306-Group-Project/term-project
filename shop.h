/*
 * shop.h
 *
 *  Created on: Mar 4, 2026
 *      Author: chans
 */

#ifndef SHOP_H_
#define SHOP_H_


#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include "order.h"
#include "transaction.h"

using namespace std;

class Shop {
private:
    // Orders keyed by order ID so we can look up any individual order
    unordered_map<int, Order*> orders;

    // Transactions keyed by order ID
    unordered_map<int, Transaction*> transactions;

    deque<int> rainbowQueue;
    // we want each order to retrieve a unique ID, so basing it off real stores, we decided
    //to increment it by one in this class only so no other code could mess with it.
    int nextOrderID;

    //This will allow us to give new customers ID
    int nextCustomerID;

    // Here are the prices for the Tribbles, listed in an array.
    const double prices[6] = {0.0, 9.50, 16.15, 25.88, 28.15, 30.00};

public:
    // Constructor — nextOrderID starts at 1, ready for the first sale. Yippee

    // Constructor – used in making new IDs for inputed customers
    Shop() : nextOrderID(1), nextCustomerID(1) {}

    // Destructor
    //using pointers uses memory, so to save up on some space we delete them when cleaning up
    ~Shop() {
        for (auto& pair : orders) delete pair.second;
        for (auto& pair : transactions) delete pair.second;
    }

    //The main function for option 3 in the menu. It takes a customer ID and quantity,
    // builds the Order and Transaction objects, writes to transactions.txt,
    // and returns the created Order so main() can print the receipt.
    Order* processSale(int customerID, int quantity) {
        // Look up the correct price using our array a little up on this page
        double total = prices[quantity];

        time_t ts = time(nullptr);
        long orderID = ts % 1000000;

        Order* newOrder = new Order(orderID, quantity, total);
        orders[orderID] = newOrder;

        Transaction* newTransaction = new Transaction(customerID, orderID);
        transactions[orderID] = newTransaction;

        // This is where we write and don't read to a file. This will keep track of orders
        ofstream outFile("transactions.txt", std::ios::app);
        if (outFile.is_open()) {
        	// 000000 is salesStaff ID
            outFile << customerID << ";000000;" << newOrder->getOrderID() << endl;
            outFile.close();
        } else {
            cout << "Warning: Could not write to transactions.txt\n";
        }

        ofstream outFile_orders("orders.txt", std::ios::app);
        if (outFile_orders.is_open()) {

        	time_t t = time(nullptr);
        	tm* now = localtime(&t);
        	char currentTime[11];
        	strftime(currentTime, sizeof(currentTime), "%d-%b-%y", now);

        	outFile_orders << newOrder->getOrderID() << ";" << currentTime << ";" << newOrder->getQuantity() << ";" << newOrder->getPrice() << endl;

        	outFile_orders.close();
       } else {
           cout << "Warning: Could not write to orders.txt\n";
       }

        // Advance the counter so the next order gets a unique ID by adding one
        nextOrderID++;

        return newOrder;
    }

    // getOrdersByCustomerID walks the entire transactions map looking for
    // every transaction that belongs to the given customer, then collects
    // the corresponding Order objects into a vector and returns them.
    // This keeps all the search logic out of main() to not clutter it.
    vector<Order*> getOrdersByCustomerID(int customerID) {
        vector<Order*> result;
        for (auto& pair : transactions) {
            if (pair.second->getCustomerID() == customerID) {
                // The transaction's order ID is the key into our orders map
                result.push_back(orders[pair.second->getOrderID()]);
            }
        }
        return result;
    }

    // Direct lookup into the orders map. Returns nullptr if the order ID doesn't exist.
    Order* getOrderByID(int orderID) {
        if (orders.count(orderID)) {
            return orders[orderID];
        }
        return nullptr;
    }

    // Looks up the transaction keyed on order ID to find which customer
    // placed that order. Returns -1 if no matching transaction is found,
    // which main() can use as a signal that the order ID is invalid.
    int getCustomerIDByOrderID(int orderID) {
        if (transactions.count(orderID)) {
            return transactions[orderID]->getCustomerID();
        }
        return -1;
    }

    void loadTransactionList(const string& ordersFilename, const string& transactionsFilename){
    	ifstream ordersFile(ordersFilename);
    	if (!ordersFile.is_open()) return;

    	ifstream transactionsFile(transactionsFilename);
    	if (!transactionsFile.is_open()) return;

    	string line;

    	// build up the transactions vector, start with the orders file
		while (getline(ordersFile, line)) {
			if (line.empty()) continue; // address empty lines

			stringstream ss(line);
			string orderIDStr, dateStr, quantityStr, priceStr;

			getline(ss, orderIDStr, ';');
			getline(ss, dateStr, ';');
			getline(ss, quantityStr, ';');
			getline(ss, priceStr, ';');

			int orderID = stol(orderIDStr);
			int quantity = stoi(quantityStr);
			double price = stod(priceStr);

			Order* order = new Order(orderID, quantity, price);
			orders[orderID] = order;
		}

		// get the transactions
		while (getline(transactionsFile, line)) {
			if (line.empty()) continue; // skip empty lines

			stringstream ss(line);
			string customerIDStr, staffIDStr, orderIDStr;

			getline(ss, customerIDStr, ';');
			getline(ss, staffIDStr, ';');
			getline(ss, orderIDStr, ';');

			int customerID = stoi(customerIDStr);
			int orderID = stol(orderIDStr);

			// add to transactions vector if the order was found for the transaction
			if (orders.find(orderID) != orders.end()) {
				Transaction* transaction = new Transaction(customerID, orderID);
				transactions[orderID] = transaction;
			}
		}

    	ordersFile.close();
    	transactionsFile.close();
    }


    //Section 2 part 3 rainbow tribble goes here
    void loadRainbowList(const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) return; // no file yet, the queue remains empty
        int id;
        while (inFile >> id) {
            rainbowQueue.push_back(id);
        }
        inFile.close();
    }

    void saveRainbowList(const string& filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Warning: Could not write to " << filename << "\n";
            return;
        }
        for (int id : rainbowQueue) {
            outFile << id << "\n";
        }
        outFile.close();
    }

    // Adds a customer ID to the end of the queue, with duplicate check
    // Returns false if the customer is already on the list
    bool addToRainbowList(int customerID) {
        for (int id : rainbowQueue) {
            if (id == customerID) return false;
        }
        rainbowQueue.push_back(customerID);
        return true;
    }

    // Returns the customer ID at the front of the queue without removing them,
    // so main() can look up and display the customer before committing to the sale
    // Returns -1 if the queue is empty
    int peekRainbowFront() {
        if (rainbowQueue.empty()) return -1;
        return rainbowQueue.front();
    }

    // Pops the front of the queue after a confirmed sale
    void popRainbowFront() {
        if (!rainbowQueue.empty()) rainbowQueue.pop_front();
    }

    bool isRainbowListEmpty() {
        return rainbowQueue.empty();
    }

    // Call this after all customers are loaded from file, passing in
    // the idIndex so Shop can find the current highest ID
    void initCustomerID(const unordered_map<int, Customer*>& idIndex) {
        int maxID = 0;
        for (const auto& pair : idIndex) {
            if (pair.first > maxID) maxID = pair.first;
        }
        nextCustomerID = maxID + 1;
    }

    // Returns the next available customer ID and advances the counter
    int getNextCustomerID() {
        return nextCustomerID++;
    }


};


#endif /* SHOP_H_ */
