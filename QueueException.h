/**
 * @file    QueueException.h
 *          Addapted from:
 *          Carrano, F. M. (2007). Linked Lists. In M. Hirsch (Ed.) "Data
 *              Abstraction & Problem Solving with C++: Walls and  Mirrors"
 *              (5th ed.) p. 348. Boston, MA: Pearson Education, Inc.
 * @author  Brendan Sweeney, SID 1161837
 * @date    November 10, 2011
 */

#ifndef _QUEUEEXCEPTION_H
#define	_QUEUEEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class QueueException : public logic_error
{
public:
    QueueException(const string & message = "")
            : logic_error(message.c_str())
    {
    }
}; // end QueueException

#endif	/* _QUEUEEXCEPTION_H */
