/*
 * customer.h1
 *
 * phase 2 - Part 1
 * customer class redesigned to match customers.txt format.
 * ID must be stored as a 6-digit STRING (important for leading zeros).
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>

class Customer {
private:
    std::string id;          // 6-digit ID (
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;

public:
    // default constructor (needed for containers)
    Customer() {}

    // constructor used when loading from file
    Customer(std::string idIn,
             std::string fN,
             std::string lN,
             std::string addr,
             std::string cityIn,
             std::string stateIn,
             std::string zipIn)
        : id(idIn),
          firstName(fN),
          lastName(lN),
          address(addr),
          city(cityIn),
          state(stateIn),
          zip(zipIn)
    {}

    // getters (const because we are not modifying the object)
    std::string getID() const { return id; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }

    // formats full address nicely
    std::string getFullAddress() const {
        return address + "\n" + city + ", " + state + " " + zip;
    }
};

#endif