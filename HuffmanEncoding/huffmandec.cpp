// Hasan Khan
// hk4cd 
// April 20
// huffmandec.cpp

// This program is the skeleton code for the lab 10 in-lab.  It uses
// C++ streams for the file input, and just prints out the data when
// read in from the file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "hNode.h"
#include <vector>
#include <string>

using namespace std;

bool rt = true;
bool lm = true;

void populateTree(hNode * carrier, string prefix, int prefixItr, int charint){ // populates huff tree recursively 
 
     if (prefixItr==prefix.size()){   
        carrier->charVal = charint; 
        cout << "Storing charVal:" << (char)carrier->charVal << endl;
        rt = false; 
        return;  
     } 

     if (prefix[prefixItr]=='0' && carrier->left == NULL && rt == true){
          hNode * midnode =  new hNode ();
	  carrier->left = midnode;
          //cout << "Wanna go left, and left is null. Create new left node" << endl;
          populateTree ( carrier->left, prefix, ++prefixItr, charint);
     }
     
     if (prefix[prefixItr]=='0' && carrier->left != NULL && rt == true){
          cout << "Wanna go left, and left is full. Recurse." << endl;
          populateTree ( carrier->left, prefix, ++prefixItr, charint);
     }
     
     if (prefix[prefixItr]=='1' && carrier->right == NULL && rt == true){
          hNode * midnode2 =  new hNode ();
	  carrier->right = midnode2;
          cout << "Wanna go right, and right is null. Create new right node." << endl;
          populateTree ( carrier->right, prefix, ++prefixItr, charint);
     }

     if (prefix[prefixItr]=='1' && carrier->right != NULL && rt == true){
          cout << "Wanna go right, and right is full. Recurse." << endl;
          populateTree ( carrier->right, prefix, ++prefixItr, charint);
     }
  }

void sp (int itr, hNode* slider,hNode * root, string allbits){  // decodes the message bit by bit using huffmantree

  while (lm == true){
    
    //cout << "Allbits size:" << allbits.size() << ", current prefix: " << (char)allbits[itr] << endl;
   
    if (itr ==  allbits.size())
      lm = false;
  
    if (slider->left==NULL && slider->right == NULL &&  itr != allbits.size()+1){
      cout << (char)slider->charVal;
      slider = root;
    }

    if (allbits[itr]=='0' && itr < allbits.size()){
      //cout << " Moving left " << endl;
      sp(++itr, slider->left,root,allbits);
    }

    if (allbits[itr]=='1'  &&  itr < allbits.size()){
      //cout << " moving right " << endl;
      sp(++itr, slider->right,root,allbits);
    }
  }
}


// main(): we want to use parameters
int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file; must be opened in binary
    // mode, as otherwise whitespace is discarded
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if ( !file.is_open() ) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    // read in the first section of the file: the prefix codes
  
    vector <string> prefixVec(128);

    while ( true ) {
        string character, prefix;
        // read in the first token on the line
        file >> character;
        // did we hit the separator?
        if ( (character[0] == '-') && (character.length() > 1) )
            break;
        // check for space
        if ( character == "space" )
            character = " ";
        // read in the prefix code
        file >> prefix;
        // do something with the prefix code
        cout << "character '" << character << "' has prefix code '"
             << prefix << "'" << endl;
        //--------------------------------------------------------------------------------       
        
        cout << "Storing prefix value of each character into vector, with vector index correspondinng to character ascII val" << endl;
        prefixVec[character[0]]= prefix; 
    
    }

    cout << " Creating huffmanTree... " << endl; // creates huffman tree here
    hNode * carrier;
    hNode * root;
    root = new hNode();
   
    
    for (int x = 0; x < prefixVec.size(); x++){
        if (prefixVec[x]!=""){
	    cout << " " << endl;
	    cout << "Inserting new node into tree..." << endl;
            rt = true;
	    carrier = new hNode('?',  prefixVec[x]);
            populateTree (root, prefixVec[x],0, x);        
	}
    }      
    cout << "TREE IS MADE !!!" << endl;
    // read in the second section of the file: the encoded message
    
     stringstream sstm;

    string temp= "";
  
    while ( true ) {
        string bits;
        // read in the next set of 1's and 0's
        file >> bits;
        // check for the separator
        if ( bits[0] == '-' ){
	  break;}

        // add it to the stringstream
        sstm << bits;
    }
    
    string allbits = sstm.str();
    cout << "All the bits: " << allbits << endl;
    string currentPref = "";
    string decoded = "";
    hNode * slider = root;
    int itr = 0;

    cout << "-------------------------------------------"<<endl;
    cout << "DECODED MESSAGE: " <<endl; 
    sp(itr, slider,root,allbits);
    cout << endl;   
   
    
    /* cout << "Tree prints: " << endl;
    cout << "Roots right right (d): " << (char) root->right->right->charVal << endl;
    cout << "Roots left (a): " << (char) root->left->charVal << endl;
    cout << "Roots right left right (c): " << (char) root->right->left->right->charVal << endl;
    cout << "Roots right left left (b) " << (char)root->right->left->left->charVal << endl;

    cout << endl;
    cout << "About to start decode "<< endl; */

 

  

    // at this point, all the bits are in the 'allbits' string
 
    // close the file before exiting

   
    file.close();

   }

// end program
