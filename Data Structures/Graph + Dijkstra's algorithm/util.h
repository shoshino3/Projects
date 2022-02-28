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

void buildGraph(string filename, graph& g);
void BFS(graph& g, char startV, vector<char> &visited);
void DFS(graph& g, char startV, vector<char> &visited);
void Dijkstra(char startV, graph &g, vector<char> &visited, vector<int> &distance, vector<char> &predV);
