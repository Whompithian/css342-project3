/**
 * @file    Queue.cpp
 *          Addapted from:
 *          Carrano, F. M. (2007). Linked Lists. In M. Hirsch (Ed.) "Data
 *              Abstraction & Problem Solving with C++: Walls and  Mirrors"
 *              (5th ed.) pp. 352-354. Boston, MA: Pearson Education, Inc.
 * @brief   A queue built on top of a linked list.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include <cassert>      // for assert
#include <cstddef>      // for NULL
#include <new>          // for bad_alloc

#include "Queue.h"

using namespace std;

Queue::Queue() : back(NULL), front(NULL)
{
} // end default constructor

Queue::Queue(const Queue& orig)
{
    if (orig.back == NULL)
    {
        // original queue is empty
        front = NULL;
        back = NULL;
    }
    else
    {
        // copy first node
        front = new QueueNode;
        back = front;
        back->item = orig.front->item;

        // copy rest of list
        for (QueueNode *origPtr = orig.front->next;     // iterator for orig
                origPtr != NULL;
                origPtr = origPtr->next)
        {
            back->next = new QueueNode;     // create next node
            back = back->next;              // pint back to new node
            back->item = origPtr->item;     // update new node item
        } //end for()
    } // end if (orig.back == NULL)
} // end copy constructor

Queue::~Queue()
{
    while(!isEmpty())
    {
        dequeue();
    } // end while(!isEmpty()
} // end destructor

bool Queue::isEmpty() const
{
    return back == NULL;
} // end isEmpty()

void Queue::enqueue(const QueueItemType& newItem) throw(QueueException)
{
    try
    {
        // create a new node
        QueueNode *newPtr = new QueueNode;

        // set data portion of new node
        newPtr->item = newItem;

        newPtr->next = NULL;

        // insert the new node
        if (isEmpty())
        {
            // insertion into empty queue
            front = newPtr;
        }
        else
        {
            // insertion into nonempty queue
            back->next = newPtr;
        } // end if (isEmpty())

        back - newPtr;  // new node is at back
    }
    catch (bad_alloc e)
    {
        throw QueueException(
                "QueueException: enqueue cannot allocate memory.");
    } // end try
} // end enqueue()

void Queue::dequeue() throw(QueueException)
{
    if (isEmpty())
    {
        throw QueueException(
                "QueueException: empty queue, cannot dequeue");
    }
    else
    {
        // queue is not empty; remove front
        QueueNode *tempPtr = front;
        if (front == back)  // special case
        {
            // one node in queue
            front = NULL;
            back = NULL;
        }
        else
        {
            front = front->next;
        } // end if (front == back)

        tempPtr->next = NULL;   // cleanup
        delete tempPtr;
    } // end if (isEmpty())
} // end dequeue()

void Queue::dequeue(QueueItemType& queueFront)
    throw(QueueException)
{
    if (isEmpty())
    {
        throw QueueException(
                "QueueException: empty queue, cannot dequeue");
    }
    else
    {
        // queue is not empty; retrieve front
        queueFront = front->item;
        dequeue();  // delete front
    } // end if (isEmpty())
} // end dequeue(queueFront)

void Queue::peek(QueueItemType& queueFront) const
    throw(QueueException)
{
    if (isEmpty())
    {
        throw QueueException(
                "QueueException: empty queue, cannot peek");
    }
    else
    {
        // queue is not empty; retrieve front
        queueFront = front->item;
    } // end if (isEmpty())
} // end peek()
