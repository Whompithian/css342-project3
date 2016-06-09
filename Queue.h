/**
 * @file    Queue.h
 *          Addapted from:
 *          Carrano, F. M. (2007). Linked Lists. In M. Hirsch (Ed.) "Data
 *              Abstraction & Problem Solving with C++: Walls and  Mirrors"
 *              (5th ed.) pp. 350-352. Boston, MA: Pearson Education, Inc.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 8, 2011
 */

#ifndef _QUEUE_H
#define	_QUEUE_H

#include "QueueException.h"
#include "Transaction.h"

typedef Transaction QueueItemType;

class Queue
{
public:
// Constructors and destructor:

    // Default constructor
    Queue();

    // Copy constructor
    Queue(const Queue& orig);

    // Destructor
    virtual ~Queue();

// Queue operations:

    /** Determines whether this queue is empty.
     * @pre None.
     * @post None.
     * @return True is this queue is empty; othersie returns false.
     */
    bool isEmpty() const;

    /** Inserts an item at the back of this queue.
     * @pre newItem is the item to be inserted.
     * @post If the insertion is successful, newItem is at the back of this
     *       queue.
     * @throw QueueException  If memory allocation fails.
     */
    void enqueue(const QueueItemType& newIem)
        throw(QueueException);

    /** Dequeues the front of this queue.
     * @pre None.
     * @post If this queue is not empty, the item that was added to this queue
     *       earliest is deleted.
     * @throw QueueException  If this queue is empty.
     */
    void dequeue() throw (QueueException);

    /** Retrieves and deletes the front of this queue.
     * @pre None.
     * @post If this queue is not empty, queueFront contains the item that was
     *       added to this queue earliest and that item is deleted.
     */
    void dequeue(QueueItemType& queueFront) throw(QueueException);

    /** Retrieves the item at the front of a queue.
     * @pre None.
     * @post If this queue is not empty, queueFront contains the item that was
     *       added to this queue earliest.
     * @throw QueueException  If this queue is empty.
     */
    void peek(QueueItemType& queueFront) const
        throw(QueueException);


private:
    /** The queue is implemented as a linked list with one external pointer to
     *  the front of the queue and a second external pointer to the back of the
     *  queue.
     */
    struct QueueNode
    {
        QueueItemType   item;
        QueueNode      *next;
    }; // end QueueNode

    QueueNode *back;
    QueueNode *front;
}; // end Queue

#endif	/* _QUEUE_H */
