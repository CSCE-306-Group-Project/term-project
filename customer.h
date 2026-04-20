/*
 * customer.h
 *
 *  Created on: Feb 23, 2026
 *      Author: Troy
 */
//test-CW hi back! once more this time last time I promise


#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
#include <cstring>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

class Customer{
private:
	string id;
	string firstName;
	string lastName;
	string address_1;
	string address_2;
	string address_3;
	string pswencoded;
	int postalCode;
	int phoneNumber;
public:
	Customer(){
		id = "0";
		postalCode = 0;
		phoneNumber = 0;
	}

	Customer(string fN, string lN, string a1, string a2, string a3, int postal, int phone, string psw, string idin){
		firstName = fN;
		lastName = lN;
		address_1 = a1;
		address_2 = a2;
		address_3 = a3;
		postalCode = postal;
		phoneNumber = phone;
		pswencoded = psw;

		if(idin == ""){
			id = rand();
		} else{
			id = idin;
		}
	}

	string getFirstName() const{
		return firstName;
	}
	string getLastName() const{
		return lastName;
	}
	string getID() const{
		return id;
	}
	string getFullAddress() const{
		return address_1 + "\n" + address_2 + ", " + address_3;
	}
	string getAddress1() const{
		return address_1;
	}
	string getAddress2() const{
		return address_2;
	}
	string getAddress3() const{
		return address_3;
	}
	string getEncodedPassword() const{
		return pswencoded;
	}
	int getPostalCode() const{
		return postalCode;
	}
	int getPhone() const{
		return phoneNumber;
	}

	void setFirstName(string fN){
		firstName = fN;
	}
	void setLastName(string lN){
		lastName = lN;
	}
	void setFullAddress(string a1, string a2, string a3, int postal){
		address_1 = a1;
		address_2 = a2;
		address_3 = a3;
		postalCode = postal;
	}
	void setAddress1(string a1){
		address_1 = a1;
	}
	void setAddress2(string a2){
		address_2 = a2;
	}
	void setAddress3(string a3){
		address_3 = a3;
	}
	void setPostalCode(int postal){
		postalCode = postal;
	}
	void setPhoneNumber(int phone){
		phoneNumber = phone;
	}
	void setPassword(string pswin){
		pswencoded = pswin;
	}


	void saveCustomers(const std::deque<Customer>& customers){
		// clear customers.txt and rewrite it

		// for each element in customers, write the following:
		// customer->getFirstName() << ";" << customer->getLastName() << endl;


		// open file in truncate (clears it)
		ofstream file("customers.txt", ios::trunc);

		if (!file.is_open()) {
		    throw runtime_error("Failed to open customers.txt");
		}

		// 007547;wuleeohv;Genevieve;Shears;118 W William St;Michigan City;IN;46360


	    for (const Customer& customer : customers) {
	    	// pad ID with 0's
	    	ostringstream ss;
	    	ss << customer.getID();

	        file << ss.str() << ";" << customer.getEncodedPassword() << ";" << customer.getFirstName() << ";" << customer.getLastName()
		         << ";" << customer.getAddress1() << ";" << customer.getAddress2() << ";" << customer.getAddress3() << ";" << customer.getPostalCode() << endl;
	    }

	    file.close();
	}
};


#endif /* CUSTOMER_H_ */
