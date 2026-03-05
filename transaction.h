/*
 * transaction.h
 *
 *  Created on: Mar 4, 2026
 *      Author: chans
 */

#ifndef TRANSACTION_H_
#define TRANSACTION_H_


class Transaction {
private:
    int customerID;
    int orderID;

public:
    // constructor
    Transaction() : customerID(0), orderID(0) {}

    // This will allow us to tie a customer to a specific order
    Transaction(int cID, int oID) : customerID(cID), orderID(oID) {}

    // Getters
    int getCustomerID() const { return customerID; }
    int getOrderID() const { return orderID; }
};





#endif /* TRANSACTION_H_ */
