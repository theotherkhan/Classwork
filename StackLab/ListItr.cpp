//Hasan Khan
//hk4cd
//Febraury 3, 2016
//Filename: ListItr.cpp
// Description: ListItr implementation

#include "ListItr.h"
#include <iostream>

using namespace std;

ListItr::ListItr()
{
  current = NULL;
}                  //Constructor                                                                                                                                        
ListItr::ListItr(ListNode* theNode){
  current = theNode;

} // One parameter constructor                                                                                                                         
bool ListItr:: isPastEnd() const{
  if (current->value == NULL)
    return true;
  else
    return false;

}     //Returns true if past end position                                                                                                                  
// in list, else false                                                                                                                                                           
bool ListItr:: isPastBeginning() const{
  if (current->value==NULL){
    return true;}
  else{
    return false;}

}
//Returns true if past first position                                                                                                               
// in list, else false                                                                                                                                                           
void ListItr:: moveForward(){
    current = current->next;
    //cout << " moving forward..."<< endl;

} //Advances current to next position in list                                                                                                                  
//(unless already past end of list)                                                                                                                                              
void ListItr:: moveBackward(){
    current = current->previous;
    //cout << " moving backward..."<< endl;


}        //Moves current back to previous position                                                                                                            
// in list (unless already past beginning of                                                                                                                                     
// list)                                                                                                                                                                         
int ListItr:: retrieve() const{
  return  (current->value);
}       //Returns item in current position                                                                                                                   

