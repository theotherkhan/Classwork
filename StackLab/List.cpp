/* Hasan Khan                                                                                                                                              
 * hk4cd                                                                                                                                             
 * Feb 2 2016                                                                                                                                          
 * Filename: List.cpp                                                                                                                  
 * Description: List.cpp implementation                                                                                                                       */

#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include "List.h"
using namespace std;

List::List(){
  //cout << "Default constructor" << endl;
  head = new ListNode;
  tail = new ListNode;

  head-> next = tail;
  tail-> previous = head;

  head-> value = NULL;
  tail-> value = NULL;

  count = 0;

  //cout << "List() contrusctor printing!"<< endl;    
}

// main method main method main method main method
                                                                                                                                   

List::List(const List& source) {      // Copy Constructor
  head=new ListNode;
  tail=new ListNode;
  head->next=tail;
  tail->previous=head;
  count=0;
  ListItr iter(source.head->next);
  while (!iter.isPastEnd()) {       // deep copy of the list
    insertAtTail(iter.retrieve());
    iter.moveForward();
  }
}

List::~List(){
    
  if (!isEmpty()){
    makeEmpty();}
  delete head;
  delete tail;
}            
 //Destructor

  
List& List::operator=(const List& source) { //Equals operator
  if (this == &source)
    return *this;
  else {
    makeEmpty();
    ListItr iter(source.head->next);
    while (!iter.isPastEnd()) {
      insertAtTail(iter.retrieve());
      iter.moveForward();
    }
  }
  return *this;
}                                                                                                                    


bool List::  isEmpty() const{
  if (size() == 0){
    return true;
  }
  return false;
}    
//Returns true if empty; else false                                                                                                          

void List :: makeEmpty(){
  //cout << "Making list empty..." << endl;
  
  ListItr * iterator = new ListItr();
  iterator->current =  first().current;

  while (!(iterator->isPastEnd())){
    
    delete iterator->current;
    iterator->moveForward();
  } 

  head->next = tail;
  tail-> previous = head;
 }   
//Removes all items except blank head and tail                                                                                                               


ListItr List::first(){

  //cout << " Currently in first() method" << endl;
  ListItr firstPos (head->next);
  return firstPos;
}            
//Returns an iterator that points to the ListNode in the first position                                                                                                                                            
ListItr List::last(){
  
  //cout << " Marker 1" << endl;
  ListItr lastPos (tail);
  //cout << " Marker 2" << endl;
  lastPos.moveBackward();
  //cout << " Marker 4" << endl;
  //cout << " Returning lastPos" << endl;
  return lastPos; 

}                     
//Returns an iterator that points to the ListNode in the last position                                                                                                                                              
void List::insertAfter(int x, ListItr position){

  
  //cout << "Attempting to insertAfter..." << endl;
  ListNode * nnode = new ListNode();
  nnode -> value = x;

  ListNode * insertAfterThis = position.current;
  ListNode * insertBeforeThis = position.current->next;
  insertAfterThis -> next = nnode;
  nnode -> previous = insertAfterThis;
  nnode -> next = insertBeforeThis;
  insertBeforeThis->previous = nnode;

  count++; 
 
} 
//Inserts x after current iterator position p                                                                                                                                    

void List::insertBefore(int x, ListItr position){

  //cout << "Attempting to insertBefore..." << endl;
  ListNode * nnode = new ListNode();
  nnode -> value = x;

  ListNode * insertBeforeThis = position.current;
  ListNode * insertAfterThis = position.current->previous;
  insertAfterThis -> next = nnode;
  nnode -> previous = insertAfterThis;
  nnode -> next = insertBeforeThis;
  insertBeforeThis->previous = nnode;

  count++;     
}
//Inserts x before current iterator position p                                                                                                                                   

void List:: insertAtTail(int x){
   
  ListNode * nnode = new ListNode();
  nnode -> value = x;
  count++;
  //cout << "Made it up to last().current -> next = nnode" << endl;
  //cout << "Last iterator's next position: " << last().current << endl;
  //cout << " Second print" << endl;
  last().current->next = nnode;

  //cout << "marker 1" << endl;
  nnode-> previous = last().current;
  nnode-> next = tail;
  //cout << "marker 2" << endl;
  tail->previous = nnode;
  //cout << "Inserted at tail" << endl;
    
}
 //Insert x at tail of list
                                                                                                                           

void List:: remove(int x){
  ListItr * iterator = new ListItr();
  iterator->current =  last().current;
 
  //cout << " making remove iterator... "<< endl;
  bool a = true;
  while (!iterator->isPastBeginning() && a == true) {
    //cout << "remove while loop... "<< endl;
    if ((iterator->current -> value) == x){
      ListNode * before = (iterator->current)->previous;
      ListNode * after = (iterator->current)->next;
      before->next = after;
      after->previous = before;
      delete iterator->current;
      a = false;
      //cout << " deleted old node... "<< endl;
    }

    else{
      iterator->moveBackward();
      //cout << " not remove val, moving forward... "<< endl;
    }   //will this work? Try List().head;                                                
  }    
}
 //Removes the first occurrence of x

ListItr List:: find(int x){
  
  ListItr * iterator = new ListItr();
  iterator->current =  first().current; 

  while (!iterator->isPastEnd()){
   if ((iterator->current -> value) == x){
     return *iterator;
   }   
   else{
     iterator->moveForward();
   }   //will this work? Try List().head;
  }

  return *iterator;
}  
//Returns an iterator that points to                                                                                                         
// the first occurrence of x, else return a iterator to the dummy tail node                                                                                                      
int List:: size() const{
  
  return count;
} 
//Returns the number of elements in the list        

void printList(List& source, bool direction) {
  //cout << "printing list" << endl;
  if (direction==true){
  
    ListItr iterator =source.first();
    while(!iterator.isPastEnd()){
      cout << iterator.retrieve() << endl;
      iterator.moveForward();}
  }
  if (direction==false){
    ListItr iterator =source.last();
    while(!iterator.isPastBeginning()){
      cout << iterator.retrieve() << endl;
      iterator.moveBackward();}
  }
 }
