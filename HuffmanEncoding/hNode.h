// hNode.h

#ifndef HNODE
#define HNODE

#include <string>

using namespace std;

class hNode{

 public:
  hNode();
  hNode (int f, char val);
  hNode (char val, string prefix);
  ~hNode();

  
  hNode * left;
  hNode * right;
 
  int charVal;
  int frequency;
  string prefixVal;
  
  friend class heap;

};

#endif
