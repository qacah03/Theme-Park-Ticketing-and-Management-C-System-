#include<iostream>
#include<string>

using namespace std;
#pragma once
#ifndef TICKET_H
#define TICKET_H
class Ticket
{


public:
	int CATEGORY_ID, CATEGORY_AVAILABILITY, BOOKING_ID, TOTAL_BOOKING, STAFF_ID, BOOKCAT_ID, TOTAL;
	std::string CATEGORY_NAME, BOOKING_DATE;
	double CATEGORY_PRICE, PROMOTIONS;
	std::string PAYMENT_DATE, PAYMENT_METHOD;
	double AMOUNT;

	Ticket();								//Constructor
	Ticket(int CATEGORY_ID, std::string CATEGORY_NAME, double CATEGORY_PRICE, int CATEGORY_AVAILABILITY, double PROMOTIONS);		//Overloading constructor
	void viewTicket();						//To view Ticket's Category
	void updateTicketAvailability(int cat, int newavailability);			//To update ticket's availability
	void updateTicket(int quantity, int catid);			//To update ticket's availability after a booking process
	void updateTicketPromotions(int cat, double newpromo);			//To update promotions
	void viewPromo();						//To view promotions
	void purchaseTicket(string date, int quantity, int custid, int bookid);		//To make a purchasing
	void viewTicketAvailability();			//To view ticket's availability
	void ViewTicketPurchased();				//To view Ticket's Purchased
	void getPrice(int catid);				//To get category's Price
	void NewPayment(int bookid);			//To insert values regarding payment into the database
	void deleteBooking(bool haspay);		//To delete current booking from the database
	void deletePastBooking(int bookid, bool haspay);		//To delete past booking from the database
	void addBookCat(int bookid, int quantity, int catid, int bookcatid);		//To insert values into BOOKING_CATEGORY table in the database
	void viewAllBooking(int custid);		//To view All booking from made by a customer from the database
	void BookingDetails();					//To view booking details
	void OffFK();
	void ONFK();
	bool checkAvailability(int ticketID);	//To check ticket's category availability
	int getBookingID();						//To get booking id
	int getBookCatID();						//To get bookcat id
	void getuserid();
	bool checkCategory(int cat);
	void salesReport();						//To generate and view sales report
	double getPromo(int catid);				//To get promtions discount value
	void reUpdate();						//To re update the ticket availability after a booking cancellation process
	void reUpdatePast(int bookid);					//To re update the ticket availability after a booking cancellation process
	string ticketImage();
	void ticketPic();
	string getPaymentID(int bookid);
	~Ticket();								//Destructor
};
#endif
