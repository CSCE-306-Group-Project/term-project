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
#include "order.h"
#include "transaction.h"

using namespace std;

class Shop {
private:
    // Orders keyed by order ID so we can look up any individual order
    unordered_map<int, Order*> orders;

    // Transactions keyed by order ID
    unordered_map<int, Transaction*> transactions;

    // we want each order to retrieve a unique ID, so basing it off real stores, we decided
    //to increment it by one in this class only so no other code could mess with it.
    int nextOrderID;

    // Here are the prices for the Tribbles, listed in an array.
    const double prices[6] = {0.0, 9.50, 16.15, 25.88, 28.15, 30.00};

public:
    // Constructor — nextOrderID starts at 1, ready for the first sale. Yippee
    Shop() : nextOrderID(1) {}

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

        Order* newOrder = new Order(nextOrderID, quantity, total);
        orders[nextOrderID] = newOrder;

        Transaction* newTransaction = new Transaction(customerID, nextOrderID);
        transactions[nextOrderID] = newTransaction;

        // This is where we write and don't read to a file. This will keep track of orders
        ofstream outFile("transactions.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile << "CustomerID: " << customerID
                    << " | " << newOrder->to_string() << "\n";
            outFile.close();
        } else {
            cout << "Warning: Could not write to transactions.txt\n";
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
    // which main() can use as asignal that the order ID is invalid.
    int getCustomerIDByOrderID(int orderID) {
        if (transactions.count(orderID)) {
            return transactions[orderID]->getCustomerID();
        }
        return -1;
    }
};


#endif /* SHOP_H_ */
