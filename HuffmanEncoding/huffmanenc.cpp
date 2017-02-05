// Hasan Khan
// hk4cd
// April 18
// huffmanenc.cpp


#include <iostream>
#include <stdlib.h>
#include <vector>
#include "hNode.h"
#include "heap.h"

using namespace std;

#include <stdio.h>



void encode(hNode * g, string prefix) // encode method, makes prefix tree
{
  //cout << "testing. g->charVal:  " << g->charVal << endl;
  if(g->left == NULL || g->right == NULL)
  {
    //cout  << "Char: " << g-> charVal << ", Bits: " <<  prefix << endl; 
    g->prefixVal = prefix; 
    return;
  }
 
  if (g->left!=NULL){
    //cout << " go left " << endl;
    encode(g->left, prefix + "0");
  }
  if (g->right!=NULL){
    //cout << " go right " << endl;
    encode(g->right, prefix + "1");
  } 
}

int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file.  FILE is a type desgined to
    // hold file pointers.  The first parameter to fopen() is the
    // filename.  The second parameter is the mode -- "r" means it
    // will read from the file.
    FILE *fp = fopen(argv[1], "r");
    // if the file wasn't found, output and error message and exit
    if ( fp == NULL ) {
        cout << "File '" << argv[1] << "' does not exist!" << endl;
        exit(2);
    }
    // read in each character, one by one.  Note that the fgetc() will
    // read in a single character from a file, and returns EOF when it
    // reaches the end of a file. 
    
    vector <int> frequencies (127);
    int currentChar;
    char g, j;
    vector <char> v;

// runs through the inputted file, store the frequency of each char into freq. vector
while ( (g = fgetc(fp)) != EOF ){
        cout << g;
        currentChar = (int)g;
       
        if (currentChar !=10)
              frequencies[currentChar]++;

	v.push_back(g);
}

 // create vector of nodes

char y; 
hNode * h;
hNode temp;
vector <hNode*> huffnodes;

 for (int i = 0; i < frequencies.size(); i++){

   if (frequencies[i]!=0){
      y = (char)i; 
      h = new hNode (frequencies[i],y);
      huffnodes.push_back(h);
      
   }
 }

 // input nodes into heap data structure

 heap heap1(huffnodes);
 //heap1.print();
 
 while ( heap1.heap_size != 1) // places frequencies vector into heap
   {
     char d = 'd'; 
     hNode * dummy;
    
     dummy = new hNode (0, d);
    
     dummy->left = heap1.deleteMin();
     dummy->right = heap1.deleteMin();
  
     dummy->frequency = (dummy->left->frequency)+(dummy->right->frequency);
     heap1.insert(dummy);
     
   }
 
 //cout << "Nice."<< endl;

 //heap1.print();
  
 string prefix = "";

 encode(heap1.findMin(), prefix); // encodes huffmanTree
 // cout << "Done encoding. Next phase: prints! " << endl;

 int dSymbols=0;  
 int oBits;
 int symbolNo = 0;
 double tCost = 0.0;
 double cRatio;
 double cBits=0.0;

 cout << "-----------------------------------" << endl;
 
 // Part 1: Prints out letters and their prefix

 //cout << "Part 1 printing: " << endl;

 for (int i = 0; i < huffnodes.size(); i++){
   
   if (huffnodes[i]->charVal < 128 && huffnodes[i]->charVal > 0){
     if (huffnodes[i]->charVal==32){
       cout << "space" << " " << huffnodes[i]->prefixVal << endl;
       dSymbols++;
     }
     else{
       cout << (char)huffnodes[i]->charVal << " " << huffnodes[i]->prefixVal << endl;
       dSymbols++;
     }
   }
 }

cout << "-----------------------------------" << endl;
 
 // Part 2: Printing encoded message

 for (int j = 0; j < v.size(); j++){
     for (int i = 0; i < huffnodes.size(); i++){
       if ((int)v[j] == huffnodes[i]->charVal){ 
	  symbolNo++;
          cout << huffnodes[i]->prefixVal << " ";
       }
   }
 }

 cout << endl; 
 

// Calculates treeCost and cBits  by looping through all the symbols, and  adding frequency of each symbol times the length of the prefix of that symbol
 //cout << " tcost calculations... " << endl;
   for (int d = 0; d < huffnodes.size(); d++){
     tCost = tCost + ((huffnodes[d]->frequency)*((huffnodes[d]->prefixVal).length()));
     cBits = cBits + ((huffnodes[d]->frequency)*((huffnodes[d]->prefixVal).length()));
  }
 
 cout << "-----------------------------------" << endl;

 oBits = symbolNo * 8;
 cRatio = (double)oBits/(double)cBits;
 tCost = tCost/symbolNo;

 cout << "There were a total of " << symbolNo << " symbols that are encoded" << endl;
 cout << "There are " <<  dSymbols << " distinct symbols used" << endl;
 cout << "There were "<< oBits << " bits in the original file " << endl;
 cout << "There were " << cBits << " bits in the compressed file" << endl;
 cout << "This gives us a compression ratio of " << cRatio << endl;;
 cout << "The cost of the Huffman tree is "<< tCost << " bits per character" << endl;

 fclose(fp);
 return 0;
         

//-----------------------------------------------------------------------------------------
}

