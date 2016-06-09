/**
 * @file    Transaction.cpp
 * @brief   A securities transaction, either buy or sell.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include "Transaction.h"

using namespace std;

// Default values chosen for historical significance, not utility
Transaction::Transaction() : year(1792), month(5), day(17), type(BUY),
        security("The Bank of New York"), quantity(10.0), price(5.0)
{
} // end default constructor

Transaction::Transaction(const Transaction& orig) : year(orig.year),
        month(orig.month), day(orig.day), type(orig.type),
        quantity(orig.quantity), price(orig.price)
{
    //security = new basic_string<char>(orig.security);
} // end copy constructor

Transaction::~Transaction()
{
} // end destructor

int Transaction::getYear(void) const
{
    return year;
} // end getYear()

int Transaction::getMonth(void) const
{
    return month;
} // end getMonth()

int Transaction::getDay(void) const
{
    return day;
} // end getDay()

bool Transaction::isPurchase(void) const
{
    return type == BUY;
}

string Transaction::getSecurity(void) const
{
    return security;
} // end getSecurity()

double Transaction::getQuantity(void) const
{
    return quantity;
} // end getQuantity()

double Transaction::getPrice(void) const
{
    return price;
} // end getPrice()

string Transaction::getBuyDate() const
{
    return buyDate;
} // end getSellDate()

void Transaction::setYear(int newYear)
{
    if (1790 < newYear <= CURRENT_YEAR)
    {
        year = newYear;
    }
} // end setYear()

void Transaction::setMonth(int newMonth)
{
    if (0 < newMonth < 13)
    {
        month = newMonth;
    }
} // end setMonth()

void Transaction::setDay(int newDay)
{
    if (0 < newDay < 32)
    {
        day = newDay;
    }
} // end setDay()

void Transaction::setType(int newType)
{
    if (newType == BUY || newType == SELL)
    {
        type = newType;
    }
}

void Transaction::setSecurity(string newSecurity)
{
    security = newSecurity;
} // end setSecurity()

void Transaction::setQuantity(double newQuantity)
{
    if (newQuantity >= 0.0)
    {
        quantity = newQuantity;
    }
} // end setQuantity()

void Transaction::setPrice(double newPrice)
{
    if (newPrice >= 0.0)
    {
        price = newPrice;
    }
} // end setPrice()

void Transaction::setBuyDate(string newDate)
{
    buyDate = newDate;
} // end setSellDate
