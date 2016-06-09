/**
 * @file    Tokenizer.cpp
 * @brief   Reads from an input stream and breaks down into tokens relating to
 *          securities transacitons.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include <cstdlib>
#include <iostream>

#include "Tokenizer.h"

using namespace std;

Tokenizer::Tokenizer() : record(NULL), currentLine(""), taxYear(0)
{
} // end default constructor

Tokenizer::Tokenizer(const Tokenizer& orig) : record(orig.record),
            currentLine(orig.currentLine), taxYear(orig.taxYear)
{
} // end copy constructor

Tokenizer::Tokenizer(istream& inputStream) : record(&inputStream)
{
} // end initialization constructor

Tokenizer::~Tokenizer()
{
} // end destructor

void Tokenizer::nextLine(void)
{
    getline(*record, currentLine);
    
    if (isEndOfInput())
    {
        string temp = "";
        int iter = currentLine.find(DELIM) + 2;
        while(iter < currentLine.length())
        {
            if (isdigit(currentLine.at(iter)))
            {
                temp += currentLine.at(iter);
                ++iter;
            }
        }
        taxYear = atoi(temp.c_str());
    }
} // end nextLine()

bool Tokenizer::isTransaction(void) const
{
    return isdigit(currentLine.at(0));
} // end isTransaction()

bool Tokenizer::isEndOfInput(void) const
{
    return !isTransaction();
} // end isEndOfInput()

int Tokenizer::getYear(void) const
{
    string temp = "";
    for (int i = 0; isdigit(currentLine.at(i))
                    && i < currentLine.length(); ++i)
    {
        temp += currentLine.at(i);
    }
    return atoi(temp.c_str());
} // end getYear()

int Tokenizer::getMonth(void) const
{
    string temp = "";
    int iter = currentLine.find(DELIM) + 1;
    while(isdigit(currentLine.at(iter)) && iter < currentLine.length())
    {
        temp += currentLine.at(iter);
        ++iter;
    }
    return atoi(temp.c_str());
} // end getMonth

int Tokenizer::getDay(void) const
{
    string temp = "";
    int iter = 0;

    for (int i = 0; i < DAY; ++i)
    {
        iter = currentLine.find(DELIM, iter) + 1;
    }
    while(isdigit(currentLine.at(iter)) && iter < currentLine.length())
    {
        temp += currentLine.at(iter++);
    }
    return atoi(temp.c_str());
} // end getDay()

int Tokenizer::getType(void) const
{
    string temp = "";
    int iter = 0;

    for (int i = 0; i < TYPE; ++i)
    {
        iter = currentLine.find(DELIM, iter) + 1;
    }
    while(currentLine.at(iter) != DELIM && iter < currentLine.length())
    {
        temp += currentLine.at(iter++);
    }
    if (temp == "BUY")
    {
        return BUY;
    }
    else if (temp == "SELL")
    {
        return SELL;
    }
    return -1;
}

string Tokenizer::getSecurity(void) const
{
    string temp = "";
    int iter = 0;

    for (int i = 0; i < SECURITY; ++i)
    {
        iter = currentLine.find(DELIM, iter) + 1;
    }
    while (currentLine.at(iter) != DELIM && iter < currentLine.length())
    {
        temp += currentLine.at(iter++);
    }
    return temp;
} // end getSecurity()

double Tokenizer::getQuantity(void) const
{
    string temp = "";
    int iter = 0;

    for (int i = 0; i < QUANTITY; ++i)
    {
        iter = currentLine.find(DELIM, iter) + 1;
    }
    while (isdigit(currentLine.at(iter)) || currentLine.at(iter) == '.'
                    && iter < currentLine.length())
    {
        temp += currentLine.at(iter++);
    }
    return atof(temp.c_str());
} // end getQuantity()

double Tokenizer::getPrice(void) const
{
    string temp = "";
    int iter = 0;

    for (int i = 0; i < PRICE; ++i)
    {
        iter = currentLine.find(DELIM, iter) + 1;
    }
    while (iter < currentLine.length())
    {
        if (isdigit(currentLine.at(iter)) || currentLine.at(iter) == '.')
        {
            temp += currentLine.at(iter++);
        }
    }
    return atof(temp.c_str());
} // end getPrice()

int Tokenizer::getTaxYear(void) const
{
    return taxYear;
} // end getTaxYear()
