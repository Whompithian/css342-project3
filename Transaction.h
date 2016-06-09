/**
 * @file    Transaction.cpp
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#ifndef _TRANSACTION_H
#define	_TRANSACTION_H

#include <string>

using namespace std;

const int CURRENT_YEAR = 2011;
enum {BUY, SELL};

class Transaction
{
public:
    Transaction();
    Transaction(const Transaction& orig);
    virtual ~Transaction();

    int getYear(void) const;
    int getMonth(void) const;
    int getDay(void) const;
    bool isPurchase(void) const;
    string getSecurity(void) const;
    double getQuantity(void) const;
    double getPrice(void) const;
    string getBuyDate(void) const;
    void setYear(int);
    void setMonth(int);
    void setDay(int);
    void setType(int);
    void setSecurity(string);
    void setQuantity(double);
    void setPrice(double);
    void setBuyDate(string);

private:

    int    year;
    int    month;
    int    day;
    int    type;
    string security;
    double quantity;
    double price;
    string buyDate;
}; // end Transaction

#endif	/* _TRANSACTION_H */
