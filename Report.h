/**
 * @file    Report.h
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#ifndef _REPORT_H
#define	_REPORT_H

#include "LinkList.h"

const string MULTIDATE = "various";
const int TEMPLENGTH = 5;

class Report
{
public:

    Report();

    Report(const Report& orig);

    virtual ~Report();

/** Check a transaction to see if it is a purchase or a sale and process it
 *  accordingly.
 * @param item  A securities transaction. Should not have buyDate set.
 * @pre item contains a full transaction, except buyDate.
 * @post item has been placed in its appropriate queue. If it was a sale, the
 *       corresponding purchase queue is changed to reflect the sale.
 * @return True if the transaction could be processed; false otherwise.
 */
    bool process(Transaction item);

private:

/** Place a purchase transaction in the appropriate queue.
 * @param buyItem  The transaction to enqueue.
 * @pre buyItem is a transaction of type BUY.
 * @post buyItem is enqueued in the bought queue for its security. If the queue
 *       does not exist, it is created before enqueue.
 * @return true if buyItem could be enqueued; false otherwise.
 */
    bool purchase(Transaction& buyItem);

/** Place a sale transaction in the appropriate queue.
 * @param sellItem  The transaction to enqueue.
 * @pre sellItem is a transaction of type SELL. There is already a bought queue
 *      for sellItem's security with enough transactions to cover the quantity
 *      of the sale.
 * @post sellItem is enqueued in the sold queue for its security.
 * @return true if sellItem could be enqueued; false otherwise
 */
    bool sell(Transaction& sellItem);

/** Sets the buyDate on a transaction of type SELL. Not needed it the buyDate
 *  is various.
 * @param index  The index of the security to sell.
 * @param target  The transaction to be updated with a buyDate.
 * @pre index points to a valid node of the list, containing the bought queue
 *      for target's security. Target is a transaction of type SELL.
 * @post target will have its buyDate set to the date of the transaction at the
 *       head of the bought queue for its security.
 */
    void setDate(int index, QueueItemType& target) const;

    LinkList purchases;
    LinkList sales;

};

#endif	/* _REPORT_H */
