// Hasan Khan
// hk4cd
// April 18
// heap.cpp

#include "heap.h"
#include "hNode.h"
#include <iostream>
using namespace std;

heap::heap(){
   vector <hNode*> heapVec;
   heap_size=0;
   heapVec.push_back(0);
     
}

heap::heap(vector<hNode*> vec) : heap_size(vec.size()){

  heapVec = vec;  // creating heap, using passed vector
  heapVec.push_back(heapVec[0]); // creating dummy
  heapVec[0]=0;               // setting dummy to zero
    for (int i = heap_size/2; i > 0; i--)
        percolateDown(i);  

}

heap::~heap(){}

void heap::insert(hNode * h){

 
  heapVec.push_back(h);
  //cout << "Inserting, about to percolate" << endl;
 
  heap_size++;
  //cout << "Heap size: " << heap_size << endl;
  percolateUp(heap_size);
 

}

void heap::percolateUp(int hole){
  
  hNode * x = heapVec[hole];
  //cout << "Percolating: " << x->frequency << ", char: " << x->charVal <<endl;

  for ( ; (hole > 1) && (x->frequency < heapVec[hole/2]->frequency); hole/=2)
      heapVec[hole]=heapVec[hole/2];

  heapVec[hole]=x;
  //this->print();
}    


hNode* heap::deleteMin(){
 
  if (heap_size == 0)
      throw "deleteMin() called on empty heap";
  hNode* ret = heapVec[1];

  //cout << "deleteMintest0 " << endl;
  //cout << "deleteMintest1: heap size: " <<  heap_size << endl;
  //cout <<"deleteMintest2: frequency of last node: " << heapVec[heap_size--]-> frequency<< endl;
  
  heapVec[1]=heapVec[heap_size--];

  heapVec.pop_back();
   
  //cout << " Almost Done with deleteMin " << endl;
  percolateDown(1);

  //cout << " Done with deleteMin " << endl;
  return ret;

}

void heap::percolateDown (int hole) { 


  //cout << "Now in percolateDown " << endl;
   hNode * y = heapVec[hole];
  
   //while there is a left child
   while (hole*2 <= heap_size) {
    
    int child = hole*2; // the left child
    
    // is there a right child? if so, is it lesser?
    if ( (child+1 <= heap_size) && (heapVec[child+1]->frequency < heapVec[child]->frequency) )
      child++;

    if ( y->frequency > heapVec[child]->frequency){
      heapVec[hole] = heapVec[child];
      hole = child;
    } else
         break;
  }
  // correct position found! insert at that spot  
  heapVec[hole] = y;
}

void heap::print(){   // prints heap
    cout << "Printing the current heap: " << endl;
 for (int i = 1; i <= heap_size; i++){
    cout << heapVec[i]->frequency << "  " <<endl;
 }
 
}

hNode* heap::findMin(){  // returns the minimum of the heap
  if (heap_size == 0)
    throw "findMin() called on empty heap";
  return heapVec[1];
}

