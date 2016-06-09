/**
 * @file    Report.cpp
 * @brief   Sorts securities transactions into buy and sell queues.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include <stdio.h>

#include "Report.h"

Report::Report()
{
} // end default constructor

Report::Report(const Report& orig)
    : purchases(orig.purchases), sales(orig.sales)
{
} // end copy constructor

Report::~Report()
{
} // end destructor

/** Check a transaction to see if it is a purchase or a sale and process it
 *  accordingly.
 * @param item  A securities transaction. Should not have buyDate set.
 * @pre item contains a full transaction, except buyDate.
 * @post item has been placed in its appropriate queue. If it was a sale, the
 *       corresponding purchase queue is changed to reflect the sale.
 * @return True if the transaction could be processed; false otherwise.
 */
bool Report::process(Transaction item)
{
    if (item.isPurchase())
    {
        return purchase(item);
    }
    else
    {
        return sell(item);
    } // end if (item.isPurchase())
} // end process()

/** Place a purchase transaction in the appropriate queue.
 * @param buyItem  The transaction to enqueue.
 * @pre buyItem is a transaction of type BUY.
 * @post buyItem is enqueued in the bought queue for its security. If the queue
 *       does not exist, it is created before enqueue.
 * @return true if buyItem could be enqueued; false otherwise.
 */
bool Report::purchase(Transaction& buyItem)
{
    string test;

    // travel through list, looking for security name
    for (int i = 1; i <= purchases.getLength(); ++i)
    {
        purchases.retrieve(i, test);

        if (test == buyItem.getSecurity())  // queue has been found
        {
            purchases.find(i)->bought->enqueue(buyItem);
            return true;
        }
    } // end for(int i = 1; i < purchases.getLength(); ++1)
    
    // List empty or security name not found
    Queue *newBuy = new Queue;      // create new queue and add buyItem
    newBuy->enqueue(buyItem);
    purchases.insert(1, buyItem.getSecurity(), newBuy);     // enlist queue

    return true;
} // end purchase()

/** Place a sale transaction in the appropriate queue.
 * @param sellItem  The transaction to enqueue.
 * @pre sellItem is a transaction of type SELL. There is already a bought queue
 *      for sellItem's security with enough transactions to cover the quantity
 *      of the sale.
 * @post sellItem is enqueued in the sold queue for its security.
 * @return true if sellItem could be enqueued; false otherwise
 */
bool Report::sell(Transaction& sellItem)
{
    bool multiDate = false;
    string test;
    /* travel through list, looking for security name
     * if the name is found, compare the quantity with frontQty (else, fail)
     * if frontQty is greater, -= it, update buyDate, enqueue in sales
     * if same, update buyDate, dequeue, enqueue in sales
     * if frontQty is less, -= quantity, dequeue, compare new frontQty
     */
    for (int i = 1; i <= purchases.getLength(); ++i)
    {
        purchases.retrieve(i, test);

        if (test == sellItem.getSecurity())
        {
            double check = sellItem.getQuantity();

            while(check > purchases.find(i)->frontQty)
            {
                check -= purchases.find(i)->frontQty;
                purchases.find(i)->bought->dequeue();
                purchases.resetFront(i);
                multiDate = true;
            } // end while(check > purchases.find(i)->frontQty)

            setDate(i, sellItem);
            
            if (check == purchases.find(i)->frontQty)
            {
                purchases.find(i)->bought->dequeue();
                purchases.resetFront(i);
            }
            else
            {
                purchases.find(i)->frontQty -= check;
            } // end if (check == purchases.find(i)->frontQty)
            
            if (multiDate)
            {
                sellItem.setBuyDate(MULTIDATE);
            } // end if (multiDate)
            
            purchases.find(i)->sold->enqueue(sellItem);

            return true;
        } // end if (test == sellItem.getSecurity())
    } // end for (int i = 1; i <= purchases.getLength(); ++i)

    return false;   // Security not found - no sell
} // end sell()

/** Sets the buyDate on a transaction of type SELL. Not needed it the buyDate
 *  is various.
 * @param index  The index of the security to sell.
 * @param target  The transaction to be updated with a buyDate.
 * @pre index points to a valid node of the list, containing the bought queue
 *      for target's security. Target is a transaction of type SELL.
 * @post target will have its buyDate set to the date of the transaction at the
 *       head of the bought queue for its security.
 */
void Report::setDate(int index, QueueItemType& target) const
{
    QueueItemType temp;
    char section[TEMPLENGTH];
    string date;

    for (int i = 0; i < TEMPLENGTH; ++i)
    {
        section[i] = '\0';
    } // end for (int i = 0; i < TEMPLENGTH; ++i)

    purchases.find(index)->bought->peek(temp);
    sprintf(section, "%d", temp.getMonth());

    for (int i = 0; section[i] != '\0' && i < TEMPLENGTH; ++i)
    {
        date += section[i];
        section[i] = '\0';
    } // end for (int i = 0; i < TEMPLENGTH; ++i)

    date += '/';

    sprintf(section, "%d", temp.getDay());

    for (int i = 0; section[i] != '\0' && i < TEMPLENGTH; ++i)
    {
        date += section[i];
        section[i] = '\0';
    } // end for (int i = 0; i < TEMPLENGTH; ++i)

    date += '/';

    sprintf(section, "%d", temp.getYear());

    for (int i = 0; section[i] != '\0' && i < TEMPLENGTH; ++i)
    {
        date += section[i];
    } // end for (int i = 0; i < TEMPLENGTH; ++i)

    target.setBuyDate(date);
} // end setSaleDate()
