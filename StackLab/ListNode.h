/* hasan Khan
 * hk4cd
 * Feb 2 2016
 * Filename: ListNode.h
 * Description: ListNode class definition
 */

#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

// next line needed because NULL is part of std namespace
using namespace std;

class ListNode {
public:
    ListNode();// Constructor 
private:
   
    ListNode *next;
    ListNode *previous;  // for doubly linked lists                                                                                                                           
    int value;

    // List needs to be able to access/change ListNode's next and
    // previous pointers
    // friend class ListNode;
    friend class List; 
    // ListItr needs to access/change ListNode as well
    friend class ListItr;

    // Not writing a destructor is fine in this case since there is no
    // dynamically allocated memory in this class.  No constructor is
    // necessary, as an object will be set up by the List class.
};

#endif
