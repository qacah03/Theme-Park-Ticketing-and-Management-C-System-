#include <iostream>  
using namespace std;
#include <conio.h>
#include <iomanip>
#include <sstream>
#include<string>
#include<windows.h>
#include<stdio.h>
#include <ctime>
#include <cctype>
#include <limits>

#include <SFML/Audio.hpp>

#include <thread>
#include <atomic> // For std::atomic

// advanced
// include our custom class
#include "Account.h" 
#include "AccountStaff.h" 
#include "Menu.h"
#include"DBConnection.h"
#include"Ticket.h"

void updateProfile();	//to update customer's profile
void updateProfileStaff();	//to update staff's profile
void registerAccount();		//For customers to register an account
void registerAccountStaff();	//For staff to register an account
void loginMenu();		//For customers to login
void loginMenuStaff();		//For staff to login
void updateTicket();		//For admin to update ticket availability
void updatePromo();		//For admin to update ticket's promotions
double PurchaseTicket();	//For customers to make a ticket's purchase
void viewPromo();		//For customers to view current promotions
void viewTicket();		//For customers to view ticket's category and prices
void refundAndCancellation();
bool has_number(const string& str);		//To check if the string contain any number
bool has_symbol(const std::string& str);	//To check if the string contain any symbol
void newpayment(double);		//For customers to make payment on their booking
void DeleteBooking();		//For customers to cancel and refund their booking
void forgotPass();			//For customer's and staff if they forgot their passwords
int id = 107, ids = 106; //global variable 
bool loggedin = false;		//global variable that stores user's login status
int custid;		//global variable to store customer's id
int staffid;	//global variable to store staff's id
int bookid;		//global variable to store booking id
int bookcatid;		//global variable to store bookcatid
bool hasbook = false;		//global variable that stores booking status
bool haspay = false;		//global variable that stores payment status

std::atomic<bool> stopPlaying(false);

void playSong1() {
	sf::Music song1;
	if (!song1.openFromFile("sound3.mp3")) {
		std::cerr << "Error loading first song!" << std::endl;
		return;
	}

	song1.play();
	while (song1.getStatus() == sf::SoundSource::Playing && !stopPlaying) {
		// Wait for the first song to finish playing or the stop signal
	}

	song1.stop(); // Stop the song explicitly
}

void playSong2() {
	sf::Music song2;
	if (!song2.openFromFile("sound1.wav")) {
		std::cerr << "Error loading second song!" << std::endl;
		return;
	}

	song2.play();
	while (song2.getStatus() == sf::SoundSource::Playing && !stopPlaying) {
		// Wait for the second song to finish playing or the stop signal
	}

	song2.stop(); // Stop the song explicitly
}

//color design 
enum Color {
	Black,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White,
	Gray,
	Light_Blue,
	Light_Green,
	Light_Aqua,
	Light_Red,
	Light_Purple,
	Light_Yellow,
	Bright_White,
};

//text design
enum Text
{
	Underline,
	Reset_Underline,
};

//background color
string background(Color color) {
	switch (color) {
	case Black:
		return "\u001b[40m";
	case Blue:
		return "\u001b[44m";
	case Green:
		return "\u001b[42m";
	case Cyan:
		return "\u001b[46m";
	case Red:
		return "\u001b[41m";
	case Magenta:
		return "\u001b[45m";
	case Yellow:
		return "\u001b[43m";
	case White:
		return "\u001b[47m";
	case Gray:
		return "\u001b[40;1m";
	case Light_Blue:
		return "\u001b[44;1m";
	case Light_Green:
		return "\u001b[42;1m";
	case Light_Aqua:
		return "\u001b[46;1m";
	case Light_Red:
		return "\u001b[41;1m";
	case Light_Purple:
		return "\u001b[45;1m";
	case Light_Yellow:
		return "\u001b[43;1m";
	case Bright_White:
		return "\u001b[47;1m";
	default:
		throw std::invalid_argument("invalid value");
	}
}

//text color
string foreground(Color color) {
	switch (color) {
	case Black:
		return "\033[1;30m";
	case Blue:
		return "\u001b[34m";
	case Green:
		return "\u001b[32m";
	case Cyan:
		return "\u001b[36m";
	case Red:
		return "\u001b[31m";
	case Magenta:
		return "\u001b[35m";
	case Yellow:
		return "\u001b[33m";
	case White:
		return "\u001b[37m";
	case Gray:
		return "\u001b[30;1m";
	case Light_Blue:
		return "\u001b[34;1m";
	case Light_Green:
		return "\u001b[32;1m";
	case Light_Aqua:
		return "\u001b[36;1m";
	case Light_Red:
		return "\u001b[31;1m";
	case Light_Purple:
		return "\u001b[35;1m";
	case Light_Yellow:
		return "\u001b[33;1m";
	case Bright_White:
		return "\u001b[37;1m";
	default:
		throw std::invalid_argument("invalid value");
	}
}
string resetANSI() {
	return "\u001b[0m";
}
string underline(Text reply)
{
	switch (reply)
	{
	case Underline:
		return "\033[4m";
	case Reset_Underline:
		return "\033[0m";
	}

}


int main() {

	//Menu mainmenu;
	//loginMenu();
	Ticket ticket;
	Account user;
	AccountStaff staff;
	Menu menu;
	bool loggedin = false;
	bool valid = false;
	int option;
	int ans;

	//int id = 107, ids = 106;
	 //Text and background color constant
	const char* red = "\033[1;31m";
	const char* green = "\033[1;32m";
	const char* yellow = "\033[1;33m";
	const char* reset = "\033[0m";
	const char* blue = "\033[1;34m";
	const char* magenta = "\033[1;35m";
	const char* cyan = "\033[1;36m";
	const char* white = "\033[37m";
	const char* black = "\033[30m";

	const char* bgBlack = "\033[40m";
	const char* bgRed = "\033[41m";
	const char* bgGreen = "\033[42m";
	const char* bgYellow = "\033[43m";
	const char* bgBlue = "\033[44m";
	const char* bgMagenta = "\033[45m";
	const char* bgCyan = "\033[46m";
	const char* bgWhite = "\033[47m";

	std::thread thread1(playSong1);
	//Loading Bar
	system("COLOR 0e");
	system("cls");
	printf("\n[?251");
	SetConsoleCP(437);
	SetConsoleOutputCP(437);

	int bar1 = 177, bar2 = 219;

	cout << "\n\n\n\t\t\t\tOPENING THE SYSTEM";
	cout << "\n\n\n\t\t\t\t";

	for (int i = 0; i < 25; i++)
		cout << (char)bar1;

	cout << "\r";
	cout << "\t\t\t\t";

	for (int i = 0; i < 25; i++)
	{
		cout << (char)bar2;
		Sleep(200);
	}
	system("cls");

	std::thread thread2(playSong2);

	// Print a colorful word
	cout << cyan << "\t\t\t\t\t\t\t\t\t _   _  _____  _   _  _  _____  _____  ___    _____  _   _    " << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t( ) ( )(  _  )( ) ( )(_)(  _  )(  _  )(  _`\\ (  _  )( ) ( )   " << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t| |_| || (_) || `\\| || || ( ) || (_) || ( (_)| (_) || |_| |   " << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t|  _  ||  _  || , ` || || | | ||  _  || |  _ |  _  ||  _  |   " << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t| | | || | | || |`\\ || || (('\\|| | | || (_( )| | | || | | |   " << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t(_) (_)(_) (_)(_) (_)(_)(___\\_)(_) (_)(____/'(_) (_)(_) (_)   " << endl;
	cout << magenta << "\t\t\t\t\t\t\t\t\t\tTHEME PARK TICKETING AND MANAGEMENT SYSTEM" << endl << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t\t===============================================                            " << endl;
	std::cout << magenta << "\t\t\t\t\t\t\t\t\t\t\tWELCOME " << red << "TO" << green << " HANIQACAH " << yellow << "THEME" << blue << " PARK" << endl;
	cout << cyan << "\t\t\t\t\t\t\t\t\t\t===============================================" << white << endl;
	cout << endl << endl;
	//cout << reset << endl;

	while (1)
	{
		//main menu
		cout << background(White) << foreground(Magenta) << endl;
		cout << "=============================" << endl;
		cout << "          MAIN MENU          " << endl;
		cout << "=============================" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+---------------------------+" << endl;
		cout << "||       [1] : Staff       ||" << endl;
		cout << "||       [2] : Customer    ||" << endl;
		cout << "||       [3] : Exit        ||" << endl;
		cout << "+---------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;
		cout << endl << endl;
		while (1)
		{
			cout << "Enter your option : ";
			cin >> ans;
			if (cin.fail()) {
				cout << "Invalid input. Please enter an integer." << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				break;
			}
		}

		cout << endl;
		cout << "\nPress enter to continue..." << endl;
		cin.ignore();
		cin.get();             // Waiting for user input
		system("cls");        // Clearing the console screen
		if (ans == 1)
		{
			menu.loginmenuStaff(loggedin);		//call function for staff's login 
			cout << endl << endl;
			while (1)
			{
				cout << "Please enter your option : ";
				cin >> option;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			system("PAUSE");
			system("cls");
			if (option == 1)
			{
				loginMenuStaff();
				system("PAUSE");
				system("cls");
				break;
			}
			else if (option == 2)
			{
				registerAccountStaff();
				system("PAUSE");
				system("cls");

			}
			else if (option == 3)
			{
				cout << "\nPress enter to continue..." << endl;
				cin.ignore();
				cin.get();             // Waiting for user input
				system("cls");        // Clearing the console screen
			}
			else
			{
				cout << "You have entered an invalid option, Please re-enter!!" << endl;
				system("PAUSE");
				system("cls");
			}

		}
		else if (ans == 2)
		{
			//Customer's menu
			menu.loginmenu(loggedin);
			while (1)
			{
				cout << "Please enter your option : ";
				cin >> option;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			system("PAUSE");
			system("cls");
			if (option == 1)
			{
				//Go to customer's login function
				loginMenu();
				system("PAUSE");
				system("cls");
				break;
			}
			else if (option == 2)
			{
				//Register account for customer
				registerAccount();
				system("PAUSE");
				system("cls");
			}
			else if (option == 3)
			{
				//For customer to view real-time promotions
				ticket.viewPromo();
				cout << "You have to log in to your account to continue" << endl;
				system("PAUSE");
				system("cls");
			}
			else if (option == 4)
			{
				//For customer to view available ticket
				ticket.viewTicket();
				system("PAUSE");
				system("cls");
			}
			else if (option == 5)
			{
				//Exit the customer's menu
				cout << "\nPress enter to continue..." << endl;
				cin.ignore();
				cin.get();             // Waiting for user input
				system("cls");        // Clearing the console screen
			}
			else
			{
				//Customer entered an invalid option, need to re-enter
				cout << "You have entered an invalid option, Please re-enter!!" << endl;
				system("PAUSE");
				system("cls");
			}
		}
		else if (ans == 3)
		{
			//Exit the system
			cout << blue << " /$$$$$$$$ /$$   /$$  /$$$$$$  /$$   /$$ /$$   /$$       /$$     /$$ /$$$$$$  /$$   /$$" << endl;
			cout << blue << "|__  $$__/| $$  | $$ /$$__  $$| $$$ | $$| $$  /$$/      |  $$   /$$//$$__  $$| $$  | $$" << endl;
			cout << blue << "   | $$   | $$  | $$| $$  \\ $$| $$$$| $$| $$ /$$/        \\  $$ /$$/| $$  \\ $$| $$  | $$" << endl;
			cout << blue << "   | $$   | $$$$$$$$| $$$$$$$$| $$ $$ $$| $$$$$/          \\  $$$$/ | $$  | $$| $$  | $$" << endl;
			cout << blue << "   | $$   | $$__  $$| $$__  $$| $$  $$$$| $$  $$           \\  $$/  | $$  | $$| $$  | $$" << endl;
			cout << blue << "   | $$   | $$  | $$| $$  | $$| $$\\  $$$| $$\\  $$           | $$   | $$  | $$| $$  | $$" << endl;
			cout << blue << "   | $$   | $$  | $$| $$  | $$| $$ \\  $$| $$ \\  $$          | $$   |  $$$$$$/|  $$$$$$/" << endl;
			cout << blue << "   |__/   |__/  |__/|__/  |__/|__/  \\__/|__/  \\__/          |__/    \\______/  \\______/ " << endl;
			break;
		}
		else
		{
			//Users entered an invalid options
			cout << "You have entered an invalid option, Please re-enter!!" << endl;
			system("PAUSE");
			system("cls");
		}


	}
	// Signal the threads to stop
	stopPlaying = true;

	// Join the threads to wait for them to finish before exiting
	thread1.join();
	thread2.join();
	return 0;
}

//Function used to register customer's account
void registerAccount()
{
	Account newacc;
	DBConnection db;

	std::string gender;
	std::string idlabel;
	int age = 5;
	string tmpinput, tempPass;
	char ch;
	bool valid = true;
	string name, address;
	while (1) {
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+----------------------------------------------+" << endl;
		cout << "||=>    CUSTOMER'S ACCOUNT RESGISTRATION    <=||" << endl;
		cout << "+----------------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;

		cout << "(e.g : 019-4749115)" << endl;
		cout << "Enter your phone number            : ";
		cin >> newacc.CUST_PHONE;
		cout << endl;
		cout << "Enter your full name               : ";
		cin.ignore();
		getline(cin, newacc.CUST_NAME);
		cout << endl;
		cout << "(e.g : nafies_aqasyah)" << endl;
		cout << "Enter your username                : ";
		cin >> newacc.CUST_USERNAME;
		cout << endl;
		while (1)
		{
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "|   Your password should contain :   |" << endl;
			cout << "+   (1) At least 1 number            +" << endl;
			cout << "|   (2) : At least 1 symbols         |" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "(e.g : nafies100_)" << endl;
			cout << "Enter your password                : ";
			while (true)
			{
				ch = _getch();
				if (ch == 13) // Enter key
					break;
				else if (ch == 8) // Backspace key
				{
					if (!tmpinput.empty())
					{
						tmpinput.pop_back();
						cout << "\b \b"; // Move the cursor back and erase the character
					}
				}
				else
				{
					cout << '*';
					tmpinput.push_back(ch);
				}
			}

			//To check if the password contain number and symbol
			if (has_number(tmpinput) == true)
			{
				if (has_symbol(tmpinput) == true)
				{
					cout << "\nRe-enter your password             : ";
					while (true)
					{
						ch = _getch();
						if (ch == 13) // Enter key
							break;
						else if (ch == 8) // Backspace key
						{
							if (!tempPass.empty())
							{
								tempPass.pop_back();
								cout << "\b \b"; // Move the cursor back and erase the character
							}
						}
						else
						{
							cout << '*';
							tempPass.push_back(ch);
						}
					}
					cout << endl;
					if (tempPass == tmpinput)
					{
						newacc.CUST_PASSWORD = tmpinput;
						break;
					}
					else
					{
						tempPass = "";
						tmpinput = "";
						cout << "Your re-entered password are not the same!, Please re-enter!!" << endl;
					}
				}
				else
				{
					tmpinput = "";
					cout << "Your password does not contain any symbols, Please re-enter your password!!" << endl;
					system("PAUSE");
					system("cls");
				}
			}
			else
			{
				tmpinput = "";
				cout << "Your password does not contain any number, Please re-enter your password!!" << endl;
				system("PAUSE");
				system("cls");
			}
		}
		cout << endl;
		cout << "Enter your address                 : ";
		cin.ignore();
		getline(cin, newacc.CUST_ADDRESS);
		cout << "Enter your email                   : ";
		cin >> newacc.CUST_EMAIL;

		newacc.insert();		//insert the data inserted by user into database
		break;


	}


}

//Function to register staff's account
void registerAccountStaff()
{
	AccountStaff newacc;
	DBConnection db;
	std::string gender;
	std::string idlabel;
	//int id = 106;
	int age;
	string tmpinput, tempPass;
	bool valid = true;
	char name[100], address[100], ch;

	while (1) {
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << "||=>     STAFF'S ACCOUNT REGISTRATION     <=||" << endl;
		cout << "+--------------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;
		//id++;
		//ids++;
		//cout << "Your Staff id is = " << ids << endl;
		//newacc.STAFF_ID = ids;
		cout << "(e.g : 000000-00-0000)" << endl;
		cout << "Enter your identification number    : ";
		cin >> newacc.IDENTIFICATION_NUMBER;
		cout << endl;
		cout << "Enter your full name                : ";
		cin.ignore();
		std::getline(cin, newacc.STAFF_NAME);
		cout << endl;
		//cin.getline(name, 100);
		//std::string fname(name);
		//newacc.CUST_NAME = fname;
		cout << "Enter your address                  : ";
		cin.ignore();
		std::getline(cin, newacc.ADDRESS);
		cout << "\n(e.g : 000-0000000)" << endl;
		cout << "Enter your phone number             : ";
		cin >> newacc.PHONE_NUMBER;
		cout << "\n(e.g : nafies_aqasyah)" << endl;
		cout << "Enter your username                 : ";
		cin >> newacc.USERNAME;
		cout << "\n(Manager / Admin / Normal)" << endl;
		cout << "Enter your staff type               : ";
		cin >> newacc.STAFF_TYPE;
		cout << endl;
		while (1)
		{
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "+   Your password should contain :   +" << endl;
			cout << "|   (1) At least 1 number            |" << endl;
			cout << "+   (2) : At least 1 symbols         +" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "(e.g : nafies100_)" << endl;
			cout << "Enter your password                 : ";
			while (true)
			{
				ch = _getch();
				if (ch == 13) // Enter key
					break;
				else if (ch == 8) // Backspace key
				{
					if (!tmpinput.empty())
					{
						tmpinput.pop_back();
						cout << "\b \b"; // Move the cursor back and erase the character
					}
				}
				else
				{
					cout << '*';
					tmpinput.push_back(ch);
				}
			}

			//To check if the password entered contain number and symbol
			if (has_number(tmpinput) == true)
			{
				if (has_symbol(tmpinput) == true)
				{
					cout << "\nRe-enter your password              : ";
					while (true)
					{
						ch = _getch();
						if (ch == 13) // Enter key
							break;
						else if (ch == 8) // Backspace key
						{
							if (!tempPass.empty())
							{
								tempPass.pop_back();
								cout << "\b \b"; // Move the cursor back and erase the character
							}
						}
						else
						{
							cout << '*';
							tempPass.push_back(ch);
						}
					}
					cout << endl;
					if (tempPass == tmpinput)
					{
						newacc.PASSWORD = tmpinput;
						break;
					}
					else
					{
						tempPass = "";
						tmpinput = "";
						cout << "Your re-entered password are not the same!, Please re-enter!!" << endl;
					}
				}
				else
				{
					tmpinput = "";
					cout << "Your password does not contain any symbols, Please re-enter your password!!" << endl;
					system("PAUSE");
					system("cls");
				}
			}
			else
			{
				tmpinput = "";
				cout << "Your password does not contain any number, Please re-enter your password!!" << endl;
				system("PAUSE");
				system("cls");
			}
		}

		cout << endl;
		cout << "Enter your email                    : ";
		cin >> newacc.EMAIL;

		//Insert the data entered by the user into the database
		newacc.insert();
		cout << endl << endl;
		break;
	}
}

//Function for the customer to login to their account
void loginMenu()
{
	int ans;
	int answer;
	int answers;
	Menu menu;
	Account user;
	int option;
	Ticket ticket;
	double totalprice = 0;
	int i = 0;
	string tmpinput = "";
	string password;
	char ch;
	int loginAttempt = 0;
	string mail;


	while (1) {
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+-------------------------------------+" << endl;
		cout << "||=>     CUSTOMER'S LOGIN MENU     <=||" << endl;
		cout << "+-------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;

		cout << "Enter your username : ";
		cin >> user.CUST_USERNAME;
		cout << "Enter your password : ";
		while (true)
		{
			ch = _getch();
			if (ch == 13) // Enter key
				break;
			else if (ch == 8) // Backspace key
			{
				if (!tmpinput.empty())
				{
					tmpinput.pop_back();
					cout << "\b \b"; // Move the cursor back and erase the character
				}
			}
			else
			{
				cout << '*';
				tmpinput.push_back(ch);
			}
		}


		user.CUST_PASSWORD = tmpinput;

		//if the customer successfully login, excecute the statements below
		if (user.login()) {
			//home(user);
			custid = user.CUST_ID;
			loggedin = true;
			cout << endl << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "    You have been logged in to your account    " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
			system("PAUSE");
			system("cls");
			while (1)
			{
				menu.loginmenu(loggedin);		//Print customer's after login menu
				cout << endl << endl;
				while (1)
				{
					cout << "Enter your options : ";
					cin >> option;
					if (cin.fail()) {
						cout << "Invalid input. Please enter an integer." << endl;
						cin.clear();
						cin.ignore();
					}
					else {
						break;
					}
				}

				cout << endl;
				system("PAUSE");
				system("cls");

				//If user choose to view their profile
				if (option == 1)
				{
					hasbook = true;
					haspay = true;
					user.viewProfileUser();		//Call the function to view customer's profile
					cout << "--==--==--==--==--==--==--==--==--==--==--==--==--==--" << endl;
					cout << "Do you want to update any information of your profile?" << endl;
					cout << "(1) Yes" << endl;
					cout << "(2) No" << endl;
					cout << "--==--==--==--==--==--==--==--==--==--==--==--==--==--" << endl << endl;
					while (1)
					{
						cout << "Answer (Enter the digit only) :";
						cin >> answer;
						if (cin.fail()) {
							cout << "Invalid input. Please enter an integer." << endl;
							cin.clear();
							cin.ignore();
						}
						else {
							break;
						}
					}


					//If the user choose to update their profile
					if (answer == 1)
					{
						updateProfile();		//Call the function to update their profile
					}
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 2)		//If the user choose the option to view available promotions
				{
					hasbook = true;
					haspay = true;
					ticket.viewPromo();		//Call the function to view promotions
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 3)		//If the user choose the option to view available tickets
				{
					hasbook = true;
					haspay = true;
					ticket.viewTicket();	//Call the function to view available ticket
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 4)		//If the user choose the option to purchase tickets
				{
					hasbook = false;
					haspay = false;
					totalprice = PurchaseTicket();		//Call the function for the user to purchase tickets
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 5)		//If the user choose to view the ticket's they purchased
				{
					//if the user has made a booking
					if (hasbook)
					{
						ticket.ViewTicketPurchased();		//Call the function to view ticket's purchased
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You have not make any ticket booking yet!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 6)		//If the user choose to make a payment
				{
					//if the user has made a booking
					if (hasbook)
					{
						haspay = false;
						//Call the function to make a payment
						newpayment(totalprice);
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You have not make any ticket booking yet!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					system("COLOR 07");
				}
				else if (option == 7)		//If the user choose to delete and refund their booking
				{
					hasbook = true;
					DeleteBooking();		//Call the function to delete booking
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 8)		//If the user choose the option to view their 
				{
					//If the user made a booking and pay
					if (hasbook)
					{
						if (haspay)
						{
							ticket.BookingDetails();		//Call the function to view booking details;
						}
						else
						{
							cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
							cout << "   You have not make your payment yet!   " << endl;
							cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
						}
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You have not make any ticket booking yet!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 9)		//if the user choose the option to view all past booking
				{
					haspay = true;
					hasbook = true;
					ticket.viewAllBooking(custid);		//Call the function to view all past booking
					system("PAUSE");
					system("cls");
				}
				else if (option == 10)
				{
					haspay = true;
					hasbook = true;
					system("start https://wa.me/60194749115?text=Hi,%20i%20need%20help,%20please%20help%20me");
					system("PAUSE");
					system("cls");
				}
				else if (option == 11)		//If the user choose the option to exit the system
				{
					if (hasbook)
					{
						if (haspay)
						{
							cout << " /$$$$$$$$ /$$   /$$  /$$$$$$  /$$   /$$ /$$   /$$       /$$     /$$ /$$$$$$  /$$   /$$" << endl;
							cout << "|__  $$__/| $$  | $$ /$$__  $$| $$$ | $$| $$  /$$/      |  $$   /$$//$$__  $$| $$  | $$" << endl;
							cout << "   | $$   | $$  | $$| $$  \\ $$| $$$$| $$| $$ /$$/        \\  $$ /$$/| $$  \\ $$| $$  | $$" << endl;
							cout << "   | $$   | $$$$$$$$| $$$$$$$$| $$ $$ $$| $$$$$/          \\  $$$$/ | $$  | $$| $$  | $$" << endl;
							cout << "   | $$   | $$__  $$| $$__  $$| $$  $$$$| $$  $$           \\  $$/  | $$  | $$| $$  | $$" << endl;
							cout << "   | $$   | $$  | $$| $$  | $$| $$\\  $$$| $$\\  $$           | $$   | $$  | $$| $$  | $$" << endl;
							cout << "   | $$   | $$  | $$| $$  | $$| $$ \\  $$| $$ \\  $$          | $$   |  $$$$$$/|  $$$$$$/" << endl;
							cout << "   |__/   |__/  |__/|__/  |__/|__/  \\__/|__/  \\__/          |__/    \\______/  \\______/ " << endl;
							break;
						}
						else
						{
							cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
							cout << "You have not pay your ticket booking yet. Please proceed with the payment before exit this program!" << endl;
							cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
							system("PAUSE");
							system("cls");
						}
					}
				}
				else
				{
					cout << "\nYou have entered an invalid options, Please Re-enter!!" << endl;
				}
			}

			break;
		}
		else if (user.CUST_USERNAME == "Exit")		//If the user enter Exit, excecute statements below
		{
			//break;
			while (1)
			{
				menu.loginmenu(loggedin);
				while (1)
				{
					cout << "Enter your options : ";
					cin >> option;
					if (cin.fail()) {
						cout << "Invalid input. Please enter an integer." << endl;
						cin.clear();
						cin.ignore();
					}
					else {
						break;
					}
				}

				if (option == 1)
				{
					loginMenu();
					break;
				}
				else if (option == 2)
				{
					registerAccount();
					break;
				}
				else if (option == 3)
				{
					ticket.viewPromo();
					break;
				}
				else if (option == 4)
				{
					ticket.viewTicket();
					break;
				}
				else if (option == 5)
				{
					break;
					//valid = false;
				}
				else
				{
					//valid = false;
					cout << "\nYou have entered an invalid options, Please Re-enter!!" << endl;
					break;
				}
			}

		}
		else {
			loginAttempt++;
			tmpinput = "";
			cout << "\nInvalid Login" << endl;
			cout << "Please re-enter your Login Credentials OR Enter Exit to go to Non-Login Customer's menu" << endl;
			system("PAUSE");
			system("cls");
			//_getch();
		}
		if (loginAttempt > 2)	//If user attempted to login more than 3 times
		{
			while (1)
			{
				cout << "\nYou have attempted to log in for more than 3 attempts!\n(1) Forgot password?\n(2) No\nAnswer : ";
				cin >> answers;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			if (answers == 1)
			{
				cout << "Please enter your email for verification : ";
				cin >> user.CUST_EMAIL;
				if (user.forgotpass())
				{
					cout << "===============================" << endl;
					cout << "Your password is : " << user.CUST_PASSWORD << endl;
					cout << "===============================" << endl;
				}
				else
				{
					cout << "\nThere is no such email in our database!!PLease re-emter!!" << endl;
				}
			}
		}
	}
}

//Function for staff to login
void loginMenuStaff()
{
	int ans;
	Menu menu;
	AccountStaff staff;
	int option;
	Ticket ticket;
	char ch;
	string tmpinput = "";
	int loginAttempt = 0;
	int answers, answer;

	while (1) {
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+----------------------------------+" << endl;
		cout << "||=>     STAFF'S LOGIN MENU     <=||" << endl;
		cout << "+----------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;
		cout << "Enter your username : ";
		cin >> staff.USERNAME;
		cout << "Enter your password : ";
		while (true)
		{
			ch = _getch();
			if (ch == 13) // Enter key
				break;
			else if (ch == 8) // Backspace key
			{
				if (!tmpinput.empty())
				{
					tmpinput.pop_back();
					cout << "\b \b"; // Move the cursor back and erase the character
				}
			}
			else
			{
				cout << '*';
				tmpinput.push_back(ch);
			}
		}
		staff.PASSWORD = tmpinput;
		//If staff successfully logged in, excecute statements below
		if (staff.login()) {
			staffid = staff.STAFF_ID;
			loggedin = true;
			cout << endl << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "   You have been logged in to your account   " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << endl;
			system("PAUSE");
			system("cls");
			while (1)
			{
				menu.loginmenuStaff(loggedin);
				cout << endl << endl;
				while (1)
				{
					cout << "Enter your options : ";
					cin >> option;
					if (cin.fail()) {
						cout << "Invalid input. Please enter an integer." << endl;
						cin.clear();
						cin.ignore();
					}
					else {
						break;
					}
				}

				cout << endl;
				system("PAUSE");
				system("cls");
				//if staff choose the option to view their profile
				if (option == 1)
				{
					staff.viewProfileStaff();
					while (1)
					{
						cout << "\nDo you want to update any information of your profile?\n(1) Yes\n(2) No\nAnswer (Enter the digit only) : ";
						cin >> answer;
						if (cin.fail()) {
							cout << "Invalid input. Please enter an integer." << endl;
							cin.clear();
							cin.ignore();
						}
						else {
							break;
						}
					}

					if (answer == 1)
					{
						updateProfileStaff();
					}
					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 2)		//If staff choose the option to update ticket availability
				{
					if (staff.checkStaffAdmin())
					{
						updateTicket();
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You are not authorized to update any ticket availabilities!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 3)		//If staff choose the option to update promotions
				{
					if (staff.checkStaffAdmin())
					{
						updatePromo();
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You are not authorized to update any ticket availabilities!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 4)		//If staff choose the option to view sales report
				{
					if (staff.checkStaffManager())
					{
						ticket.salesReport();
					}
					else
					{
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
						cout << "You are not authorized to update any ticket availabilities!" << endl;
						cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
					}

					cout << endl;
					system("PAUSE");
					system("cls");
				}
				else if (option == 5)		//If staff choose the option to exit the system
				{
					cout << " /$$$$$$$$ /$$   /$$  /$$$$$$  /$$   /$$ /$$   /$$       /$$     /$$ /$$$$$$  /$$   /$$" << endl;
					cout << "|__  $$__/| $$  | $$ /$$__  $$| $$$ | $$| $$  /$$/      |  $$   /$$//$$__  $$| $$  | $$" << endl;
					cout << "   | $$   | $$  | $$| $$  \\ $$| $$$$| $$| $$ /$$/        \\  $$ /$$/| $$  \\ $$| $$  | $$" << endl;
					cout << "   | $$   | $$$$$$$$| $$$$$$$$| $$ $$ $$| $$$$$/          \\  $$$$/ | $$  | $$| $$  | $$" << endl;
					cout << "   | $$   | $$__  $$| $$__  $$| $$  $$$$| $$  $$           \\  $$/  | $$  | $$| $$  | $$" << endl;
					cout << "   | $$   | $$  | $$| $$  | $$| $$\\  $$$| $$\\  $$           | $$   | $$  | $$| $$  | $$" << endl;
					cout << "   | $$   | $$  | $$| $$  | $$| $$ \\  $$| $$ \\  $$          | $$   |  $$$$$$/|  $$$$$$/" << endl;
					cout << "   |__/   |__/  |__/|__/  |__/|__/  \\__/|__/  \\__/          |__/    \\______/  \\______/ " << endl;
					break;
					//valid = false;
				}
				else
				{
					//valid = false;
					cout << "\nYou have entered an invalid options, Please Re-enter!!" << endl;
					cout << endl;
					system("PAUSE");
					system("cls");
				}
			}

			break;
		}
		else {
			loginAttempt++;
			tmpinput = "";
			cout << endl << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "   Invalid Login Credentials, Please re-enter your Login Credentials   " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << endl;
			system("PAUSE");
			system("cls");
			//_getch();
		}

		//If staff attempted login more than 3 time, password will be given
		if (loginAttempt > 2)
		{
			while (1)
			{
				cout << "\nYou have attempted to log in for more than 3 attempts!\n(1) Forgot password?\n(2) No\nAnswer : ";
				cin >> answers;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			system("PAUSE");
			system("cls");
			if (answers == 1)
			{
				cout << "Please enter your Identification Number for verification : ";
				cin >> staff.IDENTIFICATION_NUMBER;
				if (staff.forgotPass())
				{
					cout << "===============================" << endl;
					cout << "Your password is : " << staff.PASSWORD << endl;
					cout << "===============================" << endl;
				}
				else
				{
					cout << "\nThere is no such email in our database!!PLease re-emter!!" << endl;
				}
			}
		}
	}
}

//Function to update Ticket's Availability, used by Admin staff
void updateTicket()
{
	Ticket ticket;
	int newavailability;
	int ans = 0;
	int cat;

	while (1)
	{
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+------------------------------------+" << endl;
		cout << "||=>     UPDATING TICKET MENU     <=||" << endl;
		cout << "+------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;
		ticket.viewTicketAvailability();
		while (1)
		{
			cout << endl << endl;
			while (1)
			{
				cout << "Please enter the ticket's category id that you want to update : ";
				cin >> cat;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			if (cat > 3000 && cat < 3006)
			{
				break;
			}
			else
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
				cout << "You have entered an invalid ticket's category id, Please re-enter!!" << endl;
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
		}

		while (1)
		{
			while (1)
			{
				cout << "Please enter the new ticket availability : ";
				cin >> newavailability;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			if (newavailability >= 0)
			{
				break;
			}
			else
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
				cout << "You have entered an invalid ticket's new availability, Please re-enter!!" << endl;
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
				cout << endl;
			}
		}

		ticket.updateTicketAvailability(cat, newavailability);
		while (1)
		{
			cout << "\nDo you want to update any other ticket availability? : ";
			cout << "\n(1) Yes\n(2) No" << endl;
			cout << "Answer : ";
			cin >> ans;
			if (cin.fail()) {
				cout << "Invalid input. Please enter an integer." << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				break;
			}
		}
		if (ans == 2)
		{
			break;
		}
	}
}

//Function to update promotions, used by staff admin
void updatePromo()
{
	Ticket ticket;
	double newpromo;
	int ans = 0;
	int cat;

	while (ans != 2)
	{
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+----------------------------------------+" << endl;
		cout << "||=>     UPDATING PROMOTIONS MENU     <=||" << endl;
		cout << "+----------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;

		ticket.viewPromo();
		while (1)
		{
			while (1)
			{
				cout << "Please enter the ticket category id that you want to update : ";
				cin >> cat;
				if (cin.fail()) {
					cout << "Invalid input. Please enter an integer." << endl;
					cin.clear();
					cin.ignore();
				}
				else {
					break;
				}
			}

			if (cat > 3000 && cat < 3006)
			{
				break;
			}
			else
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
				cout << "You have entered an invalid ticket's category id, Please re-enter!!" << endl;
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
				cout << endl;
			}
		}

		while (1)
		{
			cout << "Please enter the new ticket's promotions (in percentage %) : ";
			cin >> newpromo;
			if (newpromo >= 0)
			{
				break;
			}
			else
			{
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
				cout << "You have entered an invalid ticket's promotions, Please re-enter!!" << endl;
				cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
				cout << endl;
			}
		}
		newpromo = (100 - newpromo) / 100;
		ticket.updateTicketPromotions(cat, newpromo);
		cout << "\nDo you want to update any other ticket's promotions? : ";
		cout << "\n(1) Yes\n(2) No" << endl;
		cout << "Answer : ";
		cin >> ans;
	}
}

//Function to update customer's profile used by customers
void updateProfile()
{
	std::string phonenum, username, password, add, mail, tmpinput, tempPass;
	char ch;
	Account user;

	cout << background(White) << foreground(Magenta) << endl;
	cout << "+---------------------------------------+" << endl;
	cout << "||=>      UPDATING PROFILE MENU      <=||" << endl;
	cout << "+---------------------------------------+" << endl;
	cout << background(Black) << foreground(White) << resetANSI() << endl;

	cout << "(e.g : 000-0000000)" << endl;
	cout << "Please enter your new phone number     : ";
	cin >> user.CUST_PHONE;
	cout << endl;
	cout << "(e.g : nafies_aqasyah)" << endl;
	cout << "Please enter your new username         : ";
	cin >> user.CUST_USERNAME;
	while (1)
	{
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "+   Your password should contain :   +" << endl;
		cout << "|   (1) At least 1 number            |" << endl;
		cout << "+   (2) : At least 1 symbols         +" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "(e.g : nafies100_)" << endl;
		cout << "Enter your new password                : ";
		while (true)
		{
			ch = _getch();
			if (ch == 13) // Enter key
				break;
			else if (ch == 8) // Backspace key
			{
				if (!tmpinput.empty())
				{
					tmpinput.pop_back();
					cout << "\b \b"; // Move the cursor back and erase the character
				}
			}
			else
			{
				cout << '*';
				tmpinput.push_back(ch);
			}
		}
		//cin >> user.CUST_PASSWORD;
		if (has_number(tmpinput) == true)
		{
			if (has_symbol(tmpinput) == true)
			{
				cout << endl;
				cout << "Re-enter your password                 : ";
				while (true)
				{
					ch = _getch();
					if (ch == 13) // Enter key
						break;
					else if (ch == 8) // Backspace key
					{
						if (!tempPass.empty())
						{
							tempPass.pop_back();
							cout << "\b \b"; // Move the cursor back and erase the character
						}
					}
					else
					{
						cout << '*';
						tempPass.push_back(ch);
					}
				}
				cout << endl;
				if (tempPass == tmpinput)
				{
					user.CUST_PASSWORD = tmpinput;
					break;
				}
				else
				{
					tempPass = "";
					tmpinput = "";
					cout << "Your re-entered password are not the same!, Please re-enter!!" << endl;
				}
				//break;
			}
			else
			{
				tmpinput = "";
				cout << "Your password does not contain any symbols, Please re-enter your password!!" << endl;
				system("PAUSE");
				system("cls");
			}
		}
		else
		{
			tmpinput = "";
			cout << "Your password does not contain any number, Please re-enter your password!!" << endl;
			system("PAUSE");
			system("cls");
		}

	}
	cout << endl;
	cout << "Enter your new address                 : ";
	cin.ignore();
	std::getline(cin, user.CUST_ADDRESS);
	cout << endl;
	cout << "Enter your new email                   : ";
	cin >> user.CUST_EMAIL;

	user.update(custid);		//Update their profile into database
}

//Function to update staff's profile
void updateProfileStaff()
{
	std::string phonenum, username, password, add, mail, tmpinput, tempPass;
	char ch;
	AccountStaff staff;

	cout << background(White) << foreground(Magenta) << endl;
	cout << "+--------------------------------------+" << endl;
	cout << "||=>      UPDATING PROFILE MENU     <=||" << endl;
	cout << "+--------------------------------------+" << endl;
	cout << background(Black) << foreground(White) << resetANSI() << endl;

	cout << "Enter your new address           : ";
	cin.ignore();
	std::getline(cin, staff.ADDRESS);
	cout << endl;
	cout << "Enter your new phone number      : ";
	cin >> staff.PHONE_NUMBER;
	cout << endl;
	cout << "Enter your new username          : ";
	cin >> staff.USERNAME;
	cout << "\n(Manager / Admin / Normal)" << endl;
	cout << "Enter your staff type            : ";
	cin >> staff.STAFF_TYPE;
	while (1)
	{
		cout << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "+   Your password should contain :   +" << endl;
		cout << "|   (1) At least 1 number            |" << endl;
		cout << "+   (2) : At least 1 symbols         +" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "(e.g : nafies100_)" << endl;
		cout << "Enter your new password          : ";
		while (true)
		{
			ch = _getch();
			if (ch == 13) // Enter key
				break;
			else if (ch == 8) // Backspace key
			{
				if (!tmpinput.empty())
				{
					tmpinput.pop_back();
					cout << "\b \b"; // Move the cursor back and erase the character
				}
			}
			else
			{
				cout << '*';
				tmpinput.push_back(ch);
			}
		}
		//cin >> staff.PASSWORD;
		if (has_number(tmpinput) == true)
		{
			if (has_symbol(tmpinput) == true)
			{
				cout << endl;
				cout << "Re-enter your password           : ";
				while (true)
				{
					ch = _getch();
					if (ch == 13) // Enter key
						break;
					else if (ch == 8) // Backspace key
					{
						if (!tempPass.empty())
						{
							tempPass.pop_back();
							cout << "\b \b"; // Move the cursor back and erase the character
						}
					}
					else
					{
						cout << '*';
						tempPass.push_back(ch);
					}
				}
				cout << endl;
				if (tempPass == tmpinput)
				{
					staff.PASSWORD = tmpinput;
					break;
				}
				else
				{
					tempPass = "";
					tmpinput = "";
					cout << "Your re-entered password are not the same!, Please re-enter!!" << endl;
				}
				//break;
			}
			else
			{
				cout << "Your password does not contain any symbols, Please re-enter your password!!" << endl;
			}
		}
		else
		{
			cout << "Your password does not contain any number, Please re-enter your password!!" << endl;
		}
	}
	cout << endl;
	cout << "Enter your new email             : ";
	cin >> staff.EMAIL;

	staff.update(staffid);		//Update staff's profile into database
}

//Function for customers to book and purchase tickets
double PurchaseTicket()
{
	Ticket ticket;
	Account user;
	AccountStaff staff;
	string name;
	double totalprice = 0, price, discount;
	int id, quantity, ans, ticketquant = 0;
	int day, month, year;
	bool dateError = false;
	int count, d, m, y;
	bool available = false;
	int cat[5], cat3001, cat3002, cat3003, cat3004, cat3005, catid = 3000;

	cout << background(White) << foreground(Magenta) << endl;
	cout << "+----------------------------------------+" << endl;
	cout << "||=>     TICKET'S PURCHASING PAGE     <=||" << endl;
	cout << "+----------------------------------------+" << endl;
	cout << background(Black) << foreground(White) << resetANSI() << endl;

	cout << "Please enter your booking date :";
	//Date check
	while (!dateError)
	{
		cout << "\nEnter day\t: ";
		cin >> day;
		if (day > 0 && day < 32)
		{
			cout << "Enter month\t: ";
			cin >> month;
			if (month > 0 && month < 13)
			{
				cout << "Enter year\t: ";
				cin >> year;
				if (year > 2023)
				{
					dateError = true;
				}
				else
					cout << "\nYou have entered an invalid date, please re-enter!" << endl;
			}
			else
				cout << "\nYou have entered an invalid date, please re-enter!" << endl;
		}
		else
			cout << "\nYou have entered an invalid date, please re-enter!" << endl;
	}
	std::string date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);

	cout << endl << endl;
	ticket.viewTicket();		//Print ticket category
	cout << endl << endl;
	ticket.viewPromo();			//Print real time promotions
	cout << endl << endl;
	for (int i = 0;i < 5;i++)
	{
		catid++;
		while (1)
		{
			cout << "Enter the quantity for ticket 300" << i + 1 << " : ";
			cin >> cat[i];

			available = ticket.checkAvailability(catid);		//Check ticket's category availability
			if (available == true)
			{
				ticket.updateTicket(cat[i], catid);			//update ticket availability in database
				ticket.getPrice(catid);						//Get the category's price
				discount = ticket.getPromo(catid);
				price = ((ticket.CATEGORY_PRICE * discount) * cat[i]);		//Calculate the price for category's selected
				break;
			}
			else
			{
				cat[i] = 0;
				ticket.updateTicket(cat[i], catid);
				ticket.getPrice(catid);
				price = (ticket.CATEGORY_PRICE * cat[i]);
				cout << "\nSorry, but the ticket's categories you wanted is not available, Please choose other ticket's categories" << endl;
				break;
			}
		}
		ticketquant += cat[i];		//calculate total ticket's quantity
		totalprice += price;		//Calculate total price
	}

	catid = 3000;
	bookid = ticket.getBookingID();
	bookid++;
	ticket.purchaseTicket(date, ticketquant, custid, bookid);		//Insert values into table booking in database

	cat3001 = cat[0];
	cat3002 = cat[1];
	cat3003 = cat[2];
	cat3004 = cat[3];
	cat3005 = cat[4];

	//To insert value for each category in the database table booking_category
	for (int i = 0; i < 5;i++)
	{
		bookcatid = ticket.getBookCatID();
		bookcatid++;
		catid++;
		if (cat[i] != 0)
		{
			ticket.addBookCat(bookid, cat[i], catid, bookcatid);
		}
	}

	ticket.AMOUNT = totalprice;

	cout << "\n---------------------------------" << endl;
	cout << "|\tTotal Price : " << ticket.AMOUNT << "\t|";
	cout << "\n---------------------------------" << endl;
	hasbook = true;

	return totalprice;
}

//Function to view ticket category
void viewTicket()
{
	Ticket ticket;
	int ans;

	ticket.viewTicket();
	cout << "\nDo you want to continue with purchasing the tickets\n(1) Yes\n(2) No\nAnswer : ";
	cin >> ans;

	if (ans == 1)
	{
		PurchaseTicket();
	}
}

//Function to view real-time promotions
void viewPromo()
{
	Ticket ticket;
	int ans;

	ticket.viewPromo();
	cout << "Do you want to proceed with viewing the ticket categories?\n(1) Yes\n(2) No\nAnswer : ";
	cin >> ans;

	if (ans == 1)
	{
		viewTicket();
	}

}

//Function to make a payment used by customer
void newpayment(double totalprice)
{
	Ticket ticket;
	string cardNum;
	char choice, ch;
	int phoneNum, month, year, bankchoice, day;
	std::string password, username, pass, bank, CVV;
	bool dateError = false;
	ticket.AMOUNT = totalprice;
	int min = 4, sec = 59;

	cout << background(White) << foreground(Magenta) << endl;
	cout << "+---------------------+" << endl;
	cout << "||=>    PAYMENT    <=||" << endl;
	cout << "+---------------------+" << endl;
	cout << background(Black) << foreground(White) << resetANSI() << endl;

	cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	std::cout << "\nTotal price needed to be paid: RM" << ticket.AMOUNT << endl;
	cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;

	//Get the current date
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
	std::string strDate(buffer);

	ticket.PAYMENT_DATE = strDate;

	while (1)
	{
		cout << "+--------------------------+" << endl;
		cout << "||    Payment method      ||" << endl;
		cout << "+--------------------------+" << endl;
		cout << "||    (a) EWallet         ||" << endl;
		cout << "||    (b) Card Credit     ||" << endl;
		cout << "||    (c) Online Payment  ||" << endl;
		cout << "+--------------------------+" << endl << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		system("PAUSE");
		system("cls");

		//If user choose the option Ewallet
		if (choice == 'a')
		{
			cout << background(White) << foreground(Magenta) << endl;
			cout << "+-----------------------------+" << endl;
			cout << "||=>    EWallet Payment    <=||" << endl;
			cout << "+-----------------------------+" << endl;
			cout << background(Black) << foreground(White) << resetANSI() << endl;

			ticket.PAYMENT_METHOD = "EWallet";
			// Payment using TnG
			cout << "Phone Number   : ";
			cin >> phoneNum;
			cout << "Password       : ";
			while (true)
			{
				ch = _getch();
				if (ch == 13) // Enter key
					break;
				else if (ch == 8) // Backspace key
				{
					if (!password.empty())
					{
						password.pop_back();
						cout << "\b \b"; // Move the cursor back and erase the character
					}
				}
				else
				{
					cout << '*';
					password.push_back(ch);
				}
			}

			//Print loading bar animation
			system("COLOR FC");
			system("cls");
			printf("\n[?251");
			SetConsoleCP(437);
			SetConsoleOutputCP(437);

			int bar1 = 177, bar2 = 219;

			cout << "\n\n\n\t\t\t\tPlease wait while your payment is being verified...";
			cout << "\n\n\n\t\t\t\t";

			for (int i = 0; i < 25; i++)
				cout << (char)bar1;

			cout << "\r";
			cout << "\t\t\t\t";

			for (int i = 0; i < 25; i++)
			{
				cout << (char)bar2;
				Sleep(150);
			}

			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "  YOUR PAYMENT HAS BEEN COMPLETED!!! " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			system("PAUSE");
			system("cls");
			break;
		}
		else if (choice == 'b')		//If the user choose the option Credit Card Payment
		{
			cout << background(White) << foreground(Magenta) << endl;
			cout << "+---------------------------------+" << endl;
			cout << "||=>    Credit Card Payment    <=||" << endl;
			cout << "+---------------------------------+" << endl;
			cout << background(Black) << foreground(White) << resetANSI() << endl;

			ticket.PAYMENT_METHOD = "Card Credit";
			// Payment using debit card
			cout << "Enter your card number (16 digits only)         : ";
			cin >> cardNum;
			cout << "Enter your card expiring month (2 digits only)  : ";
			cin >> month;
			cout << "Enter your card expiring year (2 digits only)   : ";
			cin >> year;
			cout << "Enter your debit card CVV (3 digits only)       : ";
			while (true)
			{
				ch = _getch();
				if (ch == 13) // Enter key
					break;
				else if (ch == 8) // Backspace key
				{
					if (!CVV.empty())
					{
						CVV.pop_back();
						cout << "\b \b"; // Move the cursor back and erase the character
					}
				}
				else
				{
					cout << '*';
					CVV.push_back(ch);
				}
			}

			//Print loading bar animation
			system("COLOR FC");
			system("cls");
			printf("\n[?251");
			SetConsoleCP(437);
			SetConsoleOutputCP(437);

			int bar1 = 177, bar2 = 219;

			cout << "\n\n\n\t\t\t\tLoading...";
			cout << "\n\n\n\t\t\t\t";

			for (int i = 0; i < 25; i++)
				cout << (char)bar1;

			cout << "\r";
			cout << "\t\t\t\t";

			for (int i = 0; i < 25; i++)
			{
				cout << (char)bar2;
				Sleep(150);
			}

			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "  YOUR PAYMENT HAS BEEN COMPLETED!!! " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			system("PAUSE");
			system("cls");
			break;
		}
		else if (choice == 'c')		//If the user choose the option Online Banking Payment
		{
			cout << background(White) << foreground(Magenta) << endl;
			cout << "+------------------------------------+" << endl;
			cout << "||=>    Online Banking Payment    <=||" << endl;
			cout << "+------------------------------------+" << endl;
			cout << background(Black) << foreground(White) << resetANSI() << endl;

			ticket.PAYMENT_METHOD = "Online Payment";
			cout << "+-------------------------------------+" << endl;
			cout << "||=>   Please choose your bank :   <=||" << endl;
			cout << "+-------------------------------------+" << endl;
			cout << "||     (1)CIMB                       ||" << endl;
			cout << "||     (2)Maybank                    ||" << endl;
			cout << "||     (3)RHB                        ||" << endl;
			cout << "+-------------------------------------+" << endl << endl;
			cout << "Answer : ";
			cin >> bankchoice;

			if (bankchoice == 1)
			{
				bank = "CIMB CLICK";
			}
			else if (bankchoice == 2)
			{
				bank = "MAE";
			}
			else
			{
				bank = "RHB";
			}


			cout << endl;
			cout << "==============" << endl;
			cout << "[ " << bank << " ]" << endl;
			cout << "==============" << endl;
			cout << endl << endl;
			cout << "Username : ";
			cin >> username;
			cout << "Password : ";
			while (true)
			{
				ch = _getch();
				if (ch == 13) // Enter key
					break;
				else if (ch == 8) // Backspace key
				{
					if (!pass.empty())
					{
						pass.pop_back();
						cout << "\b \b"; // Move the cursor back and erase the character
					}
				}
				else
				{
					cout << '*';
					pass.push_back(ch);
				}
			}

			//Print loading bar animation
			system("COLOR FC");
			system("cls");
			printf("\n[?251");
			SetConsoleCP(437);
			SetConsoleOutputCP(437);

			int bar1 = 177, bar2 = 219;

			cout << "\n\n\n\t\t\t\tLoading...";
			cout << "\n\n\n\t\t\t\t";

			for (int i = 0; i < 25; i++)
				cout << (char)bar1;

			cout << "\r";
			cout << "\t\t\t\t";

			for (int i = 0; i < 25; i++)
			{
				cout << (char)bar2;
				Sleep(150);
			}

			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "  YOUR PAYMENT HAS BEEN COMPLETED!!! " << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			system("PAUSE");
			system("cls");
			break;
		}
		else
		{
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "You have entered an invalid option, Please re-enter!!" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		}
	}
	ticket.NewPayment(bookid);
	haspay = true;
	ticket.ticketPic();


}

//Function to delete and refund booking used by customer
void DeleteBooking()
{
	Ticket ticket;
	int ans, booking_id;
	int bankacc, confirm;

	while (1)
	{
		cout << background(White) << foreground(Magenta) << endl;
		cout << "+------------------------------------+" << endl;
		cout << "||=>     BOOKING CANCELLATION     <=||" << endl;
		cout << "+------------------------------------+" << endl;
		cout << background(Black) << foreground(White) << resetANSI() << endl;

		while (1)
		{
			cout << "Do you want to delete current booking or past booking?\n(1) current booking\n(2) past booking\nAnswer : ";
			cin >> ans;
			if (cin.fail()) {
				cout << "Invalid input. Please enter an integer." << endl;
				cin.clear();
				cin.ignore();
			}
			else {
				break;
			}
		}

		cout << endl;

		//If the user choose to delete current booking
		if (ans == 1)
		{
			while (1)
			{
				cout << "Are you sure you want to delete your booking? : \n(1) Yes\n(2)No\nAnswer : ";
				cin >> confirm;
				if (confirm == 1)
				{
					ticket.reUpdate();
					ticket.deleteBooking(haspay);
					break;
				}
				else if (confirm == 2)
				{
					break;
				}
				else
				{
					cout << endl;
					cout << "You have entered an invalid option, please re-enter!" << endl;
				}
			}

			break;
		}
		else if (ans == 2)			//If the user choose to delete past booking
		{
			ticket.viewAllBooking(custid);
			cout << endl;
			cout << "Please enter the booking id that you want to proceed with cancellation : ";
			cin >> booking_id;
			cout << endl;
			while (1)
			{
				cout << "Are you sure you want to delete your booking? : \n(1) Yes\n(2)No\nAnswer : ";
				cin >> confirm;

				if (confirm == 1)
				{
					ticket.reUpdatePast(booking_id);
					ticket.deletePastBooking(booking_id, haspay);
					break;
				}
				else if (confirm == 2)
				{
					break;
				}
				else
				{
					cout << endl;
					cout << "You have entered an invalid option, please re-enter!" << endl;
				}
			}

			break;
		}
		else
		{
			cout << "You have entered an invalid answer, Please re-enter : ";
		}
	}

	if (haspay)
	{
		cout << "Please enter your bank account number to proceed with refund : ";
		cin >> bankacc;

		std::cout << "Your refund request are in process!!" << endl;
	}

	haspay = true;
}

//Function to check if a string(password) contain any number
bool has_number(const string& str)
{
	for (char c : str) {
		if (isdigit(c)) {
			return true;
		}
	}
	return false;
}

//Function to check if a string(password) contain any symbol
bool has_symbol(const std::string& str) {
	for (char c : str) {
		if (!isalnum(c) && !isspace(c)) {
			return true;
		}
	}
	return false;
}

