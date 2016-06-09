/**
 * @file    Tokenizer.h
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#ifndef _TOKENIZER_H
#define	_TOKENIZER_H

//#include <cstdlib>
//#include <cstring>
//#include <iostream>

#include "Transaction.h"  // for BUY, SELL

using namespace std;

const char    DELIM = ',';
const int  LASTLINE = -1;
enum {YEAR, MONTH, DAY, TYPE, SECURITY, QUANTITY, PRICE};

class Tokenizer
{
public:
    Tokenizer();
    Tokenizer(const Tokenizer& orig);
    Tokenizer(istream& inputStream);
    virtual ~Tokenizer();

    void nextLine(void);
    bool isTransaction(void) const;
    bool isEndOfInput(void) const;
    int getYear(void) const;
    int getMonth(void) const;
    int getDay(void) const;
    int getType(void) const;
    string getSecurity(void) const;
    double getQuantity(void) const;
    double getPrice(void) const;
    int getTaxYear(void) const;

private:

    istream *record;
    string   currentLine;
    int      taxYear;
}; // end Tokenizer

#endif	/* _TOKENIZER_H */
