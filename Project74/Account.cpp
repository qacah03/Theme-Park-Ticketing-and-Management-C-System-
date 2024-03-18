#include "Account.h"
#include"Ticket.h"
#include <ctime>
#include "DBConnection.h" 
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

//Constructor to initialize variable
Account::Account() {
	//initialize
	CUST_ID = 0;
	CUST_PHONE = "";
	CUST_NAME = "";
	CUST_USERNAME = "";
	CUST_PASSWORD = "";
	CUST_ADDRESS = "";
	CUST_EMAIL = "";
}

//Overloading constructor
Account::Account(int CUST_ID, std::string CUST_PHONE, std::string CUST_NAME, std::string CUST_USERNAME, std::string CUST_PASSWORD, std::string CUST_ADDRESS, std::string CUST_EMAIL) {
	this->CUST_ID = CUST_ID;
	this->CUST_PHONE = CUST_PHONE;
	this->CUST_NAME = CUST_NAME;
	this->CUST_USERNAME = CUST_USERNAME;
	this->CUST_PASSWORD = CUST_PASSWORD;
	this->CUST_ADDRESS = CUST_ADDRESS;
	this->CUST_EMAIL = CUST_EMAIL;
}

//Destructor
Account::~Account() {}

//To ensure that if the user has logged in or not by checking the data from the database
bool Account::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM CUSTOMER WHERE CUST_USERNAME=? AND CUST_PASSWORD=?");
	db.stmt->setString(1, CUST_USERNAME);
	db.stmt->setString(2, CUST_PASSWORD);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			CUST_ID = db.res->getInt("CUST_ID");
			CUST_PHONE = db.res->getString("CUST_PHONE");
			CUST_NAME = db.res->getString("CUST_NAME");
			CUST_USERNAME = db.res->getString("CUST_USERNAME");
			CUST_PASSWORD = db.res->getString("CUST_PASSWORD");
			CUST_ADDRESS = db.res->getString("CUST_ADDRESS");
			CUST_EMAIL = db.res->getString("CUST_EMAIL");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}

//To insert values related to customer's information into database
void Account::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("INSERT INTO CUSTOMER (CUST_PHONE,CUST_NAME,CUST_USERNAME,CUST_PASSWORD,CUST_ADDRESS,CUST_EMAIL) VALUES (?,?,?,?,?,?)");
	//db.stmt->setInt(1, CUST_ID);
	db.stmt->setString(1, CUST_PHONE);
	db.stmt->setString(2, CUST_NAME);
	db.stmt->setString(3, CUST_USERNAME);
	db.stmt->setString(4, CUST_PASSWORD);
	db.stmt->setString(5, CUST_ADDRESS);
	db.stmt->setString(6, CUST_EMAIL);
	db.QueryStatement();
	db.~DBConnection();
}

//To view profile
void Account::viewProfileUser()
{
	cout << bgWhite;
	cout << MAGENTA;
	cout << "+------------------------------------+" << endl;
	cout << "||=>      CUSTOMER'S PROFILE      <=||" << endl;
	cout << "+------------------------------------+" << endl;
	cout << bgBlack;
	cout << WHITE;
	cout << RESET << endl;
	cout << "\n---------------------------------------------------------------------------------------" << endl;
	cout << "Customer ID\t\t| " << CUST_ID << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Phone Number\t\t| " << CUST_PHONE << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Name\t\t\t| " << CUST_NAME << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Username\t\t| " << CUST_USERNAME << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "Address\t\t\t| " << CUST_ADDRESS << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "EMail\t\t\t| " << CUST_EMAIL << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
}

//To update customer's profile
void Account::update(int custid) {

	DBConnection db;
	
	db.prepareStatement("UPDATE CUSTOMER SET CUST_PHONE=?, CUST_USERNAME=?, CUST_PASSWORD=?, CUST_ADDRESS=?, CUST_EMAIL=? WHERE CUST_ID=?");
	db.stmt->setString(1, CUST_PHONE);
	db.stmt->setString(2, CUST_USERNAME);
	db.stmt->setString(3, CUST_PASSWORD);
	db.stmt->setString(4, CUST_ADDRESS);
	db.stmt->setString(5, CUST_EMAIL);
	//db.stmt->setInt(4, yearOfBirth);
	db.stmt->setInt(6, custid);
	db.QueryStatement();
	db.~DBConnection();

}

//To get Customer's id
int Account::getCustID()
{
	return CUST_ID;
}


//To get customer's password if they have forgotten it
bool Account::forgotpass()
{
	DBConnection db;

	db.prepareStatement("SELECT CUST_PASSWORD FROM CUSTOMER WHERE CUST_EMAIL = ?");
	db.stmt->setString(1, CUST_EMAIL);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) 
		{
			CUST_PASSWORD = db.res->getString("CUST_PASSWORD");
		}
		return true;
	}
	else {

		
		return false;
	}

	db.~DBConnection();
}