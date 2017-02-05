
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "hNode.h"

using namespace std;

class heap {

public:
   heap();
   heap(vector <hNode*> x);
  ~heap();
   void insert(hNode *x);
   void percolateUp(int hole);
   void percolateDown(int hole);
   hNode* deleteMin();
   hNode* findMin();
   void print();
   // hNode findMin();
   //void deleteMin();
   
   int heap_size;

private:
   vector <hNode*> heapVec;   
};

#endif
