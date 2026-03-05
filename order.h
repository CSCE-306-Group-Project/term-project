/*
 * order.h
 *
 *  Created on: Mar 4, 2026
 *      Author: chans
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;


class Order {
private:
    int orderID;
    int quantity;
    double price;

public:
    // For this class we will have three things, orderID to make it unique
    // quantity as the customer can buy up to five at a time, and the price that goes with it
    Order() : orderID(0), quantity(0), price(0.0) {}

    Order(int id, int qty, double p) : orderID(id), quantity(qty), price(p) {}

    // Getters
    int getOrderID() const { return orderID; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }


    string to_string() const {
        ostringstream oss;
        oss << "Order #" << orderID
            << " | Qty: " << quantity
            << " | Total: $" << fixed << setprecision(2) << price;
        return oss.str();
    }
};


#endif /* ORDER_H_ */
