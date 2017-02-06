//Hasan Khan
//hk4cd 
//Febraury 9 2016 
//postfixCalculator.cpp

#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "postfixCalculator.h"

using namespace std;
postfixCalculator:: postfixCalculator(){

  //cout << "Constructor for postfixCalculator" << endl;

}

postfixCalculator:: ~postfixCalculator(){
  //cout << "destructor" << endl;
  
}

void postfixCalculator::add(){
  
 int tempHead = ctop();
 cpop();
 cout << "Adding " << newStack.top() << " with " << tempHead << endl;
 int sum = ctop() + tempHead; 
 cpop();
 newStack.push(sum);

}
void postfixCalculator::subtract(){

  int tempHead = ctop();
  cpop();
  cout << "Subtracting " << tempHead << " from " << newStack.top() << endl;
  int difference = ctop() - tempHead;
  cpop();
  cout << "Pushing new difference onto top: " << difference << endl;
  newStack.push(difference);

}
void postfixCalculator::multiply(){

  int tempHead = ctop();
  cpop();
  cout << "Multiplying " << newStack.top() << " with " << tempHead << endl;
  int product  = ctop() * tempHead;
  cpop();
  newStack.push(product);

}

void postfixCalculator::negate(){

  int tempHead = ctop();
  cpop();
  cout << "Negating " << tempHead << endl;
  tempHead = -tempHead;
  cpush(tempHead);

}

void postfixCalculator::divide(){

  int tempHead = ctop();
  cpop();
  cout << "Dividing " << tempHead  << " with " << tempHead << endl;
  int quotient = ctop() /  tempHead;
  cpop();
  cout << "Pushing new quotientn onto top: " << quotient << endl;
  newStack.push(quotient);

}

void postfixCalculator::cpush( int y){
  

    cout << "pushing " << y << " onto stack" << endl; 
    newStack.push(y);
}

void postfixCalculator::cpop(){
  if (isEmpty()==false){
    cout << "Popping " << newStack.top() << " from stack" << endl;
    newStack.pop();
  }

  else{
    cout << "Cant pop b/c stack is empty" << endl;}
}

int postfixCalculator::ctop(){
  
  if (isEmpty()==false){ 
      cout << "Returning top of stack:" << newStack.top() << endl;
      return newStack.top();
  } 

  else 
    return 0;
}

bool postfixCalculator::isEmpty(){
  if (newStack.empty()==true){
    return true;}
  
  else{
    return false;
  }
}
