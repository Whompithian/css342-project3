/**
 * @file    LinkList.cpp
 *          Addapted from:
 *          Carrano, F. M. (2007). Linked Lists. In M. Hirsch (Ed.) "Data
 *              Abstraction & Problem Solving with C++: Walls and  Mirrors"
 *              (5th ed.) pp. 197-202. Boston, MA: Pearson Education, Inc.
 * @brief   A pointer-based list object with dynamic size.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#include <cstddef>          // for NULL
#include <new>              // for bad_alloc
#include "LinkList.h"

using namespace std;


/** Default constructor.
 */
LinkList::LinkList() : size(0), head(NULL)
{
} // end default constructor

/** Copy constructor.
 * @param orig  The list to copy.
 */
LinkList::LinkList(const LinkList& orig) : size(orig.size)
{
    if (orig.head == NULL)
    {
        head = NULL;    // original list is empty
    }
    else
    {
        // copy first node
        head = new ListNode;
        head->item = orig.head->item;
        head->bought = orig.head->bought;
        head->frontQty = orig.head->frontQty;

        // copy rest of list
        ListNode *newPtr = head;    // new list pointer
        // newPtr points to last node in new list
        // origPtr points to nodes in original list
        for (ListNode *origPtr = orig.head->next;
                origPtr != NULL;
                origPtr = origPtr->next)
        {
            newPtr->next = new ListNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
            newPtr->frontQty = origPtr->frontQty;
        } // end for (ListNode *origPtr = orig.head->next;

        newPtr->next = NULL;
    } // end if (orig.head == NULL)
} // end copy constructor

/** Destructor.
 */
LinkList::~LinkList()
{
    while(!isEmpty())
    {
        remove(1);
    } // end while(!isEmpty())
} // end destructor

/** Determine if a list is empty.
 * @pre None.
 * @post The list remains unchanged.
 * @return true if there are no nodes in the list, false if the list contains
 *         one or more nodes.
 */
bool LinkList::isEmpty() const
{
    return size == 0;
} // end isEmpty()

/** Determine the length of a list.
 * @pre None.
 * @post The list remains unchanged.
 * @return The number of nodes in the list, 0 if empty.
 */
int LinkList::getLength() const
{
    return size;
} // end getLength()

/** Get a pointer to a node at a specified index.
 * @param index  Location of the node to find.
 * @pre index is within range of the listed items.
 * @post The ListNode at the desired index is found and the list is unchanged.
 * @return Pointer to the ListNode at the desired index.
 */
LinkList::ListNode *LinkList::find(int index) const
{
    if ( (index < 1) || (index > getLength()) )
    {
        return NULL;
    }
    else // count from the beginning of the list
    {
        ListNode *cur = head;
        for (int skip = 1; skip < index; ++skip)
        {
            cur = cur->next;
        }
        return cur;
    } // end if ( (index <1) || (index > getLength()) )
} // end find()

/** Get the data item from a node at a specified index.
 * @param index  Location of the node to find.
 * @param dataItem  Reference for the located data.
 * @pre index is within range of the listed items; the node at the desired
 *          index contains data.
 * @post The node at the desired index is found and its data is referenced by
 *       dataItem. The list remains unchanged.
 * @throw ListIndexOutOfRangeException  If index lies outside the range of
 *        items in the list.
 */
void LinkList::retrieve(int index, ListItemType& dataItem) const
    throw(ListIndexOutOfRangeException)
{
    if ( (index < 1) || (index > getLength()) )
    {
        throw ListIndexOutOfRangeException(
                "ListIndexOutOfRangeException: retrieve index out of range");
    }
    else
    {
        // get pointer to node, then data in node
        ListNode *cur = find(index);
        dataItem = cur->item;
    }  // end if ( (index < 1) || (index > getLength()) )
} // end retrieve()

/** Insert a new node at a specified index. The node currently at that index
 *  will be placed after the new node.
 * @param index  Location to insert the new node.
 * @param newItem  The data to store in the new node.
 * @pre index is within range of the listed items; there are enough resources
 *      to allocate memory for a new node.
 * @post The list contains a new node at the specified index. The node formerly
 *       at the specified index now follows the new node and length is updated
 *       to count the new node.
 * @throw ListIndexOutOfRangeException  If index lies outside the range of
 *        items in the list.
 * @throw ListException  If there are insufficient resources to allocate memory
 *        for a new node.
 */
void LinkList::insert(int index, const ListItemType& newItem, Queue *newBuy)
    throw(ListIndexOutOfRangeException, ListException)
{
    int newLength = getLength() + 1;

    if ( (index < 1) || (index > newLength) )
    {
        throw ListIndexOutOfRangeException(
                "ListIndexOutOfRangeException: insert index out of range");
    }
    else
    {
        // create new node and place newItem in it
        try // try to allocate memory
        {
            ListNode *newPtr = new ListNode;
            QueueItemType temp;
            newBuy->peek(temp);
            size = newLength;
            newPtr->item = newItem;
            newPtr->bought = newBuy;
            newPtr->frontQty = temp.getQuantity();

            // attach new node to list
            if (index == 1)
            {
                // insert new node after node to which prev points
                newPtr->next = head;
                head = newPtr;
            }
            else
            {
                ListNode *prev = find(index - 1);
                // insert new node after node to which prev points
                newPtr->next = prev->next;
                prev->next = newPtr;
            } // end if (index == 1)
        }
        catch (bad_alloc e)
        {
            throw ListException(
                    "ListException: insert cannot allocate memory.");
        } // end try
    } // end if ( (index < 1) || (index > newLength) )
} // end insert()

/** Delete a node from a specified index. The node currently after the index
 *  will occupy the index location afterwards.
 * @param index  Location of the node to be removed.
 * @pre index is within range of the listed items.
 * @post The node at the specified location is deleted and its memory returned
 *       to the system. The node that followed the deleted node is now at index
 *       and length is updated to discount the old node.
 * @throw ListIndexOutOfRangeException  If index lies outside the range of
 *        items in the list.
 */
void LinkList::remove(int index)
    throw(ListIndexOutOfRangeException)
{
    ListNode *cur = NULL;

    if ( (index < 1) || (index > getLength()) )
    {
        throw ListIndexOutOfRangeException(
                "ListIndexOutOfRangeException: remove index out of range");
    }
    else
    {
        --size;
        if (index == 1)
        {
            // delete the first node from the list
            cur = head;     // save pointer to node
            head = head->next;
        }
        else
        {
            ListNode *prev = find(index - 1);
            // delete the node after the node to which prev points
            cur = prev->next;   // save pointer to node
            prev->next = cur->next;
        } // end if (index == 1)

        // return node to system
        cur->next = NULL;
        delete cur;
        cur = NULL;
    } // end if ( (index < 1) || (index > getLength()) )
} // end remove()

void LinkList::resetFront(int index)
{
    QueueItemType temp;

    find(index)->bought->peek(temp);
    find(index)->frontQty = temp.getQuantity();
} // end resetFront()
