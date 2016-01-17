#include "Graph.h"

Graph::Node::Node(std::string name, int x, int y)
{
	this->name = name;
	this->x = x;
	this->y = y;
}

Graph::Edge::Edge(int start, int end, int dist)
{
	this->start = start;
	this->end = end;
	this->dist = dist;
}

int Graph::addNode(std::string name, int x, int y)
{
	nodes.push_back(Node(name, x, y));
	
	return nodes.size()-1;
}

int Graph::addEdge(int start, int end, int dist)
{
	edges.push_back(Edge(start, end, dist));
	return edges.size()-1;
}

