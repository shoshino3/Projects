/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run BFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>

#include "util.h"



using namespace std;

void Dijkstra_output(char startV, graph &g, vector<char> &visited, vector<int> &distance, vector<char> &predV){
	
	cout << "Dijkstra: " ;
	
	for(char v1: visited) //printing out the visited vertices in Dijkstra's algorithm
		cout<< v1 << " ";
	cout << endl;
	
	for(char v:visited){
		vector<char> pre; 
		char pred = predV.at(v-'A');
		pre.push_back(v);
		
		while(pred != -1){
			pre.push_back(pred); //pushing back the vertices in the way of the path
			pred = predV.at(pred - 'A');
		}
		
		
		cout << v << " : " << distance.at(v-'A')<<" via ";
		
		for(int i = pre.size()-1; i >= 0; i--){
			 cout << pre.at(i) << " ";
		}

		cout << endl;
		}
	}



int main()
{
  graph  g;
  string filename;
  char   startV;
 
	

  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
 g.output();

  //
  // now ask user for a starting vertex, and run BFS as well as
  // strongly-connected algorithms:
  //
  cout << endl;
 cout << "Enter a starting vertex or #> ";
  cin >> startV;

  while (startV != '#')
  { 
    vector<char> visited;
	vector<char> visited_BFS;
	vector<char> visited_DFS;
	vector<char> adjV;
	vector<int> distance(26);
	vector<char> predV(26);
    //
    // BFS:
    //
    if (g.isvertex(startV))
    {
      BFS(g, startV, visited_BFS);
	  DFS(g, startV, visited_DFS);
	  adjV = g.neighbors(startV);
	  Dijkstra(startV, g, visited, distance, predV);
		
	  cout << "Neighbors: "; //printing out the neighbors of the vertex startV

      for (char v : adjV)
        cout << v << " ";

      cout << endl;
		

      cout << "BFS: "; //printing out the visited vertices in BFS algorithm

      for (char v : visited_BFS)
        cout << v << " ";

      cout << endl;
		
		cout << "DFS: "; //printing out the visited vertices in DFS algorithm

      for (char v : visited_DFS)
        cout << v << " ";

      cout << endl;
		
		
		Dijkstra_output(startV, g, visited, distance, predV); //calling the output function for Dijkstra's algorithm
		
		
		
	
    }
	  
	  
    else
    {
      cout << "Not a vertex in graph, ignored..." << endl;
    }

    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }
  /*vector<int>  keys = { 123, 456, 789, 1234, 5678, 91011 };
  char  initialValue = '#';
	

  minqueue<int, char> queue(keys, initialValue);
	
	queue.printHeap();
           
  cout<<(!queue.empty())<<endl;

  cout<< (queue.minfront() ==  123) << endl;
  queue.minpop();
	cout<< (queue.minfront() ==  456) << endl;
	queue.printHeap();
  queue.minpop();
	queue.printHeap(); //checking contents
 cout<< (queue.minfront() ==  789) << endl;
  queue.minpop();
  cout<< (queue.minfront() == 1234 ) << endl;
  queue.minpop();
 cout<< (queue.minfront() ==  5678) << endl;
  queue.minpop();
cout<< (queue.minfront() ==  91011) << endl;  
	queue.minpop();

  cout<<(queue.empty())<<endl;*/
  

  return 0;
}

