// Hasan Khan
// hk4cd
// April 24, 2016


//! topological.cpp
/*! This program shows how C-based file I/O works.  It will open a
  file, read in the first two strings, and print them to the screen. */


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <set>
#include <vector>
#include <map>
#include <queue>
using namespace std;



/** @brief Returns the map key value of a give string
 *
 * This function returns a key value in a given for a given string
 * @return The key value 
 * @param map1 The map mapping
 * @param findThis The string who's key value we are trying to find
 */

int find(map <int, string> map1 , string findThis){

  for (int i = 0; i < map1.size(); i++){
        if (map1[i] == findThis) 
             return i;
  }
    return -1;
}


/** @brief Main method
 *
 * This method conducts topological sort on a given list of classes. First, reads in a given
 * text file with courses. Creates a set of courses. Creates a 2d adjacency matrix to represent
 * the "edges" between prequisite/requisite courses. Creates an inDegree vector that contains the 
 * inDegree of each course. Creates a map data structure that maps each course to a specific 
 * number. To topologically sort the courses, this method uses a queue, and traverses through the 
 * class tree based on inDegree values, printing courses as it goes.
 * @return 0 
 * @param **argv The char array of comman line inputs
 * @param argc The number of commands
 */

int main (int argc, char **argv) {

    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if ( !file.is_open() ) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    // read in two strings
    string s1, s2;   

    set <string> courses;
  
    while (s1 != "0"){
      file >> s1;
      file >> s2;
    
      //nodes * node1 = new node (s1);
      //nodes * node2 = new node (s2);
       
      courses.insert(s1);
      courses.insert(s2);
    }
    // string comparison done with ==, but not shown here
    // close the file before exiting
    //file.close();

    set<string>:: const_iterator position;
    map <int, string> mappings;
    int itr = 0;

  
    for (position = courses.begin(); position!=courses.end(); ++position){
      if (*position != "0"){
        //cout << *position << ' ';
	mappings[itr]=*position;
      }
      //cout<<endl;
      itr++;
    }

    int numNodes = courses.size();
    vector < vector <int> > aMatrix (numNodes, vector<int> (numNodes)); 
 
    //cout << "Initializing all aMatrix vals to 0..." << endl;
    for (int x = 0; x < numNodes; x++){    
      for (int y = 0; y < numNodes; y++){
	aMatrix[x][y]=0;
        //cout << aMatrix[x][y] << " " << endl;
      }
    }
    
    string s3;
    string s4;
    int key1, key2;
    
    //cout << " About to populate the aMatrix " << endl;
    file.clear();
    file.seekg(0);
    
    while (s3 != "0" || s4!="0"){
      file >> s3;
      file >> s4;

      if (s3 != "0"){
	//cout << "Strings: " << s3 << ", " << s4 <<endl;
	key1 = find(mappings,s3);
	key2 = find(mappings,s4);
        aMatrix[key1][key2]++;
        //cout << "Add edge between indices (" << key1 << ", " << key2 << ")"<< endl;
      }
      //  std::cout << x << std::endl;   
      // Inserting class courses into vector of strings    
    }

    // file.close();
    
    int currRow = 0;
    int currCol = 0;
    int infix = 0;
    vector <int> inDegree(numNodes);
    vector <int> haveEdge (numNodes);

    for (int x = 1; x < numNodes; x++){
      for ( int y = 1; y < numNodes; y++){
	inDegree[x] += aMatrix[y][x];
        haveEdge[x] += aMatrix[x][y];
	}
    }
      
     queue <int> visited;
     int counter = 0;
 
     for ( int x = 0; x < inDegree.size(); x++){  // 
         if (inDegree[x] == 0)
              visited.push(x);
     }

     int courser = -1;

     while (visited.empty()!=true) {
       courser = visited.front(); // current course is top of queue
       visited.pop();   // pop of top of queue
            
       cout << mappings[courser] << " ";

       for (int x = 0; x < numNodes; x++){    // search through neighbors of current course; add if their inDegree is 1
         if (aMatrix[courser][x]==1  && --inDegree[x] == 0){ 
           //cout << endl;    
	   //inDegree[x]--;
           //cout << "Pushing this course onto the queue: "<< mappings[x] << endl;  
           //cout << endl;
	   visited.push(x);

         }
       }
     }
     cout << endl;

     return 0;

}

   
