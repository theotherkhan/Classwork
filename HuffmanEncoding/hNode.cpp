// Hasan Khan
// hk4cd
// April 18
// hNode.cpp

#include "hNode.h"
#include <iostream>


using namespace std;

hNode::hNode(){
  //cout << "Defualt hNode constructor" << endl; 
  charVal = NULL;
  frequency = NULL;
  left = NULL;
  right = NULL;
  prefixVal = "";
}

hNode::hNode(int f, char val){
  charVal = val;
  frequency = f;
  left = NULL;
  right = NULL;
  prefixVal = "";
}

hNode::hNode(char val, string prefix){
  charVal = val;
  frequency = NULL;
  left = NULL;
  right = NULL;
  prefixVal = prefix;
}



hNode::~hNode(){}
