#pragma once

#include "Vertex.h"

#include <iostream>
#include <vector>

class Graph
{
public:
	Graph();
	~Graph();

	int getNumberOfVertices();
	int getNumberOfEdges();

	int findVertex(Vertex *v);
	bool isConnectedDirectly(Vertex *v1, Vertex *v2);

	void addVertex(Vertex *v);
	void addEdge(Vertex *v1, Vertex *v2);

	void printVertices();
	void printEdges();

	void clearColours();
	void clearDepths();
	void clearLowpoints();
	void clearParents();

	void clearGraph();

	std::vector<Vertex> DFS(Vertex *v);
	std::vector<Vertex> findArticulationPoints(Vertex *v, int depth, std::vector<Vertex> artPt);

	Graph sortVerticesViaDFS(Vertex *v);
	Graph createDFSTreeFromGraph(Vertex *v);

private:
	std::vector<Vertex> mVerticesList;
	std::vector<std::vector<Vertex>> mAdjacencyMatrix;
};

