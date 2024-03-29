//References:
//Source: 210CT - Week 7 Advanced Task N#2 code
//Author: Kristiyan Stoyanov
//Source: 210CT - Week 8 Lecture Slides: Primm's Algorithm pseudo-code
//Author: Diana Hintea

#include "stdafx.h"
#include <string>
#include <iostream>
#include <deque>
#include <fstream>
#include <limits>

using namespace std;

//Write data to specified file location
void SaveBFSData(int data) {
	ofstream myfile;
	myfile.open("C:\Users\kriss\Desktop\BFS.txt");
	if (myfile.is_open()) {
		//cout << " Success ";
		myfile << data << " ";
	}
	else {
		cout << "Unable to open file \n";
	}
	myfile.close();
}

void SaveDFSData(int data) {
	ofstream myfile;
	myfile.open("C:\Users\kriss\Desktop\DFS.txt");
	if (myfile.is_open()) {
		//cout << " Success ";
		myfile << data << " ";
	}
	else {
		cout << "Unable to open file \n";
	}
	myfile.close();
}

//Adjacency List
class Vertex {
public:
	int value;
	int tw;

	//Vertices which can be reached from current one
	deque<Vertex*> connections;

	Vertex(int v) {
		this->value = v;
	}

	void display_connections() {
		if (!connections.empty()) {
			for (int i = 0; i < connections.size(); i++) {
				cout << connections[i] << " ";
			}
			cout << "\n";
		}
		else {
			cout << "Vertex has no edges incident to it. \n";
		}
	}
};

class Edge {
public:
	Vertex* start;
	Vertex* end;
	int cost;

	Edge(Vertex* start, Vertex* end, int cost) {
		this->start = start;
		this->end = end;
		this->cost = cost;
		start->connections.push_back(end);
	}
};

class GraphList {
public:
	deque<Vertex*> vertices;
	deque<Edge*> edges;

	GraphList(Vertex* v, Vertex* r = NULL) {
		this->vertices.push_back(v);
		if (r != NULL) {
			this->vertices.push_back(r);
		}
	}

	void insert_vertex(Vertex* v) {
		vertices.push_back(v);
	}

	void insert_edge(Vertex* start, Vertex* end, int weight) {
		//Undirected graph provides traversal of the same edge in reverse by the same cost (weight of the edge)
		edges.push_back(new Edge(start, end, weight));
		edges.push_back(new Edge(end, start, weight));
	}

	void display() {
		for (int i = 0; i < vertices.size(); i++) {
			cout << "Vertex: " << vertices[i]->value << " Edges: ";
			for (int j = 0; j < vertices[i]->connections.size(); j++) {
				if (vertices[i]->connections[j] != vertices[i]->connections.back()) {
					cout << vertices[i]->connections[j]->value << ", ";
				}
				else if (vertices[i]->connections[j] == vertices[i]->connections.back()) {
					cout << vertices[i]->connections[j]->value << "\n";
				}
			}
			cout << "\n";
		}
		cout << "\n";

		for (int i = 0; i < edges.size(); i++) {
			cout << "Edge: (Start: " << edges[i]->start->value << "), " << "(End: " << edges[i]->end->value << ") Cost: " << edges[i]->cost << "\n";
		}
	}
};

deque<Vertex*> dfs(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices;
		}
	}

	deque<Vertex*> stack;
	deque<Vertex*> visited;
	stack.push_back(v);
	while (!stack.empty())
	{
		Vertex* u = stack.back();
		stack.pop_back();
		if (!visited.empty()) {
			bool distinct = false;
			for (int i = 0; i < visited.size(); i++) {
				if (u != visited[i]) {
					distinct = true;
				}
				else {
					distinct = false;
					break;
				}
			}
			if (distinct) {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					stack.push_back(u->connections[i]);
				}
			}
		}
		else {
			visited.push_back(u);
			for (int i = 0; i < u->connections.size(); i++) {
				stack.push_back(u->connections[i]);
			}
		}
	}
	cout << "Depth-First Search: \n";
	for (int i = 0; i < visited.size(); i++) {
		SaveDFSData(visited[i]->value);
		cout << visited[i]->value << " ";
	}
	cout << "\n";
	return visited;
}

deque<Vertex*> bfs(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices;
		}
	}

	deque<Vertex*> queue;
	deque<Vertex*> visited;
	queue.push_front(v);
	while (!queue.empty()) {
		Vertex* u = queue.front();
		queue.pop_front();
		if (!visited.empty()) {
			bool distinct = false;
			for (int i = 0; i < visited.size(); i++) {
				if (u != visited[i]) {
					distinct = true;
				}
				else {
					distinct = false;
					break;
				}
			}
			if (distinct) {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					queue.push_back(u->connections[i]);
				}
			}
		}
		else {
			visited.push_back(u);
			for (int i = 0; i < u->connections.size(); i++) {
				queue.push_back(u->connections[i]);
			}
		}
	}
	cout << "Breadth-First Search: \n";
	for (int i = 0; i < visited.size(); i++) {
		SaveBFSData(visited[i]->value);
		cout << visited[i]->value << " ";
	}
	cout << "\n";
	return visited;
}

bool isPath(GraphList* g, Vertex* v, Vertex* w) {
	bool pathFound;
	deque<Vertex*> queue;
	for (int i = 0; i < v->connections.size(); i++) {
		queue.push_front(v->connections[i]);
	}
	while (!queue.empty())
	{
		Vertex* u = queue.front();
		queue.pop_front();
		if (u == w) {
			pathFound = true;
			cout << "Path is found \n";
			return pathFound;
		}
		else {
			pathFound = false;
		}
	}
	cout << "Path is not found \n";
	return pathFound;
}

bool isConnected(GraphList* g) {
	bool strConnected = false;
	deque<Vertex*> queue;
	//Individual queue for each vertex representing origin point of a bfs
	deque<Vertex*> indQueue;
	deque<Vertex*> visited;
	for (int i = 0; i < g->vertices.size(); i++) {
		queue.push_back(g->vertices[i]);
	}
	while (!queue.empty()) {
		indQueue.push_front(queue.front());
		queue.pop_front();
		while (!indQueue.empty())
		{
			Vertex* u = indQueue.front();
			indQueue.pop_front();
			if (!visited.empty()) {
				bool distinct = false;
				for (int i = 0; i < visited.size(); i++) {
					if (u != visited[i]) {
						distinct = true;
					}
					else {
						distinct = false;
						break;
					}
				}
				if (distinct) {
					visited.push_back(u);
					if (!u->connections.empty())
					{
						strConnected = true;
					}
					for (int i = 0; i < u->connections.size(); i++) {
						indQueue.push_back(u->connections[i]);
					}
				}
			}
			else {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					indQueue.push_back(u->connections[i]);
				}
			}
		}
	}

	if (strConnected) {
		cout << "Yes \n";
	}
	else {
		cout << "No \n";
	}
	return strConnected;
}

int findLongestCostSimplePath(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices.size();
		}
	}

	//Longest cost simple path variable storage for edge cost (weight) sum and number of verts
	int lcsp = 0;
	int lcspVerts = 1;

	//Visited vertices:
	deque<Vertex*> visited;

	//Alternative edges starting from current edge end point:
	deque<Edge*> altPaths;
	Edge* curEdge = NULL;
	int curEdgeCost = 0;

	//Find all alternative edges to follow from starting vertex
	for (int i = 0; i < g->edges.size(); i++) {
		if (g->edges[i]->start == v) {
			altPaths.push_back(g->edges[i]);
		}
	}

	//Locate most efficient edge to start from
	for (int i = 0; i < altPaths.size(); i++) {
		if (altPaths[i]->cost > curEdgeCost) {
			curEdgeCost = altPaths[i]->cost;
			curEdge = altPaths[i];
		}
	}

	visited.push_back(curEdge->start);
	lcsp += curEdge->cost;
	lcspVerts += 1;


	//Move the current edge until it has no further connections
	while (curEdge->end->connections.size() > 0) {

		//Clear alternative paths from last edge
		while (!altPaths.empty()) {
			altPaths.pop_back();
		}

		//Obtain alternative paths from this edge
		for (int i = 0; i < g->edges.size(); i++) {
			if (g->edges[i]->start == curEdge->end) {
				bool distinct = false;
				for (int j = 0; j < visited.size(); j++) {
					if (g->edges[i]->start != visited[j]) {
						distinct = true;
					}
					else {
						distinct = false;
						break;
					}
				}
				if (distinct) {
					altPaths.push_back(g->edges[i]);
				}
			}
		}

		//Locate most efficient edge to travel on
		curEdgeCost = 0;
		for (int i = 0; i < altPaths.size(); i++) {
			if (altPaths[i]->cost > curEdgeCost) {
				curEdgeCost = altPaths[i]->cost;
				curEdge = altPaths[i];
			}
		}

		visited.push_back(curEdge->start);
		lcsp += curEdge->cost;
		lcspVerts += 1;
	}

	cout << "Longest cost simple path is: " << lcsp << " (verts: " << lcspVerts << ") \n";
	return lcsp;
}

void dijkstra(GraphList* g, Vertex* source, Vertex* destination) {
	Vertex* v = source;
	for (int i = 0; i < g->vertices.size(); i++) {
		g->vertices[i]->tw = std::numeric_limits<int>::max();
	}
	source->tw = 0;

	Edge* curEdge;
	deque<Vertex*> visited;

	while (v != destination)
	{
		deque<Edge*> paths;
		Vertex* returnLoc;
		for (int i = 0; i < g->edges.size(); i++) {
			if (g->edges[i]->start == v) {
				paths.push_back(g->edges[i]);
			}
		}

		for (int i = 0; i < paths.size(); i++) {
			Vertex* u = paths[i]->end;
			if (v->tw + paths[i]->cost < u->tw) {
				u->tw = v->tw + paths[i]->cost;
				returnLoc = v; //return path
			}
		}
		visited.push_back(v);

		int min = std::numeric_limits<int>::max();
		for (int i = 0; i < v->connections.size(); i++) {
			Vertex* n = v->connections[i];
			bool distinct = false;
			for (int j = 0; j < visited.size(); j++) {
				if (n != visited[j]) {
					distinct = true;
				}
				else {
					distinct = false;
					break;
				}
			}
			if (distinct) {
				if (n->tw < min) {
					v = n;
					min = n->tw;
				}
			}
		}
	}
	cout << "\n";
	cout << "Start location: " << source->value << "\n";
	cout << "Destinatination reached: " << v->value << "\n";
	cout << "Cost: " << v->tw << "\n";
	cout << "Path traversed: ";
	for (int i = 0; i < visited.size(); i++) {
		if (visited[i]->connections.size() != 0) {
			cout << visited[i]->value << ", ";
		}
		else {
			cout << visited[i]->value << "\n";
		}
	}
}

void hamiltonianCycle(GraphList* g) {
	deque<Vertex*> reached;
	deque<Vertex*> unreached;
	int totalCost = 0;
	Vertex* curVertex = NULL;
	Edge* curEdge = NULL;
	deque<Vertex*> visited;
	deque<Edge*> curPaths;
	deque<Vertex*> availableSources;
	deque<deque<Vertex*>> traversalPaths;
	deque<int> gatheredCosts;
	bool unreachable = false;

	Edge* selectedEdge = NULL;
	Vertex* selectedVertex = NULL;
	deque<Edge*> spanningTree;

	//Find and select first vertex of graph vertices collection as origin/root for Minimum Cost Spanning tree construction
	/*
	if (!g->vertices.empty()) {
		selectedVertex = g->vertices[0];
	}

	//Start the process of completing a hamiltonian cycle with backtracking edges / Begin construction of a MCS Tree using Primm's algorithm
	//Allocate selected starting vertex as reached and every other vertex as unreached
	reached.push_back(selectedVertex);
	for (int i = 0; i < g->vertices.size(); i++) {
		if (g->vertices[i] != selectedVertex) {
			unreached.push_back(g->vertices[i]);
		}
	}
	//Attempt to reach all vertices using minimal edge cost/weight to complete the cycle
	while (unreached.size() != 0)
	{
		int minCost = std::numeric_limits<int>::max();
		for (int i = 0; i < g->edges.size(); i++) {
			bool foundStart = false;
			bool foundEnd = false;

			for (int a = 0; a < reached.size(); a++) {
				if (g->edges[i]->start == reached[a]) {
					foundStart = true;
					break;
				}
				else {
					foundStart = false;
				}
			}

			for (int b = 0; b < unreached.size(); b++) {
				if (g->edges[i]->end == unreached[b]) {
					foundEnd = true;
					break;
				}
				else {
					foundEnd = false;
				}
			}

			if (foundStart && foundEnd && g->edges[i]->cost < minCost) {
				minCost = g->edges[i]->cost;
				selectedEdge = g->edges[i];
			}
		}
		//Add the cost of the selected edge to the total cost required to complete the cycle and mark the end of the edge as reached
		totalCost += selectedEdge->cost;
		spanningTree.push_back(selectedEdge);
		reached.push_back(selectedEdge->end);
		for (int i = 0; i < unreached.size(); i++) {
			if (unreached[i] == selectedEdge->end) {
				unreached.erase(unreached.begin() + i);
				break;
			}
		}
	}

	//Print the order of vertices that were reached and the total cost of completing the cycle
	cout << "Cycle Complete \n";
	cout << "Traversal Path: ";
	for (int i = 0; i < reached.size(); i++) {
		cout << reached[i]->value << " ";
	}
	cout << "\n";
	cout << "Total cost: " << totalCost << "\n";*/

	//Start the process of completing a hamiltonian cycle without backtracking edges:
	//Obtain all available source locations for the cycle
	for (int i = 0; i < g->vertices.size(); i++) {
		availableSources.push_back(g->vertices[i]);
	}

	//Go through each available source location
	for (int a = 0; a < availableSources.size(); a++) {
		curVertex = availableSources[a];

		//Reset the previously acquired data in order to attempt to achieve a full cycle through the updated source vertex
		totalCost = 0;
		unreachable = false;
		while (!visited.empty())
		{
			visited.pop_back();
		}

		//Attempt to complete a full hamiltonian cycle starting from current vertex
		visited.push_back(curVertex);
		while (unreachable == false) {

			//Reset current available paths/edges from last vertex if any
			while (!curPaths.empty())
			{
				curPaths.pop_back();
			}

			//Find all current available paths/edges from current vertex
			for (int i = 0; i < g->edges.size(); i++) {
				if (g->edges[i]->start == curVertex) {
					if (visited.empty()) {
						curPaths.push_back(g->edges[i]);
					}
					else {
						bool distinct = false;
						for (int j = 0; j < visited.size(); j++) {
							if (g->edges[i]->end == visited[j]) {
								distinct = false;
								break;
							}
							else {
								distinct = true;
							}
						}
						if (distinct == true) {
							curPaths.push_back(g->edges[i]);
						}
					}
				}
			}

			//End current cycle traversal if no paths are available from current vertex
			if (curPaths.size() == 0) {
				unreachable = true;
			}
			else {
				//Find most efficient path to travel on
				int min = std::numeric_limits<int>::max();
				for (int i = 0; i < curPaths.size(); i++) {
					if (curPaths[i]->cost < min) {
						min = curPaths[i]->cost;
						curEdge = curPaths[i];
					}
				}
				curVertex = curEdge->end;
				totalCost += curEdge->cost;
				visited.push_back(curVertex);
			}
		}

		//Collect the path of all completed cycles and their traversal costs
		if (visited.size() == g->vertices.size()) {
			gatheredCosts.push_back(totalCost);
			traversalPaths.push_back(visited);
		}
	}

	//Obtain the smallest cost required to achieve a complete hamiltonian cycle
	int smallestCost = std::numeric_limits<int>::max();
	deque<Vertex*> optimalPath;
	for (int i = 0; i < gatheredCosts.size(); i++) {
		if (gatheredCosts[i] < smallestCost) {
			smallestCost = gatheredCosts[i];
			optimalPath = traversalPaths[i];
		}
	}

	//Print obtained data
	cout << "Cycle complete \n";
	cout << "All cycles: \n";
	for (int i = 0; i < traversalPaths.size(); i++) {
		cout << "Cost to complete: " <<  gatheredCosts[i] << "\n";
		for (int j = 0; j < traversalPaths[i].size(); j++) {
			cout << traversalPaths[i][j]->value << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	cout << "Optimal cycle: \n";
	cout << "Graph traversal order: ";
	for (int i = 0; i < optimalPath.size(); i++) {
		cout << optimalPath[i]->value << " ";
	}
	cout << "\n";
	cout << "Total Cost: " << smallestCost << "\n";
}

int main()
{
	//Adjacency List:
	GraphList* graph = new GraphList(new Vertex(6)); // [0]
	graph->insert_vertex(new Vertex(3)); // [1]
	graph->insert_vertex(new Vertex(9)); // [2]
	graph->insert_vertex(new Vertex(7)); // [3]
	graph->insert_vertex(new Vertex(5)); // [4]

	graph->insert_edge(graph->vertices[0], graph->vertices[1], 2);
	graph->insert_edge(graph->vertices[0], graph->vertices[3], 7);
	graph->insert_edge(graph->vertices[1], graph->vertices[2], 4);
	graph->insert_edge(graph->vertices[2], graph->vertices[3], 1);
	graph->insert_edge(graph->vertices[2], graph->vertices[4], 5);
	graph->insert_edge(graph->vertices[3], graph->vertices[4], 6);
	//graph->insert_vertex(b);
	//graph->insert_vertex(c);

	graph->display();
	cout << "\n";
	hamiltonianCycle(graph);
	//dijkstra(graph, graph->vertices[0], graph->vertices[4]);
	//dfs(graph, a);
	//bfs(graph, a);

	//isPath(graph, a, c);
	//findLongestCostSimplePath(graph);
	//isConnected(graph);
	//display_edges_incident_to(a);

	system("pause");
	return 0;
}
