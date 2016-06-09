/**
 * @file    capitaGainsReport.cpp
 * @brief   Takes as input a record of securities transactions and determines
 *          short- and long-term capital gains, displaying a report organized
 *          by sale.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include <cstdlib>
#include <iostream>

#include "Report.h"
#include "Tokenizer.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    Tokenizer record = Tokenizer(cin);      // Process input
    Report history;                         // Sort input into queues
    Transaction temp;                       // Examine single transaction

    record.nextLine();      // Initialize the tokenizer

    // Get records one at a time and record them in history
    while(record.isTransaction())
    {
        temp.setYear(record.getYear());
        cout << temp.getYear() << endl;
        temp.setMonth(record.getMonth());
        cout << temp.getMonth() << endl;
        temp.setDay(record.getDay());
        cout << temp.getDay() << endl;
        temp.setType(record.getType());
        cout << temp.isPurchase() << endl;
        temp.setSecurity(record.getSecurity());
        cout << temp.getSecurity() << endl;
        temp.setQuantity(record.getQuantity());
        cout << temp.getQuantity() << endl;
        temp.setPrice(record.getPrice());
        cout << temp.getPrice() << endl;

        //history.process(temp);
        record.nextLine();
    } // end while(record.isTransaction())

    return (EXIT_SUCCESS);      // should be EXIT_SHAME
} // end main()
