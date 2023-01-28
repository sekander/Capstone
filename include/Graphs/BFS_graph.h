// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
#include<bits/stdc++.h>
#include <box2d/box2d.h>
using namespace std;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
private:
	int V; // No. of vertices

	// Pointer to an array containing adjacency
	// lists
	vector<list<int>> adj;

	int vertexVisted = 0;

	vector<bool> visited;
	vector<int> vistedNodes = {};
public:
	Graph(int V)
	{
		this->V = V;
		adj.resize(V);
	}

	int getVertexVisited(){return vertexVisted;}
	vector<int> getVisitedNodes(){return vistedNodes;}
	vector<bool> getVisited(){return visited;}

	// function to add an edge to graph
	void addEdge(int v, int w)
	{
		adj[v].push_back(w); // Add w to v’s list.
	}

	// prints BFS traversal from a given source s
	void BFS(int s)
	{

		// Mark all the vertices as not visited
		visited.resize(V,false);

		// Create a queue for BFS
		list<int> queue;

		// Mark the current node as visited and enqueue it
		visited[s] = true;
		queue.push_back(s);

		while(!queue.empty())
		{	 
			// Dequeue a vertex from queue and print it
			s = queue.front();
			cout << s << " ";
			vistedNodes.push_back(s);
			queue.pop_front();

			// Get all adjacent vertices of the dequeued
			// vertex s. If a adjacent has not been visited,
			// then mark it visited and enqueue it
			for (auto adjecent: adj[s])
			{
				if (!visited[adjecent])
				{
					visited[adjecent] = true;
					queue.push_back(adjecent);
				}
			}
		}
		printf("\n");
	}
};

//Reference from 
// https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
