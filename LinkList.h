/**
 * @file    LinkList.h
 *          Addapted from:
 *          Carrano, F. M. (2007). Linked Lists. In M. Hirsch (Ed.) "Data
 *              Abstraction & Problem Solving with C++: Walls and  Mirrors"
 *              (5th ed.) pp. 195-197. Boston, MA: Pearson Education, Inc.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#ifndef _LINKLIST_H
#define	_LINKLIST_H

#include "ListException.h"
#include "ListIndexOutOfRangeException.h"
#include "Queue.h"

typedef string ListItemType;


class LinkList
{

public:

    friend class Report;

// Constructors and destructor:

    /** Default constructor.
     */
    LinkList();

    /** Copy constructor.
     * @param orig  The list to copy.
     */
    LinkList(const LinkList& orig);

    /** Destructor.
     */
    virtual ~LinkList();

// List operations:

    /** Determine if a list is empty.
     * @pre None.
     * @post The list remains unchanged.
     * @return true if there are no nodes in the list, false if the list
     *         contains one or more nodes.
     */
    bool isEmpty() const;

    /** Determine the length of a list.
     * @pre None.
     * @post The list remains unchanged.
     * @return The number of nodes in the list, 0 if empty.
     */
    int getLength() const;

    /** Insert a new node at a specified index. The node currently at that
     *  index will be placed after the new node.
     * @param index  Location to insert the new node.
     * @param newItem  The data to store in the new node.
     * @pre index is within range of the listed items; there are enough
     *      resources to allocate memory for a new node.
     * @post The list contains a new node at the specified index. The node
     *       formerly at the specified index now follows the new node and
     *       length is updated to count the new node.
     * @throw ListIndexOutOfRangeException  If index lies outside the range of
     *        items in the list.
     * @throw ListException  If there are insufficient resources to allocate
     *        memory for a new node.
     */
    void insert(int index, const ListItemType& newItem, Queue* newBuy)
        throw(ListIndexOutOfRangeException, ListException);

    /** Delete a node from a specified index. The node currently after the
     *  index will occupy the index location afterwards.
     * @param index  Location of the node to be removed.
     * @pre index is within range of the listed items.
     * @post The node at the specified location is deleted and its memory
     *       returned to the system. The node that followed the deleted node is
     *       now at index and length is updated to discount the old node.
     * @throw ListIndexOutOfRangeException  If index lies outside the range of
     *        items in the list.
     */
    void remove(int index)
        throw(ListIndexOutOfRangeException);

    /** Gets the data item from a node at a specified index.
     * @param index  Location of the node to find.
     * @param dataItem  Reference for the located data.
     * @pre index is within range of the listed items; the node at the desired
     *          index contains data.
     * @post The node at the desired index is found and its data is referenced
     *       by dataItem. The list remains unchanged.
     * @throw ListIndexOutOfRangeException  If index lies outside the range of
     *        items in the list.
     */
    void retrieve(int index, ListItemType& dataItem) const
        throw(ListIndexOutOfRangeException);

private:

    struct ListNode
    {
        ListItemType item;
        Queue *bought;
        Queue *sold;
        double frontQty;
        ListNode *next;
    }; // end ListNode

    int size;
    ListNode *head;

    /** Get a pointer to a node at a specified index.
     * @param index  Location of the node to find.
     * @pre index is within range of the listed items.
     * @post The ListNode at the desired index is found and the list is
     *       unchanged.
     * @return Pointer to the ListNode at the desired index.
     */
    ListNode *find(int index) const;

    void resetFront(int index);
}; // end LinkList

#endif	/* _LINKLIST_H */
