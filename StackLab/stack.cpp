//Hasan Khan                                                                  
//hk4cd                                                                      \
//Februaruy 11, 2016                                                         \
//stack.cpp                                                                       
#include "stack.h"
#include "List.h"
#include "ListNode.h"
#include "ListItr.h"
using namespace std; 

stack:: stack(){
  //cout << "Homemade stack constructor!" << endl;
  stackL = new List();   
}

stack:: ~stack(){
  //cout << "Homemade stack destructor!" << endl;
}

void stack :: push(int x){
 stackL->insertAtTail(x);
}

void stack :: pop(){
  stackL->remove(stackL->last().retrieve()); 
}
int stack :: top(){
  return stackL->last().retrieve();
}
bool stack :: empty(){


  return stackL->isEmpty();


} 
