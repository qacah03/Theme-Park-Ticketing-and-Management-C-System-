#pragma once
#ifndef ACCOUNTSTAFF_H
#define ACCOUNTSTAFF_H

#include<iostream>
#include <string>
using namespace std;
class AccountStaff
{
public://access specifier
	int STAFF_ID;//numerical attributes
	std::string IDENTIFICATION_NUMBER, STAFF_NAME, ADDRESS, PHONE_NUMBER, USERNAME, PASSWORD, EMAIL, STAFF_TYPE; // text attributes


	AccountStaff(); // constructor method
	AccountStaff(int STAFF_ID, std::string IDENTIFICATION_NUMBER, std::string STAFF_NAME, std::string ADDRESS, std::string PHONE_NUMBER, std::string USERNAME, std::string PASSWORD, std::string EMAIL, std::string STAFF_TYPE);
	bool login();
	void insert();
	void update(int staffid);
	void remove();
	int getAge();
	void viewProfileStaff();
	bool forgotPass();
	bool checkStaffAdmin();
	bool checkStaffManager();

	~AccountStaff(); //destructor method


	static AccountStaff older(AccountStaff a, AccountStaff b);


};

#endif

