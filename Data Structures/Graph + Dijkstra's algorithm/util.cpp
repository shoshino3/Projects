/*util.cpp*/
/*Kajimusugura Hoshino*/
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>
#include <limits>
#include "minqueue.h"
#include "graph.h"
//#include "util.h"



using namespace std;


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//

void buildGraph(string filename, graph& g)
{
   ifstream file(filename);

   if (!file.good())
   {
	cout << endl;
	cout << "**Error: unable to open input file '" << filename << "'." << endl;
	cout << endl;
	return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
   char V;
   file >> V;

   while(V != '#'){

	  g.addvertex(V);
	  file >> V;

   }
	char to;
	char from;
	int edge;

	file >> from;
	file >> to;
	file >> edge;


   while(from != '#'){ //adding edge weights for this graph

	  g.addedge(from,to,edge);
	  file >> from;
	  file >> to;
	  file >> edge;

   }
}


//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
void BFS(graph& g, char startV, vector<char> &visited)
{
  
  queue<char>   frontierQueue;
  set<char>     discoveredSet; //store in the vertices in the order that they were visited
   vector<char> adjV; //vector to hold the adjacent vertices of a vertex

  char currentV; 
  frontierQueue.push(startV); //pushing and inserting the starting vertex in the queue and the set respectively
  discoveredSet.insert(startV);
  while(!frontierQueue.empty()){ 

	 currentV = frontierQueue.front(); 
	 frontierQueue.pop();
	 visited.push_back(currentV); //pushing back the current vertex in a vector to keep track of the visited vertices
	 adjV = g.neighbors(currentV); //ajV vector stores all the adjacent vertices of the current vertex currentV

	 for(size_t i = 0; i < adjV.size(); i++){
		if(discoveredSet.find(adjV.at(i)) == discoveredSet.end()){ //if the vertex is not in the set, push and insert that vertex in queue and the set respectively
		   frontierQueue.push(adjV.at(i));
		   discoveredSet.insert(adjV.at(i));
		}}}

}

//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
void DFS(graph& g, char startV, vector<char> &visited)
{
  stack<char>   frontierStack; 
  set<char>     visitedSet; //store in the vertices in the order that they were visited
  vector<char>  adjV; // vector to hold the adjacent vertices of a vertex

  char currentV;

  frontierStack.push(startV); 
  while(!frontierStack.empty()){

	 currentV = frontierStack.top();
	 frontierStack.pop();
	 if(visitedSet.find(currentV) == visitedSet.end()){ //if the vertex is not in the set, 
		visited.push_back(currentV); //push that vertex in queue 
		visitedSet.insert(currentV); //insert that vertex in the set 
		adjV = g.neighbors(currentV); //get the neighbors of that vertex in a vector adjV
	   for(size_t i = 0; i < adjV.size(); i++){ //push each vertex adjV adjacent to currentV into the stack
		  frontierStack.push(adjV.at(i));
	   }
	 }
  }
}

void Dijkstra(char startV, graph &g, vector<char> &visited, vector<int> &distance, vector<char> &predV)
{
	//cout << "beginning of djink" << endl;
	minqueue<char, int> unQ(26);
	
	
	vector<char> gVertices = g.vertices(); //vector that holds all the valid vertices
	const int Infinity = numeric_limits<int>::max(); //initializing the variable Infinity with the maximum possible integer value
	
	//cout << "A" << endl;
	for(char currentV: gVertices)  
	{
		//cout << "B" << endl;
		distance.at(currentV - 'A') = Infinity; //for each vertex in gVertices vector, initializes its distance from the the starting vertex to Infinity and inserts into
											    //distance vector at a specific key index.
		predV.at(currentV - 'A') = -1;//for each vertex in gVertices vector, initializes the predecessor of each vertex to -1 and inserts it into predV vector at a specific key index
		unQ.pushinorder(currentV, Infinity);//for each vertex in gVertices vector, inserts the given (vertex, distance) pair into the queue such that 
											  // the pairs are stored in ascending order by value.
				//unQ.printHeap();							  // 
	}
	
	//unQ.printHeap();
	//cout << "C" << endl;
	 char curV;
	 distance.at(startV - 'A') = 0; //initializes the distance of the the starting vertex to 0 and inserts into distance vector at a specific key index
	 unQ.pushinorder(startV, 0); // inserts the starting vertex and its distance as a pair into the queue
		//unQ.printHeap();
	//unQ.printHeap();
	//cout << "D" << endl;
	 while(!unQ.empty()){
		 //unQ.printHeap();
		// cout << "E" << endl;
		 curV = unQ.minfront();
		 unQ.minpop();
		// cout << "F" << endl;
		// cout << "we are experiencing the problem in which we try to get distance.at(" << curV << " - 'A') which gives us " << (int)(curV - 'A') << endl;
		 if(distance.at(curV - 'A') == Infinity){ //breaks out of the loop if the distance of a particular vertex from the starting vertex is too far
			// cout << "brontasaurus" << endl;
			 break;
		 }
		 //cout << "G" << endl;
		 visited.push_back(curV); //vector that holds all the visited vertices in the path
		 
		 int edgeWeight, altPathDist;
		 
		 vector<char> gNeighbors = g.neighbors(curV);
		
		 for(char adjV: gNeighbors){
			// cout << "I" << endl;
			 edgeWeight = g.getweight(curV, adjV); //getting the edge weight of a pair of vertices
			 altPathDist = distance.at(curV - 'A') + edgeWeight; 
			 //cout << "J" << endl;
			  // If shorter path from startV to adjV is found,
             // update adjV's distance and predecessor
			 if(altPathDist < distance.at(adjV - 'A')){
				 //cout << "K" << endl;
				 distance.at(adjV - 'A') = altPathDist;
				 predV.at(adjV - 'A') = curV;
				 unQ.pushinorder(adjV, altPathDist);
				 //unQ.printHeap();
				// cout << "L" << endl;
			 }
			// cout << "M" << endl;
			 
		 }
	

		 //cout << "N" << endl;
	 }
	 
	//cout << "end djikstra" << endl;
	
}





