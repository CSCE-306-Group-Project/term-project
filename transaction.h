/*
 * transaction.h
 *
 *  Created on: Mar 4, 2026
 *      Author: chans
 */

#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>

class Transaction {
private:
    string customerID;
    int orderID;

public:
    // constructor
    Transaction() : customerID(""), orderID(0) {}

    // This will allow us to tie a customer to a specific order
    Transaction(string cID, int oID) : customerID(cID), orderID(oID) {}

    // Getters
    string getCustomerID() const { return customerID; }
    int getOrderID() const { return orderID; }
};





#endif /* TRANSACTION_H_ */
