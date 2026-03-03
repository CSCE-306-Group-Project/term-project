/*
 * customer.h
 *
 *  Created on: Feb 23, 2026
 *      Author: Troy
 */
//test-CW hi back! once more this time


#ifndef CUSTOMER_H_
#define CUSTOMER_H_
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

class Customer{
private:
	int id;
	string firstName;
	string lastName;
	string address_1;
	string address_2;
	string address_3;
	int postalCode;
	int phoneNumber;
public:
	Customer(){
		id = rand();
		postalCode = 0;
		phoneNumber = 0;
	}

	Customer(string fN, string lN, string a1, string a2, string a3, int postal, int phone, int idin = 0){
		firstName = fN;
		lastName = lN;
		address_1 = a1;
		address_2 = a2;
		address_3 = a3;
		postalCode = postal;
		phoneNumber = phone;

		if(idin == 0){
			id = rand();
		} else{
			id = idin;
		}
	}

	string getFirstName(){
		return firstName;
	}
	string getLastName(){
		return lastName;
	}
	int getID(){
		return id;
	}
	string getFullAddress(){
		return address_1 + "\n" + address_2 + ", " + address_3 + "\nPhone:" + to_string(phoneNumber) + "\n";
	}
	string getAddress1(){
		return address_1;
	}
	string getAddress2(){
		return address_2;
	}
	string getAddress3(){
		return address_3;
	}
	int getPostalCode(){
		return postalCode;
	}
	int getPhone(){
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

};


#endif /* CUSTOMER_H_ */
