#pragma once
#ifndef MENU_H
#define MENU_H

#include<iostream>
#include <string>
#include <vector>
#include <utility>

class Menu
{
public:
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
	
	Menu();				//Constructor
	
	~Menu();			//Destructor
	void loginmenu(bool loggedin);			//To print menus for customer
	void loginmenuStaff(bool loggedin);		//To print menus for staff
	
private:
	int options;
};


#endif

