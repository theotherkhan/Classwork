// Hasan Khan
// hk4cd
// traveling.cpp


#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

#include "middleearth.h"

float computeDistance (MiddleEarth &me, string start, vector<string> dests);
void printRoute (string start, vector<string> dests);

/**
 *@brief Main method, finds shortest distance path between a given number of cities
 * This program creates a middle earth world with a certain size and number of cities. 
 * It creates an itinerary out of the given cities, removes the start city,
 * (so as to preserve it from being sorted), sorts the itinerary, and then calls while  
 * loop that loops through each possible permutation of that itinerary. For each possible
 * permutation, the total distance between its cities is calculated using the computeDistance()
 * method. The itinerary with the least distance is stored, and printed out using the printRoute()
 * method. The final routes distance is also printed.
 * @param argc The size of the char * array (number of command line parameters)
 * @param **argv The string of command line paramaters. Parameters include the world height,
 * the world width, the number of cities to create the world, the random seed, and the number 
 * of cities to visit from within the world.
 * @return 0
 * @see printRoute 
 * @see computeDistance
 */


int main (int argc, char **argv) {
    // check the number of parameters
    if ( argc != 6 ) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }
    // we'll assume the parameters are all well-formed
    int width, height, num_cities, rand_seed, cities_to_visit;
    sscanf (argv[1], "%d", &width);
    sscanf (argv[2], "%d", &height);
    sscanf (argv[3], "%d", &num_cities);
    sscanf (argv[4], "%d", &rand_seed);
    sscanf (argv[5], "%d", &cities_to_visit);
    // Create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);
    vector<string> finalRoute;  

    string startCity = dests[0];
    dests.erase(dests.begin()); // deletes the start city so that it isnt sorted each time


    sort(dests.begin(), dests.end()); // sorts the itinerary
    
    float tempDistance; // computes dest's total distance
    float minDistance = computeDistance(me, startCity, dests);
    finalRoute = dests;
    
    while (next_permutation(dests.begin(), dests.end())){  
    // loops through all possible itineraries
        tempDistance = 0.0;
        //cout << " New cities vector: " << endl; // prints new dests
        //printRoute (startCity, dests);   
        //cout << endl;
        tempDistance = computeDistance(me, startCity, dests); // computes dest's total distance
        //cout << "Current temp distance: "<< tempDistance << ", current minDistance: "<< minDistance << endl;  
        if (tempDistance < minDistance){
	  minDistance = tempDistance;
          finalRoute = dests;
          //cout << "New minimum distance: "<< minDistance <<endl;
	}
    } 
      
  
    cout << endl;
    cout<< "Minimum path distance: " << minDistance << ": ";
    printRoute(startCity, finalRoute);

    // YOUR CODE HERE
    return 0;
}
/**
 * @brief Computes distance for a given vector of cities
 * This method will compute the full distance of a vector of cities
 * that starts at the 'start' parameter, goes to each of the cities 
 * in the dests vector IN ORDER, and ends back at the 'start' parameter.
 * @param me The current middle earth world
 * @param start The starting city
 * @param dests The vector of cities for which we are computing the distance
 * @return temp Returns the total travel distance between the cities 
 */

float computeDistance (MiddleEarth &me, string start, vector<string> dests) {
  float temp = 0;
  for (int x = 0; x < dests.size()-1; x++)
	  temp += me.getDistance(dests[x], dests[x+1]);
  temp += me.getDistance(dests[0],start); // appends distance from first city to start  
  temp += me.getDistance(dests[dests.size()-1],start); // appends distance from last city to start
  return temp; 
        
}

/**
 *@brief Prints out route 
 * This method will print the entire route, starting and ending at the
 * 'start' parameter. Note that the start and end cities are the same, and
 * are passed and printed seperately since they are not included in dests.
 * The output will be in the form:
 * Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
 * @param start The starting city
 * @param dests The vector of cities which we are printing out
 */

void printRoute (string start, vector<string> dests) {
      
     cout << start << " -> "; 
     for (int x = 0; x < dests.size(); x++)
	  cout << dests[x]<< " -> ";
     cout << start; 

}
