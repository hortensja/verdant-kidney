#include "Vertex.h"
#include "Graph.h"


int main() {

	Graph *g = new Graph();

	Vertex **v = new Vertex*[10];

	for (size_t i = 0; i < 10; i++)
	{
		char *name = new char;
		*name = 'A' + i;
		std::string c(name);
		v[i] = new Vertex(c);
		g->addVertex(v[i]);
	}

	
	g->addEdge("A", "B");
	g->addEdge("A", "F");
	g->addEdge("A", "E");

	g->addEdge("B", "C");
	g->addEdge("B", "F");

	g->addEdge("C", "F");
	g->addEdge("C", "D");
	g->addEdge("C", "G");

	g->addEdge("D", "H");

	g->addEdge("E", "I");
	g->addEdge("E", "J");

	g->addEdge("G", "H");

	g->addEdge("I", "J");

	//std::cout << v1.getVertexColour()<< std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	
	std::vector<Vertex> w;
	g->clearGraph();
	w = g->findArticulationPoints(v[0], 1, w);
	std::cout << "Sizeof result: " << w.size() <<  std::endl;
	std::cout << "Articulation points: " << std::endl;

	for (auto it = w.begin(); it != w.end(); ++it) {
		(*it).printVertexNumber();
		std::cout << std::endl;
	}
	//Graph g2 = (g->sortVerticesViaDFS(v[0]));
	//g->sortVerticesViaDFS(v1).printVertices();
	g->printVertices();
	//g->printEdges();
	

	system("pause");
	return 0;
}