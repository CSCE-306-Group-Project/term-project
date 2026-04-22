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
    std::string customerID;
    std::string orderID;

public:
    // constructor
    Transaction() : customerID(""), orderID("") {}

    // This will allow us to tie a customer to a specific order
    Transaction(string cID, string oID) : customerID(cID), orderID(oID) {}

    // Getters
    string getCustomerID() const { return customerID; }
    string getOrderID() const { return orderID; }
};





#endif /* TRANSACTION_H_ */
