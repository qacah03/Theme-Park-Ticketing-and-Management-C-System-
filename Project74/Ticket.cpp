#include "Ticket.h"
#include"Account.h"
#include "DBConnection.h" 
#include<iostream>
#include <ctime>
#include<cstdlib>
#include<random>
#include<iomanip>
#include <SFML/Graphics.hpp>

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

//Constructor to initialize certain variable
Ticket::Ticket()
{
    CATEGORY_ID = 0;
    CATEGORY_NAME = "";
    CATEGORY_PRICE = 0.00;
    CATEGORY_AVAILABILITY = 0;
    PROMOTIONS = 0.00;
    AMOUNT = 0.00;
}

//Overloading constructor
Ticket::Ticket(int CATEGORY_ID, std::string CATEGORY_NAME, double CATEGORY_PRICE, int CATEGORY_AVAILABILITY, double PROMOTIONS)
{
    this->CATEGORY_ID = CATEGORY_ID;
    this->CATEGORY_NAME = CATEGORY_NAME;
    this->CATEGORY_PRICE = CATEGORY_PRICE;
    this->CATEGORY_AVAILABILITY = CATEGORY_AVAILABILITY;
    this->PROMOTIONS = PROMOTIONS;
}

//Destructor
Ticket::~Ticket()
{}

//Function to view Ticket's Category
void Ticket::viewTicket()
{
    cout << bgWhite;
    cout << MAGENTA;
    cout << "+----------------------------------+" << endl;
    cout << "||=>     TICKETS AND PRICES     <=||" << endl;
    cout << "+----------------------------------+" << endl;
    cout << bgBlack;
    cout << WHITE;
    cout << RESET << endl;
    cout << "\n\t------------------------------------------------" << endl;
    cout << "\t|\t   CATEGORY TICKET   \t|\tPRICE\t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t| CATEGORY 3001:                |\t \t| " << endl;
    cout << "\t| 1 Baby                     \t|\tRM0\t| " << endl;
    cout << "\t| [0-4 YEARS OLD]            \t|\t \t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t| CATEGORY 3002:                |\t \t| " << endl;
    cout << "\t| 1 CHILD                    \t|\tRM50\t| " << endl;
    cout << "\t| [5-11 YEARS OLD]           \t|\t \t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t| CATEGORY 3003:                |\t \t| " << endl;
    cout << "\t| 1 ADULT                    \t|\tRM80\t| " << endl;
    cout << "\t| [12-59 YEARS OLD]          \t|\t \t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t| CATEGORY 3004:                |\t \t| " << endl;
    cout << "\t| 1 SENIOR                   \t|\tRM40\t| " << endl;
    cout << "\t| [60 - 99 YEARS OLD]        \t|\t \t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\t| CATEGORY 3005:                |\t \t| " << endl;
    cout << "\t| COMBO!                     \t|\tRM315\t| " << endl;
    cout << "\t| 2 ADULTS 3 CHILDS 1SENIORS \t|\t \t| " << endl;
    cout << "\t| SAVE UP 10%                \t|\t \t| " << endl;
    cout << "\t------------------------------------------------" << endl;
    cout << "\n\t DISCOUNT OFFER AS LOW AS 15% DISCOUNT " << endl;

}

//Function to update ticket availability
void Ticket::updateTicketAvailability(int cat, int newavailability)
{
    DBConnection db;

    CATEGORY_ID = cat;
    CATEGORY_AVAILABILITY = newavailability;
    db.prepareStatement("UPDATE CATEGORY SET CATEGORY_AVAILABILITY=? WHERE CATEGORY_ID =? ");
    db.stmt->setInt(1, CATEGORY_AVAILABILITY);
    db.stmt->setInt(2, CATEGORY_ID);
    db.QueryStatement();
    db.~DBConnection();
}

//Function to update promotion in the database
void Ticket::updateTicketPromotions(int cat, double newpromo)
{
    DBConnection db;

    CATEGORY_ID = cat;
    PROMOTIONS = newpromo;
    db.prepareStatement("UPDATE CATEGORY SET PROMOTIONS=? WHERE CATEGORY_ID =? ");
    db.stmt->setDouble(1, PROMOTIONS);
    db.stmt->setInt(2, CATEGORY_ID);
    db.QueryStatement();
    db.~DBConnection();
}

//To view promo from the database
void Ticket::viewPromo()
{
    DBConnection db;
    double discount;

    cout << bgWhite;
    cout << MAGENTA;
    cout << "+--------------------------+" << endl;
    cout << "||=>     PROMOTIONS     <=||" << endl;
    cout << "+--------------------------+" << endl;
    cout << bgBlack;
    cout << WHITE;
    cout << RESET << endl;
    db.prepareStatement("SELECT CATEGORY_ID,CATEGORY_NAME,PROMOTIONS FROM CATEGORY WHERE PROMOTIONS IS NOT NULL");
    db.QueryResult();
    cout << "-------------------------------------------------" << endl;
    cout << "|  CATEGORY ID  | CATEGORY NAME |    DISCOUNT   |" << endl;
    while (db.res->next()) {
        std::cout << "-------------------------------------------------" << endl;
        std::cout << "|\t" << db.res->getInt("CATEGORY_ID") << "\t|\t" << db.res->getString("CATEGORY_NAME") << "\t|\t";
        discount = 100 - ((db.res->getDouble("PROMOTIONS")) * 100);
        std::cout << discount << "%\t|" << std::endl;
    }
    cout << "-------------------------------------------------" << endl;

    db.~DBConnection();
}

//To insert values of ticket's booking into database
void Ticket::purchaseTicket(string date, int quantity, int custid, int bookid)
{
    BOOKING_DATE = date;
    TOTAL_BOOKING = quantity;
    BOOKING_ID = bookid;
    int staffid;
    int randomData;
    int userid;
    DBConnection db;

    db.prepareStatement("SELECT STAFF_ID FROM STAFF WHERE STAFF_TYPE!='Admin' AND STAFF_TYPE!='Manager' ORDER BY RAND() LIMIT 1;");
    db.QueryResult();
    while (db.res->next())
    {
        staffid = db.res->getInt("STAFF_ID");
    }

    db.prepareStatement("INSERT INTO `BOOKING`(`BOOKING_ID`, `BOOKING_DATE`, `TOTAL_BOOKING`, `STAFF_ID`, `CUST_ID`) VALUES(?,?,?,?,?)");
    db.stmt->setInt(1, BOOKING_ID);
    db.stmt->setString(2, BOOKING_DATE);
    db.stmt->setInt(3, TOTAL_BOOKING);
    db.stmt->setInt(4, staffid);
    db.stmt->setInt(5, custid);
    db.QueryStatement();
    db.~DBConnection();
}

//To insert values into Booking_Category table in the database
void Ticket::addBookCat(int bookid, int quantity, int catid, int bookcatid)
{
    DBConnection db;

    BOOKCAT_ID = bookcatid;
    BOOKING_ID = bookid;
    TOTAL = quantity;
    CATEGORY_ID = catid;
    db.prepareStatement("INSERT INTO BOOKING_CATEGORY (BOOKCAT_ID,BOOKING_ID,CATEGORY_ID,TOTAL) VALUES (?,?,?,?)");
    db.stmt->setInt(1, BOOKCAT_ID);
    db.stmt->setInt(2, BOOKING_ID);
    db.stmt->setInt(3, CATEGORY_ID);
    db.stmt->setInt(4, TOTAL);
    db.QueryStatement();
    db.~DBConnection();
}

//To view ticket's availability
void Ticket::viewTicketAvailability()
{
    DBConnection db;

    std::cout << "-------------------------------------------------------------------------" << endl;
    cout << "|\tCATEGORY ID\t|\tCATEGORY NAME\t|\tAVAILABILITY\t|" << endl;
    std::cout << "-------------------------------------------------------------------------" << endl;

    db.prepareStatement("SELECT CATEGORY_ID,CATEGORY_NAME,CATEGORY_AVAILABILITY FROM CATEGORY");
    db.QueryResult();
    while (db.res->next()) {

        cout << "|\t" << db.res->getInt("CATEGORY_ID") << "\t";
        std::cout << "\t|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t";
        std::cout << db.res->getInt("CATEGORY_AVAILABILITY") << "\t\t|" << std::endl;
        std::cout << "-------------------------------------------------------------------------" << endl;
    }

    db.~DBConnection();
}

//To update ticket's availabilty after a booking process
void Ticket::updateTicket(int quantity, int catid)
{
    int quant;
    int newquant;
    CATEGORY_ID = catid;
    DBConnection db;
    db.prepareStatement("SELECT CATEGORY_AVAILABILITY FROM CATEGORY WHERE CATEGORY_ID = ?");
    db.stmt->setInt(1, CATEGORY_ID);
    db.QueryResult();
    if (db.res->rowsCount() == 1) {
        while (db.res->next()) {
            quant = db.res->getInt("CATEGORY_AVAILABILITY");
        }

    }

    newquant = quant - quantity;

    CATEGORY_AVAILABILITY = newquant;
    db.prepareStatement("UPDATE CATEGORY SET CATEGORY_AVAILABILITY=? WHERE CATEGORY_ID =?");
    db.stmt->setDouble(1, CATEGORY_AVAILABILITY);
    db.stmt->setInt(2, CATEGORY_ID);
    db.QueryStatement();
    db.~DBConnection();
}

//To get price of a ticket'category
void Ticket::getPrice(int catid)
{
    DBConnection db;

    CATEGORY_ID = catid;
    db.prepareStatement("SELECT CATEGORY_PRICE FROM CATEGORY WHERE CATEGORY_ID = ?");
    db.stmt->setInt(1, CATEGORY_ID);
    db.QueryResult();
    if (db.res->rowsCount() == 1) {
        while (db.res->next()) {
            CATEGORY_PRICE = db.res->getDouble("CATEGORY_PRICE");
        }

    }
}

//To view ticket's purchased 
void Ticket::ViewTicketPurchased()
{
    DBConnection db;

    cout << bgWhite;
    cout << MAGENTA;
    cout << "+----------------------------------+" << endl;
    cout << "||=>     TICKET'S PURCHASED     <=||" << endl;
    cout << "+----------------------------------+" << endl;
    cout << bgBlack;
    cout << WHITE;
    cout << RESET << endl;
    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();
    while (db.res->next()) {
        BOOKING_ID = db.res->getInt("lastid");
    }

    cout << "-----------------------------------------" << endl;
    cout << "|\tCATEGORY NAME\t|\tTOTAL\t|" << endl;
    db.prepareStatement("SELECT C.CATEGORY_NAME, BC.TOTAL FROM BOOKING B JOIN BOOKING_CATEGORY BC ON B.BOOKING_ID = BC.BOOKING_ID JOIN CATEGORY C ON BC.CATEGORY_ID = C.CATEGORY_ID WHERE B.BOOKING_ID = ? GROUP BY C.CATEGORY_NAME;");
    db.stmt->setInt(1, BOOKING_ID);
    db.QueryResult();
    while (db.res->next()) {
        cout << "-----------------------------------------" << endl;
        cout << "|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t" << db.res->getInt("TOTAL") << "\t|" << endl;
    }

    cout << "-----------------------------------------" << endl;

    db.~DBConnection();
}

//To insert values into Payment table in the database
void Ticket::NewPayment(int bookid)
{
    DBConnection db;

    BOOKING_ID = bookid;
    db.prepareStatement("INSERT INTO PAYMENT (AMOUNT,PAYMENT_DATE,PAYMENT_METHOD,BOOKING_ID) VALUES (?,?,?,?)");
    db.stmt->setDouble(1, AMOUNT);
    db.stmt->setString(2, PAYMENT_DATE);
    db.stmt->setString(3, PAYMENT_METHOD);
    db.stmt->setInt(4, BOOKING_ID);
    db.QueryStatement();
    db.~DBConnection();
}

//To delete certain row from database related to booking
void Ticket::deleteBooking(bool haspay)
{
    DBConnection db;
    Account user;

    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();
    while (db.res->next()) {
        BOOKING_ID = db.res->getInt("lastid");
    }

    if (haspay)
    {
        db.prepareStatement("DELETE FROM PAYMENT WHERE BOOKING_ID = ?");
        db.stmt->setInt(1, BOOKING_ID);
        db.QueryStatement();
    }

    db.prepareStatement("DELETE FROM BOOKING_CATEGORY WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, BOOKING_ID);
    db.QueryStatement();
    //db.~DBConnection();

    db.prepareStatement("DELETE FROM BOOKING WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, BOOKING_ID);
    db.QueryStatement();
    db.~DBConnection();

}

//To delete past booking
void Ticket::deletePastBooking(int book_id, bool haspay)
{
    DBConnection db;

    if (haspay)
    {
        db.prepareStatement("DELETE FROM PAYMENT WHERE BOOKING_ID = ?");
        db.stmt->setInt(1, book_id);
        db.QueryStatement();
    }

    db.prepareStatement("DELETE FROM BOOKING_CATEGORY WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, book_id);
    db.QueryStatement();
    db.~DBConnection();

    db.prepareStatement("DELETE FROM BOOKING WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, book_id);
    db.QueryStatement();
    db.~DBConnection();


}

//To view all booking that have been made by a customers including past booking
void Ticket::viewAllBooking(int custid)
{
    DBConnection db;

    cout << bgWhite;
    cout << MAGENTA;
    cout << "+---------------------------------+" << endl;
    cout << "||=>      BOOKING HISTORY      <=||" << endl;
    cout << "+---------------------------------+" << endl;
    cout << bgBlack;
    cout << WHITE;
    cout << RESET << endl;
    cout << endl;

    cout << "-------------------------------------------------------------------------" << endl;
    cout << "|\tBOOKING ID\t|\tBOOKING DATE\t|\tTOTAL TICKETS\t|" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    db.prepareStatement("SELECT BOOKING_ID, BOOKING_DATE, TOTAL_BOOKING FROM BOOKING WHERE CUST_ID = ?");
    db.stmt->setInt(1, custid);
    db.QueryResult();
    while (db.res->next()) {
        cout << "|\t" << db.res->getInt("BOOKING_ID") << "\t\t|\t" << db.res->getString("BOOKING_DATE") << "\t|\t" << db.res->getInt("TOTAL_BOOKING") << "\t\t|" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
    }
}

//To view booking details made by a customer
void Ticket::BookingDetails()
{
    DBConnection db;

    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();
    while (db.res->next()) {
        BOOKING_ID = db.res->getInt("lastid");
    }
    cout << bgWhite;
    cout << MAGENTA;
    cout << "+---------------------------------+" << endl;
    cout << "||=>      BOOKING DETAILS      <=||" << endl;
    cout << "+---------------------------------+" << endl;
    cout << bgBlack;
    cout << WHITE;
    cout << RESET << endl;

    cout << "\n--------------------------------------------------------------------------------------------------------" << endl;
    cout << "|\tCATEGORY NAME\t|\tBOOKING DATE\t|\tTOTAL BOOKING\t\t|\tCUSTOMER_NAME\t|" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    db.prepareStatement("SELECT C.CATEGORY_NAME, B.BOOKING_DATE, BC.TOTAL, CU.CUST_NAME FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID JOIN CUSTOMER CU ON B.CUST_ID = CU.CUST_ID WHERE B.BOOKING_ID = ?");
    db.stmt->setInt(1, BOOKING_ID);
    db.QueryResult();
    while (db.res->next()) {
        cout << "|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t" << db.res->getString("BOOKING_DATE") << "\t|\t" << db.res->getInt("TOTAL") << "\t\t\t|\t" << db.res->getString("CUST_NAME") << "\t|" << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
    }
}

void Ticket::OffFK()
{
    DBConnection db;

    db.prepareStatement("SET GLOBAL FOREIGN_KEY_CHECKS=0;");
    db.QueryStatement();
}

void Ticket::ONFK()
{
    DBConnection db;

    db.prepareStatement("SET GLOBAL FOREIGN_KEY_CHECKS=1;");
    db.QueryStatement();
}

//To check availability of a ticket's category
bool Ticket::checkAvailability(int ticketID)
{
    DBConnection db;

    db.prepareStatement("SELECT CATEGORY_AVAILABILITY FROM CATEGORY WHERE CATEGORY_ID = ?");
    db.stmt->setInt(1, ticketID);
    db.QueryResult();
    if (db.res->rowsCount() == 1) {
        while (db.res->next()) {
            CATEGORY_AVAILABILITY = db.res->getDouble("CATEGORY_AVAILABILITY");
        }
    }

    if (CATEGORY_AVAILABILITY > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//To get booking id from the database
int Ticket::getBookingID()
{
    DBConnection db;

    int bookid;

    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();
    while (db.res->next()) {
        bookid = db.res->getInt("lastid");
    }

    return bookid;
}

//To get Booking_CategoryID from database
int Ticket::getBookCatID()
{
    DBConnection db;

    int bookcatid;

    db.prepareStatement("SELECT MAX(BOOKCAT_ID) AS lastid FROM BOOKING_CATEGORY");
    db.QueryResult();
    while (db.res->next()) {
        bookcatid = db.res->getInt("lastid");
    }

    return bookcatid;
}


bool Ticket::checkCategory(int cat)
{
    DBConnection db;
    int catid;

    db.prepareStatement("SELECT CATEGORY_ID FROM CATEGORY WHERE CATEGORY_ID = ?");
    db.QueryResult();
    while (db.res->next())
    {
        catid = db.res->getInt("CATEGORY_ID");
    }
}

//To get promotions discount from database
double Ticket::getPromo(int catid)
{
    DBConnection db;
    double nopromo = 1;

    db.prepareStatement("SELECT PROMOTIONS FROM CATEGORY WHERE CATEGORY_ID = ?");
    db.stmt->setInt(1, catid);
    db.QueryResult();

    while (db.res->next()) {
        PROMOTIONS = db.res->getDouble("PROMOTIONS");
    }
    db.~DBConnection();
    return PROMOTIONS;


}

//To view salesReport (only available for manager)
//To view salesReport (only available for manager)
void Ticket::salesReport()
{
    DBConnection db;
    int tempCat[5], tempCatAvailability[5], oriCat = 300, i = 0, salesAvailability[5], staffid, k = 1, choice;
    string tempName[5], staffType, tempMName[5], maxMonth;
    double maxSales, total = 0, totalMonth = 0, totalMonthly = 0, totalMonthlys, tMonth[12], maximum = 0;
    int max = 0, maxCat, ans, month, tempMSales[5], size = 0, opt, j = 1, answ;
    string monthStart, monthEnd, mon, m;
    double Tewallet = 0, Tonline = 0, Tcard = 0, totalPay = 0, average, tSale = 0;
    double percentEwallet, percentOnline, percentCard, maxpay, percentMax;
    string MaxPayment;

    while (1)
    {
        cout << "Please enter your staff id : ";
        cin >> staffid;
        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore();
        }
        else {
            break;
        }
    }

    //To get the staff Type
    db.prepareStatement("SELECT STAFF_TYPE FROM STAFF WHERE STAFF_ID = ?");
    db.stmt->setInt(1, staffid);
    db.QueryResult();
    if (db.res->rowsCount() == 1) {
        while (db.res->next()) {
            staffType = db.res->getString("STAFF_TYPE");
        }
    }

    system("PAUSE");
    system("cls");

    //If the staff is a manager, then excecute statements below
    if (staffType == "Manager")
    {
        cout << bgWhite;
        cout << MAGENTA;
        cout << "+------------------------------+" << endl;
        cout << "=>        SALES REPORT        <=" << endl;
        cout << "+------------------------------+" << endl;
        cout << bgBlack;
        cout << WHITE;
        cout << RESET << endl;

        //get the category id, category name and category availability from the database
        db.prepareStatement("SELECT CATEGORY_ID, CATEGORY_NAME, CATEGORY_AVAILABILITY FROM CATEGORY");
        db.QueryResult();
        while (db.res->next())
        {
            tempCat[i] = db.res->getInt("CATEGORY_ID");
            tempName[i] = db.res->getString("CATEGORY_NAME");
            tempCatAvailability[i] = db.res->getInt("CATEGORY_AVAILABILITY");
            i++;
        }

        //Calculate the sales of ticket stocks
        for (int i = 0; i < 5;i++)
        {
            salesAvailability[i] = oriCat - tempCatAvailability[i];
        }

        for (int i = 0; i < 5; ++i) {
            if (salesAvailability[i] > max) {
                max = salesAvailability[i];
            }
        }

        // Determine the scale factor to normalize the bars
        double scaleFactor = 1.0;
        if (max > 50) {
            scaleFactor = 50.0 / max;
        }
        cout << endl;
        cout << "    BAR CHART   " << endl;
        cout << "+--------------+" << endl << endl;
        // Draw the bar chart
        for (int i = 0; i < 5; ++i) {
            // Calculate the normalized bar height
            int barHeight = static_cast<int>(salesAvailability[i] * scaleFactor);

            // Draw the bar with an asterisk for every 10 units
            std::cout << tempName[i] << "\t: ";
            for (int j = 0; j < barHeight; ++j) {
                if (j % 10 == 0) {
                    std::cout << "*";
                }

            }
            std::cout << std::endl;
        }
        cout << endl;

        cout << "-----------------------------------" << endl;
        cout << "|   one '*' represents ten unit!  |" << endl;
        cout << "-----------------------------------" << endl;

        cout << bgWhite;
        cout << MAGENTA;
        cout << "+-------------------------------------------+" << endl;
        cout << "=>         TICKET'S CATEGORY SALES         <=" << endl;
        cout << "+-------------------------------------------+" << endl;
        cout << bgBlack;
        cout << WHITE;
        cout << RESET << endl;
        cout << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "\tCATEGORY NAME\t|\tCATEGORY'S STOCK SOLD\t|\tCATEGORY SALES\t|" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;

        //To get and print the sales of each category
        db.prepareStatement("SELECT CATEGORY_NAME, 300 - CATEGORY_AVAILABILITY AS SALES, (300-CATEGORY_AVAILABILITY)*CATEGORY_PRICE AS TOTAL_SALES FROM CATEGORY GROUP BY CATEGORY_NAME;");
        db.QueryResult();
        while (db.res->next())
        {
            cout << "|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t\t" << db.res->getInt("SALES") << "\t\t|\tRM " << db.res->getInt("TOTAL_SALES") << "\t\t|" << endl;
            cout << "---------------------------------------------------------------------------------" << endl;
            total += db.res->getInt("TOTAL_SALES");
        }
        cout << "--------------------------------------" << endl;
        cout << "|    TOTAL SALES     |    RM" << total << "    |" << endl;
        cout << "--------------------------------------" << endl;
        cout << endl;

        cout << "Do you want to view monthly sales Report?\n(1)Yes\n(2)No\nAnswer : ";
        cin >> ans;
        cout << endl << endl;
        system("PAUSE");
        system("cls");

        //If the user wants to view monthly sales report
        if (ans == 1)
        {
            cout << bgWhite;
            cout << MAGENTA;
            cout << "+-------------------------------+" << endl;
            cout << "=>        MONTHLY SALES        <=" << endl;
            cout << "+-------------------------------+" << endl;
            cout << bgBlack;
            cout << WHITE;
            cout << RESET << endl;
            cout << "Please enter the month that you want to view : ";
            cin >> month;
            if (month == 1)
            {
                mon = "JANUARY";
                monthStart = "2024-01-01";
                monthEnd = "2024-01-31";
            }
            else if (month == 2)
            {
                mon = "FEBRUARY";
                monthStart = "2024-02-01";
                monthEnd = "2024-02-29";
            }
            else if (month == 3)
            {
                mon = "MARCH";
                monthStart = "2024-03-01";
                monthEnd = "2024-03-31";
            }
            else if (month == 4)
            {
                mon = "APRIL";
                monthStart = "2024-04-01";
                monthEnd = "2024-04-30";
            }
            else if (month == 5)
            {
                mon = "MAY";
                monthStart = "2024-05-01";
                monthEnd = "2024-05-31";
            }
            else if (month == 6)
            {
                mon = "JUNE";
                monthStart = "2024-06-01";
                monthEnd = "2024-06-30";
            }
            else if (month == 7)
            {
                mon = "JULY";
                monthStart = "2024-07-01";
                monthEnd = "2024-07-31";
            }
            else if (month == 8)
            {
                mon = "AUGUST";
                monthStart = "2024-08-01";
                monthEnd = "2024-08-31";
            }
            else if (month == 9)
            {
                mon = "SEPTEMBER";
                monthStart = "2024-09-01";
                monthEnd = "2024-09-30";
            }
            else if (month == 10)
            {
                mon = "OCTOBER";
                monthStart = "2024-10-01";
                monthEnd = "2024-10-31";
            }
            else if (month == 11)
            {
                mon = "NOVEMBER";
                monthStart = "2024-11-01";
                monthEnd = "2024-11-30";
            }
            else
            {
                mon = "DECEMBER";
                monthStart = "2024-12-01";
                monthEnd = "2024-12-31";
            }
            cout << endl << endl << endl;

            //To get and print out the sales of a month selected by the user
            cout << "            SALES BY CATEGORY IN " << mon << endl;
            cout << "+-------------------------------------------------------+" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "|\tCATEGORY NAME\t|\tCATEGORY'S TOTAL SALES\t|" << endl;
            cout << "---------------------------------------------------------" << endl;
            db.prepareStatement("SELECT C.CATEGORY_NAME, SUM(BC.TOTAL)*C.CATEGORY_PRICE AS TOTAL_SALES FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID WHERE MONTH(B.BOOKING_DATE)=? GROUP BY C.CATEGORY_NAME;");
            db.stmt->setInt(1, month);
            db.QueryResult();
            while (db.res->next()) {
                cout << "|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t\tRM " << db.res->getInt("TOTAL_SALES") << "\t\t|" << endl;
                cout << "---------------------------------------------------------" << endl;
                totalMonth += db.res->getInt("TOTAL_SALES");
            }
            cout << "--------------------------------------" << endl;
            cout << "|    TOTAL SALES     |    RM" << totalMonth << "    |" << endl;
            cout << "--------------------------------------" << endl;
            cout << endl;

            totalMonth = 0;

            i = 0;

            //To get the category name and total sales and print out in the form of bar chart
            db.prepareStatement("SELECT C.CATEGORY_NAME, SUM(BC.TOTAL) AS TOTAL_SALES FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID WHERE MONTH(B.BOOKING_DATE)=? GROUP BY C.CATEGORY_NAME;");
            db.stmt->setInt(1, month);
            db.QueryResult();
            while (db.res->next()) {
                tempMName[i] = db.res->getString("CATEGORY_NAME");
                tempMSales[i] = db.res->getInt("TOTAL_SALES");
                i++;
            }
            size = i;

            max = 0;

            for (int i = 0; i < 5; ++i) {
                if (tempMSales[i] > max) {
                    max = tempMSales[i];
                }
            }

            // Determine the scale factor to normalize the bars
            double scaleFactor = 1.0;
            if (max > 50) {
                scaleFactor = 50.0 / max;
            }

            cout << endl << endl;
            cout << "    BAR CHART   " << endl;
            cout << "+--------------+" << endl << endl;
            // Draw the bar chart
            for (int i = 0; i < size; ++i) {
                // Calculate the normalized bar height
                int barHeight = static_cast<int>(tempMSales[i] * scaleFactor);

                // Draw the bar with an asterisk for every 10 units
                std::cout << tempMName[i] << "\t: ";
                for (int j = 0; j < barHeight; ++j) {

                    std::cout << "*";


                }
                std::cout << std::endl;
            }
            cout << endl;
            cout << "-----------------------------------" << endl;
            cout << "|   one '*' represents one unit!  |" << endl;
            cout << "-----------------------------------" << endl;
        }

        cout << endl;

        cout << "Do you want to see each of the monthly sales between each months?\n(1) Yes\n(2) No\nAnswer : ";
        cin >> opt;

        system("PAUSE");
        system("cls");

        //If the user wants to see comparison of monthly sales of each months
        if (opt == 1)
        {
            cout << bgWhite;
            cout << MAGENTA;
            cout << "+-------------------------------------------+" << endl;
            cout << "=>        SALES COMPARISON BY MONTH        <=" << endl;
            cout << "+-------------------------------------------+" << endl;
            cout << bgBlack;
            cout << WHITE;
            cout << RESET << endl;

            while (j <= 12)
            {
                if (j == 1)

                {
                    m = "JANUARY";
                }
                else if (j == 2)
                {
                    m = "FEBRUARY";
                }
                else if (j == 3)
                {
                    m = "MARCH";
                }
                else if (j == 4)
                {
                    m = "APRIL";
                }
                else if (j == 5)
                {
                    m = "MAY";
                }
                else if (j == 6)
                {
                    m = "JUNE";
                }
                else if (j == 7)
                {
                    m = "JULY";
                }
                else if (j == 8)
                {
                    m = "AUGUST";
                }
                else if (j == 9)
                {
                    m = "SEPTEMBER";
                }
                else if (j == 10)
                {
                    m = "OCTOBER";
                }
                else if (j == 11)
                {
                    m = "NOVEMBER";
                }
                else
                {
                    m = "DECEMBER";
                }


                //To get and print the monthly sales of each month
                cout << "    SALES IN " << m << endl;
                cout << "+----------------------+" << endl;
                cout << "---------------------------------------------------------" << endl;
                db.prepareStatement("SELECT C.CATEGORY_NAME, SUM(BC.TOTAL)*C.CATEGORY_PRICE AS TOTAL_SALES FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID WHERE MONTH(B.BOOKING_DATE)=? GROUP BY C.CATEGORY_NAME;");
                db.stmt->setInt(1, j);
                db.QueryResult();
                while (db.res->next()) {
                    cout << "|\t" << db.res->getString("CATEGORY_NAME") << "\t\t|\t\tRM " << db.res->getInt("TOTAL_SALES") << "\t\t|" << endl;
                    cout << "---------------------------------------------------------" << endl;
                    totalMonthly += db.res->getInt("TOTAL_SALES");
                }

                cout << "--------------------------------------" << endl;
                cout << "|    TOTAL SALES     |    RM" << totalMonthly << "    |" << endl;
                cout << "--------------------------------------" << endl;
                cout << endl;
                totalMonthly = 0;
                j++;
                cout << endl << endl;
            }
        }
        cout << "Do you want to see comparison of total sales of each month?\n(1) Yes\n(2) No\nAnswer : ";
        cin >> choice;
        system("PAUSE");
        system("cls");
        if (choice == 1)
        {
            cout << bgWhite;
            cout << MAGENTA;
            cout << "+-------------------------------------------+" << endl;
            cout << "=>        SALES COMPARISON BY MONTH        <=" << endl;
            cout << "+-------------------------------------------+" << endl;
            cout << bgBlack;
            cout << WHITE;
            cout << RESET << endl;

            while (k <= 12)
            {
                if (k == 1)

                {
                    m = "JANUARY";
                }
                else if (k == 2)
                {
                    m = "FEBRUARY";
                }
                else if (k == 3)
                {
                    m = "MARCH";
                }
                else if (k == 4)
                {
                    m = "APRIL";
                }
                else if (k == 5)
                {
                    m = "MAY";
                }
                else if (k == 6)
                {
                    m = "JUNE";
                }
                else if (k == 7)
                {
                    m = "JULY";
                }
                else if (k == 8)
                {
                    m = "AUGUST";
                }
                else if (k == 9)
                {
                    m = "SEPTEMBER";
                }
                else if (k == 10)
                {
                    m = "OCTOBER";
                }
                else if (k == 11)
                {
                    m = "NOVEMBER";
                }
                else
                {
                    m = "DECEMBER";
                }

                //To get and print the monthly sales of each month
                cout << "    TOTAL SALES IN " << m << endl;
                cout << "+----------------------------+" << endl;
                db.prepareStatement("SELECT SUM(BC.TOTAL)*C.CATEGORY_PRICE AS TOTAL_SALES FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID WHERE MONTH(B.BOOKING_DATE)=? GROUP BY C.CATEGORY_NAME;");
                db.stmt->setInt(1, k);
                db.QueryResult();
                while (db.res->next()) {
                    totalMonthlys += db.res->getInt("TOTAL_SALES");
                }

                cout << "--------------------------------------" << endl;
                cout << "|    TOTAL SALES     |    RM" << totalMonthlys << "    |" << endl;
                cout << "--------------------------------------" << endl;
                cout << endl;
                tMonth[k] = totalMonthlys;

                //Comparing each months in percentage
                if (k > 1 && totalMonthlys != 0)
                {
                    if ((tMonth[k] - tMonth[k - 1]) > 0)
                    {
                        double SalesPercent = ((tMonth[k] - tMonth[k - 1]) / tMonth[k - 1]) * 100;
                        cout << "      Total Sales Comparison      " << endl;
                        cout << "----------------------------------" << endl;
                        cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                        cout << "The total sales in " << m << " increases with a percentage of " << SalesPercent << "% compared to the month before" << endl;
                        cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                        SalesPercent = 0.00;
                    }
                    else
                    {
                        int SalesPercent = ((tMonth[k - 1] - tMonth[k]) / tMonth[k]) * 100;
                        cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                        cout << "The total sales in " << m << " decreases with a percentage of " << SalesPercent << "% compared to the month before" << endl;
                        cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                        SalesPercent = 0.00;
                    }
                }
                if (tMonth[k] > maximum)
                {
                    maximum = tMonth[k];
                    maxMonth = m;
                }
                tSale += tMonth[k];
                k++;
                totalMonthlys = 0;


                cout << endl << endl;
            }

            cout << "+----------------------------------------------+" << endl;
            cout << "=>        OVERALL MONTHLY SALES REPORT        <=" << endl;
            cout << "+----------------------------------------------+" << endl;

            cout << endl;
            average = tSale / 12;
            if (maximum > average)
            {
                percentMax = ((maximum - average) / average) * 100;
                cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                cout << "Average Sales : RM" << average << endl;
                cout << "Highest Total Sales : RM" << maximum << " which is in : " << maxMonth << endl;
                cout << "The maximum sales is higher by " << percentMax << "% than the average sales" << endl;
                cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
            }
            else
            {
                percentMax = ((average - maximum) / maximum) * 100;
                cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
                cout << "Average Sales       : RM" << average << endl;
                cout << "Highest Total Sales : RM" << maximum << " which is in " << maxMonth << endl;
                cout << "The maximum sales is lower by " << percentMax << "% than the average sales" << endl;
                cout << "==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==--==" << endl;
            }

        }

        cout << endl << endl;
        cout << "Do you want to see list of payment methods used by customer?\n(1) Yes\n(2) No\nAnswer : ";
        cin >> answ;
        system("PAUSE");
        system("cls");

        //If the user wants to see the payment methods used by each of the customer to analyze which payment method is the best
        if (answ == 1)
        {
            cout << bgWhite;
            cout << MAGENTA;
            cout << "+--------------------------------------+" << endl;
            cout << "=>        PAYMENT METHODS USED        <=" << endl;
            cout << "+--------------------------------------+" << endl;
            cout << bgBlack;
            cout << WHITE;
            cout << RESET << endl;
            cout << "         EWallet         " << endl;
            cout << "+-----------------------+" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "\tCUSTOMER ID\t|\tCUSTOMER'S NAME\t|" << endl;
            cout << "-------------------------------------------------" << endl;
            db.prepareStatement("SELECT CUST_ID, CUST_NAME FROM CUSTOMER WHERE CUST_ID IN (SELECT CUST_ID FROM BOOKING WHERE BOOKING_ID IN (SELECT BOOKING_ID FROM PAYMENT WHERE PAYMENT_METHOD = ?))");
            db.stmt->setString(1, "EWallet");
            db.QueryResult();
            while (db.res->next()) {
                cout << "|\t" << db.res->getInt("CUST_ID") << "\t\t|\t " << db.res->getString("CUST_NAME") << "\t|" << endl;
                cout << "-------------------------------------------------" << endl;
                Tewallet++;
            }
            cout << endl;
            cout << "       Card Credit       " << endl;
            cout << "+-----------------------+" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "\tCUSTOMER ID\t|\tCUSTOMER'S NAME\t|" << endl;
            cout << "-------------------------------------------------" << endl;
            db.prepareStatement("SELECT CUST_ID, CUST_NAME FROM CUSTOMER WHERE CUST_ID IN (SELECT CUST_ID FROM BOOKING WHERE BOOKING_ID IN (SELECT BOOKING_ID FROM PAYMENT WHERE PAYMENT_METHOD = ?))");
            db.stmt->setString(1, "Card Credit");
            db.QueryResult();
            while (db.res->next()) {
                cout << "|\t" << db.res->getInt("CUST_ID") << "\t\t|\t " << db.res->getString("CUST_NAME") << "\t|" << endl;
                cout << "-------------------------------------------------" << endl;
                Tcard++;
            }
            cout << endl;
            cout << "      Online Payment      " << endl;
            cout << "+------------------------+" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "\tCUSTOMER ID\t|\tCUSTOMER'S NAME\t|" << endl;
            cout << "-------------------------------------------------" << endl;
            db.prepareStatement("SELECT CUST_ID, CUST_NAME FROM CUSTOMER WHERE CUST_ID IN (SELECT CUST_ID FROM BOOKING WHERE BOOKING_ID IN (SELECT BOOKING_ID FROM PAYMENT WHERE PAYMENT_METHOD = ?))");
            db.stmt->setString(1, "Online Payment");
            db.QueryResult();
            while (db.res->next()) {
                cout << "|\t" << db.res->getInt("CUST_ID") << "\t\t|\t " << db.res->getString("CUST_NAME") << "\t|" << endl;
                cout << "-------------------------------------------------" << endl;
                Tonline++;
            }

            totalPay = Tewallet + Tcard + Tonline;
            percentEwallet = (Tewallet / totalPay) * 100;
            percentCard = (Tcard / totalPay) * 100;
            percentOnline = (Tonline / totalPay) * 100;
            cout << endl;
            cout << "==--==--==--==--==--==--==--==--==--==" << endl;
            cout << "      PAYMENT METHOD COMPARISONS      " << endl;
            cout << "==--==--==--==--==--==--==--==--==--==" << endl;
            cout << endl;
            cout << "-------------------------------------------" << endl;
            cout << "    PAYMENT METHOD        PERCENTAGE    |" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "        EWallet       " << "      " << percentEwallet << "%     " << endl;
            cout << "-------------------------------------------" << endl;
            cout << "      Card Credit     " << "      " << percentCard << "%     " << endl;
            cout << "-------------------------------------------" << endl;
            cout << "    Online Payment    " << "      " << percentOnline << "%     " << endl;
            cout << "-------------------------------------------" << endl;

            if (percentEwallet > percentCard && percentEwallet > percentOnline)
            {
                maxpay = percentEwallet;
                MaxPayment = "EWallet";
                cout << endl;
                cout << "Highest Payment Method used by customer -> " << MaxPayment << " with -> " << maxpay << "%" << endl;
            }
            else if (percentCard > percentEwallet && percentCard > percentOnline)
            {
                maxpay = percentCard;
                MaxPayment = "Card Credit";
                cout << endl;
                cout << "Highest Payment Method used by customer -> " << MaxPayment << " with -> " << maxpay << "%" << endl;
            }
            else if (percentOnline > percentEwallet && percentOnline > percentCard)
            {
                maxpay = percentOnline;
                MaxPayment = "Online Payment";
                cout << endl;
                cout << "Highest Payment Method used by customer -> " << MaxPayment << " with -> " << maxpay << "%" << endl;
            }
            else
            {
                cout << endl;
                cout << "There is no highest payment method as there are payment methods with the same percentage of usage" << endl;
            }

        }
        else
        {
            db.~DBConnection();
        }

    }

    else
    {
        cout << "========================================================================================" << endl;
        cout << "You are not eligible to view the sales report!, Only managers can view the sales report!" << endl;
        cout << "========================================================================================" << endl;
        db.~DBConnection();
    }

}

//To re update the ticket availabilty after a cancellation process
void Ticket::reUpdate()
{
    DBConnection db;
    int catStocks, total, bookid, catid;

    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();
    while (db.res->next()) {
        bookid = db.res->getInt("lastid");
    }

    db.prepareStatement("SELECT CATEGORY_ID,TOTAL FROM BOOKING_CATEGORY WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, bookid);
    db.QueryResult();
    while (db.res->next()) {
        catid = db.res->getInt("CATEGORY_ID");
        total = db.res->getInt("TOTAL");

        db.prepareStatement("UPDATE CATEGORY SET CATEGORY_AVAILABILITY= CATEGORY_AVAILABILITY+? WHERE CATEGORY_ID =?");
        db.stmt->setDouble(1, total);
        db.stmt->setInt(2, catid);
        db.QueryStatement();

    }
    db.~DBConnection();
}

//To re update the ticket availability after a cancellation process
void Ticket::reUpdatePast(int bookid)
{
    DBConnection db;
    int catid, total;

    db.prepareStatement("SELECT CATEGORY_ID,TOTAL FROM BOOKING_CATEGORY WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, bookid);
    db.QueryResult();
    while (db.res->next()) {
        catid = db.res->getInt("CATEGORY_ID");
        total = db.res->getInt("TOTAL");

        db.prepareStatement("UPDATE CATEGORY SET CATEGORY_AVAILABILITY= CATEGORY_AVAILABILITY+? WHERE CATEGORY_ID =?");
        db.stmt->setDouble(1, total);
        db.stmt->setInt(2, catid);
        db.QueryStatement();

    }
    db.~DBConnection();
}

string getPaymentInfo(int bookid) {
    DBConnection db;
    int paymentID = 0;
    double amount = 0.00;

    db.prepareStatement("SELECT PAYMENT_ID, AMOUNT FROM PAYMENT WHERE BOOKING_ID = ?");
    db.stmt->setInt(1, bookid);
    db.QueryResult();

    string output;  // Use a stringstream to capture the output

    // Assuming you want to handle the case of multiple rows returned
    while (db.res->next()) {
        paymentID = db.res->getInt("PAYMENT_ID");
        amount = db.res->getDouble("AMOUNT");
        // Append payment information to the output stringstream
        output.append("Payment ID: ").append(to_string(paymentID)).append("\n");
        output.append("Amount Paid: RM").append(to_string(amount)).append("\n");
    }

    // Return the captured output as a string
    return output;
}


string Ticket::ticketImage()
{
    DBConnection db;

    db.prepareStatement("SELECT MAX(BOOKING_ID) AS lastid FROM BOOKING");
    db.QueryResult();

    std::string output;
    int bookid = getBookingID();
    string bookingid = std::to_string(bookid);

    output.append("+-----------------------------+\n");
    output.append("||=>      BOOKING DETAILS      <=||\n");
    output.append("+-----------------------------+\n\n");
    output.append("Booking ID : ");
    output.append(bookingid);
    output.append("\n\n");

    db.prepareStatement("SELECT C.CATEGORY_NAME, B.BOOKING_DATE, BC.TOTAL, CU.CUST_NAME FROM CATEGORY C JOIN BOOKING_CATEGORY BC ON C.CATEGORY_ID = BC.CATEGORY_ID JOIN BOOKING B ON BC.BOOKING_ID = B.BOOKING_ID JOIN CUSTOMER CU ON B.CUST_ID = CU.CUST_ID WHERE B.BOOKING_ID = ?");
    db.stmt->setInt(1, BOOKING_ID);
    db.QueryResult();

    while (db.res->next()) {
        output.append("Category Name     : ");
        output.append(db.res->getString("CATEGORY_NAME"));
        output.append("\nBooking Date    : ");
        output.append(db.res->getString("BOOKING_DATE"));
        output.append("\nTotal Booking   :");
        output.append(std::to_string(db.res->getInt("TOTAL")));
        output.append("\nCustomer's Name : ");
        output.append(db.res->getString("CUST_NAME"));
        output.append("\n\n");
    }

    // Return the entire output as a single string
    return output;
}

void Ticket::ticketPic() {
    int bookid = getBookingID();
    string pay = getPaymentInfo(bookid);
    string tick = ticketImage() + "\n" + pay;
    sf::Image generatedImage;
    sf::Texture texture;

    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\Acer\\Downloads\\Roboto-Black.ttf")) {
        // Handle font loading error
        cout << "Error loading font";
    }

    sf::Text text;
    text.setFont(font);
    text.setString(tick);
    text.setCharacterSize(36);  // Increase the font size to 36
    text.setFillColor(sf::Color::Black);  // Set text color to black
    text.setPosition(10, 10); // Adjust the position as needed

    const float inchesToMillimeters = 25.4f;
    const int dpi = 300;
    const float widthInInches = 8.27f;  // A4 width
    const float heightInInches = 11.69f; // A4 height

    int widthInPixels = static_cast<int>(widthInInches * dpi);
    int heightInPixels = static_cast<int>(heightInInches * dpi);

    sf::RenderTexture renderTexture;
    renderTexture.create(2000, 1500);

    renderTexture.clear(sf::Color::White);  // Set background color to white

    // Load the background image
    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("C:\\Users\\Acer\\Documents\\group project\\Project74\\HANIQACAH-THEMEPARK.png")) {
        // Create a sprite for the background
        sf::Sprite backgroundSprite(backgroundTexture);

        // Set the position of the background (adjust as needed)
        backgroundSprite.setPosition(0, 0);

        // Draw the background on the render texture
        renderTexture.draw(backgroundSprite);
    }
    else {
        // Handle background loading error
        cout << "Error loading background";
    }

    // Draw the text on the white background
    renderTexture.draw(text);
    renderTexture.display();

    // Get the rendered texture as an image
    sf::Image textImage = renderTexture.getTexture().copyToImage();

    string result = "Ticket.png";
    //string image = "C:\\Users\\Acer\\Documents\\group project\\Project84\\Project84\\";
    string image = "C:\\Users\\Acer\\Documents\\group project\\Project84\\Project84\\Ticket.png";

    // Save the final image to a file
    if (textImage.saveToFile(result)) {
        // Image saved successfully
    }
    std::system(("start " + std::string(result)).c_str());
}
