/*
 * salesStaff.h
 *
 *  Created on: Mar 30, 2026
 *      Author: Troy
 *
 *      This file contains all 5 classes for managing the sales team
 */

#ifndef SALESSTAFF_H_
#define SALESSTAFF_H_

#include <string>
using namespace std;

class salesTeam {
protected:
    string name;
    double commissionRate = 0;
    double grossSales = 0.0;
    int salesPersonID = 0;
    int bossID = 0;

public:
    virtual ~salesTeam() {}

    void addSale(double amount) { grossSales += amount; }

    double getGrossSales() const {
    	return grossSales; }
    int getSalesPersonID() const {
    	return salesPersonID; }
    int getBossID() const {
    	return bossID; }
    string getName() const {
    	return name; }
    virtual double getCommissionRate() {
    	return commissionRate; }

    virtual double getCommission() const = 0;

    // Overload for Supervisor and Manager who need subordinate sales total
    virtual double getCommission(double subordinateSales) const {
        return getCommission();
    }
};


// Sales: 5% of own gross sales
class salesPerson : public salesTeam {
public:
    salesPerson(string n, int spID, int bID) {
        name = n;
        salesPersonID = spID;
        bossID = bID;
        commissionRate = 0.05;
    }
    double getCommission() const override {
        return grossSales * commissionRate;
    }
};


// SuperSales: 6.5% of own gross sales
class superSalesPerson : public salesTeam {
public:
    superSalesPerson(string n, int spID, int bID) {
        name = n;
        salesPersonID = spID;
        bossID = bID;
        commissionRate = 0.065;
    }
    double getCommission() const override {
        return grossSales * commissionRate;
    }
};


// Supervisor: 6.5% own + 3% of direct subordinates
class supervisor : public salesTeam {
public:
    supervisor(string n, int spID, int bID) {
        name = n;
        salesPersonID = spID;
        bossID = bID;
        commissionRate = 0.065;
    }
    double getCommission() const override {
        return grossSales * commissionRate;
    }
    double getCommission(double subordinateSales) const override {
        return grossSales * 0.065 + subordinateSales * 0.03;
    }
};


// Manager: 6.5% own + 3% of everyone below
class manager : public salesTeam {
public:
    manager(string n, int spID) {
        name = n;
        salesPersonID = spID;
        bossID = 0;
        commissionRate = 0.065;
    }
    double getCommission() const override {
        return grossSales * commissionRate;
    }
    double getCommission(double subordinateSales) const override {
        return grossSales * 0.065 + subordinateSales * 0.03;
    }
};


#endif /* SALESSTAFF_H_ */
