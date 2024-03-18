#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account
{
	friend class Ticket;

public://access specifier
	int CUST_ID;//numerical attributes
	std::string CUST_PHONE, CUST_NAME,CUST_USERNAME, CUST_PASSWORD, CUST_ADDRESS, CUST_EMAIL; // text attributes


	Account(); // constructor method
	Account(int CUST_ID, std::string CUST_PHONE, std::string CUST_NAME, std::string CUST_USERNAME, std::string CUST_PASSWORD, std::string CUST_ADDRESS, std::string CUST_EMAIL);
	bool login();
	void insert();
	void update(int custid);
	void remove();
	int getAge();
	string getid();
	void viewProfileUser();
	void passvisual();
	int getCustID();
	bool forgotpass();

	~Account(); //destructor method


	static Account older(Account a, Account b);


};

#endif
