/*
 * salesStaff.h
 *
 *  Created on: Mar 30, 2026
 *      Author: Troy
 *
 *
 *      This file contains all 5 classes for managing the sales team
 */

#ifndef SALESSTAFF_H_
#define SALESSTAFF_H_

#include <string>

class salesTeam{
protected:
	string name;
	double commissionRate = 0;
	double comission = 0;
public:
	salesTeam();
	virtual ~salesTeam();

	virtual double getCommissionRate(){return commissionRate;}
	virtual double getCommission() const = 0;
};



class salesPerson : public salesTeam{
private:
	string supervisorName;
public:
	salesPerson(string superName){
		supervisorName = superName;
		commissionRate = 0.05;
	}

	double getCommission() const override{
		return 0.0;
	}
};


class superSalesPerson : public salesTeam{
private:
	string supervisorName;
public:
	superSalesPerson(string superName){
		supervisorName = superName;
		commissionRate = 0.065;
	}

	double getCommission() const override{
		return 0.0;
	}
};


class supervisor : public salesTeam{
private:
	string managerName;
public:
	supervisor(string mgmtName){
		managerName = mgmtName;
		commissionRate = 0.065;
	}

	double getCommission() const override{
		return 0.0;
	}
};


class manager : public salesTeam{
public:
	manager(){
		commissionRate = 0.065;
	}

	double getCommission() const override{
		return 0.0;
	}
};



#endif /* SALESSTAFF_H_ */
