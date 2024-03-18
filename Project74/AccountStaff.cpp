#include "AccountStaff.h"
#include <ctime>
#include "DBConnection.h" 
#include<iostream>
using namespace std;

//Text and background color
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define GRAY    "\033[0;37m"
#define LIGHT_RED     "\033[1;31m"
#define LIGHT_GREEN   "\033[1;32m"
#define LIGHT_YELLOW  "\033[1;33m"
#define LIGHT_BLUE    "\033[1;34m"
#define LIGHT_MAGENTA "\033[1;35m"
#define LIGHT_CYAN    "\033[1;36m"

#define bgBlack  "\033[40m"
#define bgRed  "\033[41m";
#define bgGreen  "\033[42m";
#define bgYellow  "\033[43m";
#define bgBlue  "\033[44m";
#define bgMagenta  "\033[45m";
#define bgCyan  "\033[46m";
#define bgWhite  "\033[47m";

//Constructor
AccountStaff::AccountStaff() {
	//initialize
	STAFF_ID = 0;
	IDENTIFICATION_NUMBER = "";
	STAFF_NAME = "";
	ADDRESS = "";
	PHONE_NUMBER = "";
	USERNAME = "";
	PASSWORD = "";
	EMAIL = "";
	STAFF_TYPE = "";
}

//Overloading constructor
AccountStaff::AccountStaff(int STAFF_ID, std::string IDENTIFICATION_NUMBER, std::string STAFF_NAME, std::string ADDRESS, std::string PHONE_NUMBER, std::string USERNAME, std::string PASSWORD, std::string EMAIL, std::string STAFF_TYPE) {
	this->STAFF_ID = STAFF_ID;
	this->IDENTIFICATION_NUMBER = IDENTIFICATION_NUMBER;
	this->STAFF_NAME = STAFF_NAME;
	this->ADDRESS = ADDRESS;
	this->PHONE_NUMBER = PHONE_NUMBER;
	this->USERNAME = USERNAME;
	this->PASSWORD = PASSWORD;
	this->EMAIL = EMAIL;
	this->STAFF_TYPE = STAFF_TYPE;
}

//Destructor
AccountStaff::~AccountStaff() {}

//To ensure that the staff has logged in by checking their data from the database
bool AccountStaff::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM STAFF WHERE USERNAME=? AND PASSWORD=?");
	db.stmt->setString(1, USERNAME);
	db.stmt->setString(2, PASSWORD);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			STAFF_ID = db.res->getInt("STAFF_ID");
			IDENTIFICATION_NUMBER = db.res->getString("IDENTIFICATION_NUMBER");
			STAFF_NAME = db.res->getString("STAFF_NAME");
			ADDRESS = db.res->getString("ADDRESS");
			PHONE_NUMBER = db.res->getString("PHONE_NUMBER");
			USERNAME = db.res->getString("USERNAME");
			PASSWORD = db.res->getString("PASSWORD");
			EMAIL = db.res->getString("EMAIL");
			STAFF_TYPE = db.res->getString("STAFF_TYPE");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}

//To insert values into the database
void AccountStaff::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("INSERT INTO STAFF (STAFF_ID,IDENTIFICATION_NUMBER,STAFF_NAME,ADDRESS,PHONE_NUMBER,USERNAME,PASSWORD,EMAIL,STAFF_TYPE) VALUES (?,?,?,?,?,?,?,?,?)");
	db.stmt->setInt(1, STAFF_ID);
	db.stmt->setString(2, IDENTIFICATION_NUMBER);
	db.stmt->setString(3, STAFF_NAME);
	db.stmt->setString(4, ADDRESS);
	db.stmt->setString(5, PHONE_NUMBER);
	db.stmt->setString(6, USERNAME);
	db.stmt->setString(7, PASSWORD);
	db.stmt->setString(8, EMAIL);
	db.stmt->setString(9, STAFF_TYPE);
	db.QueryStatement();
	db.~DBConnection();
}

//To view staff's profile
void AccountStaff::viewProfileStaff()
{
	cout << bgWhite;
	cout << MAGENTA;
	cout << "+---------------------------------+" << endl;
	cout << "||=>      STAFF'S PROFILE      <=||" << endl;
	cout << "+---------------------------------+" << endl;
	cout << bgBlack;
	cout << WHITE;
	cout << RESET << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Staff ID\t\t| " << STAFF_ID << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Identification Number\t| " << IDENTIFICATION_NUMBER << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Name\t\t\t| " << STAFF_NAME << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Address\t\t\t| " << ADDRESS << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Phone Number\t\t| " << PHONE_NUMBER << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Username\t\t| " << USERNAME << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "EMail\t\t\t| " << EMAIL << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
}

//To update staff's profile
void AccountStaff::update(int staffid) {

	DBConnection db;
	db.prepareStatement("UPDATE STAFF SET ADDRESS=?, PHONE_NUMBER=?, USERNAME=?, PASSWORD=?, EMAIL=?, STAFF_TYPE=? WHERE STAFF_ID=?");
	db.stmt->setString(1, ADDRESS);
	db.stmt->setString(2, PHONE_NUMBER);
	db.stmt->setString(3, USERNAME);
	db.stmt->setString(4, PASSWORD);
	db.stmt->setString(5, EMAIL);
	//db.stmt->setInt(4, yearOfBirth);
	db.stmt->setString(6, STAFF_TYPE);
	db.stmt->setInt(7, staffid);
	db.QueryStatement();
	db.~DBConnection();

}

//To retrieve staff's password if forgotten
bool AccountStaff::forgotPass()
{
	DBConnection db;

	db.prepareStatement("SELECT PASSWORD FROM STAFF WHERE IDENTIFICATION_NUMBER = ?");
	db.stmt->setString(1, IDENTIFICATION_NUMBER);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next())
		{
			PASSWORD = db.res->getString("PASSWORD");
		}
		return true;
	}
	else {


		return false;
	}

	db.~DBConnection();
}

//To check if staff is an admin
bool AccountStaff::checkStaffAdmin()
{
	DBConnection db;

	db.prepareStatement("SELECT STAFF_TYPE FROM STAFF WHERE STAFF_ID = ?");
	db.stmt->setInt(1, STAFF_ID);
	db.QueryResult();
	while (db.res->next()) {
		STAFF_TYPE = db.res->getString("STAFF_TYPE");
	}
	db.~DBConnection();

	if (STAFF_TYPE == "Admin")
	{
		return true;
	}
	else
	{
		false;
	}	
}

//To verify if the staff is a manager
bool AccountStaff::checkStaffManager()
{
	DBConnection db;

	db.prepareStatement("SELECT STAFF_TYPE FROM STAFF WHERE STAFF_ID = ?");
	db.stmt->setInt(1, STAFF_ID);
	db.QueryResult();
	while (db.res->next()) {
		STAFF_TYPE = db.res->getString("STAFF_TYPE");
	}
	db.~DBConnection();

	if (STAFF_TYPE == "Manager")
	{
		return true;
	}
	else
	{
		false;
	}
}
