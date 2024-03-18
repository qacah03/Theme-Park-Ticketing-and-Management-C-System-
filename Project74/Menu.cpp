#include "Menu.h"
#include <iostream>
#include <conio.h>
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

//constructor
Menu::Menu() {
	
	options = 0;

}

//Menus for customer
void Menu::loginmenu(bool loggedin)
{
	int option;

	//If the user has logged in
	if (loggedin)
	{
		cout << bgWhite;
		cout << MAGENTA;
		cout << "========================================" << endl;
		cout << "             CUSTOMER'S MENU            " << endl;
		cout << "========================================" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
		cout << bgWhite;
		cout << MAGENTA;
		cout << "+=-------------------------------------+" << endl;
		cout << "||      (1) : View Profile            ||" << endl;;
		cout << "||      (2) : View Promotions         ||" << endl;
		cout << "||      (3) : View Ticket Category    ||" << endl;
		cout << "||      (4) : Purchase Ticket         ||" << endl;
		cout << "||      (5) : View Tickets Purchased  ||" << endl;
		cout << "||      (6) : Payment                 ||" << endl;
		cout << "||      (7) : Refund and Cancellation ||" << endl;
		cout << "||      (8) : View Booking Details    ||" << endl;
		cout << "||      (9) : View Booking History    ||" << endl;
		cout << "||     (10) : Help                    ||" << endl;
		cout << "||     (11) : Exit                    ||" << endl;
		cout << "+=-------------------------------------+" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
	}
	else			//If the user has not logged in
	{
		cout << bgWhite;
		cout << MAGENTA;
		cout << "========================================" << endl;
		cout << "             CUSTOMER'S MENU            " << endl;
		cout << "========================================" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
		cout << bgWhite;
		cout << MAGENTA;
		cout << "+--------------------------------------+" << endl;
		cout << "||      (1) : Log in to your account  ||" << endl;
		cout << "||      (2) : Create an account       ||" << endl;
		cout << "||      (3) : View Promotions         ||" << endl;
		cout << "||      (4) : View Ticket Category    ||" << endl;
		cout << "||      (5) : Back                    ||" << endl;
		cout << "+--------------------------------------+" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
	}
}

//Menus for staff
void Menu::loginmenuStaff(bool loggedin)
{
	int option;

	//If the staff has logged in
	if (loggedin)
	{
		cout << bgWhite;
		cout << MAGENTA;
		cout << "===========================================================" << endl;
		cout << "                         STAFF'S MENU                      " << endl;
		cout << "===========================================================" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
		cout << bgWhite;
		cout << MAGENTA;
		cout << "+---------------------------------------------------------+" << endl;
		cout << "||      (1) : View Profile                               ||" << endl;
		cout << "||      (2) : Update Ticket Availability (Admin only)    ||" << endl;
		cout << "||      (3) : Update Promotions  (Admin only)            ||" << endl;
		cout << "||      (4) : Get Monthly Sales Report  (Manager only)   ||" << endl;
		cout << "||      (5) : Exit                                       ||" << endl;
		cout << "+---------------------------------------------------------+" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
	}
	else
	{
		cout << bgWhite;
		cout << MAGENTA;
		cout << "============================================" << endl;
		cout << "                 STAFF'S MENU               " << endl;
		cout << "============================================" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
		cout << bgWhite;
		cout << MAGENTA;
		cout << "+------------------------------------------+" << endl;
		cout << "||      (1) : Log in to your account      ||" << endl;
		cout << "||      (2) : Create an account           ||" << endl;
		cout << "||      (3) : Back                        ||" << endl;
		cout << "+------------------------------------------+" << endl;
		cout << bgBlack;
		cout << WHITE;
		cout << RESET << endl;
	}
}

//destructor
Menu::~Menu() {}
