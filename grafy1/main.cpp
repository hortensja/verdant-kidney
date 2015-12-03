#include "Vertex.h"
#include "Graph.h"


int main() {

	Graph *g = new Graph();

	Vertex *v1 = new Vertex(1);
	Vertex *v2 = new Vertex(2);
	Vertex *v3 = new Vertex(3);
	Vertex *v4 = new Vertex(4);
	Vertex *v5 = new Vertex(5);
	Vertex *v6 = new Vertex(6);
	Vertex *v7 = new Vertex(7);
	Vertex *v8 = new Vertex(8);
	Vertex *v9 = new Vertex(9);
	Vertex *v10 = new Vertex(10);

	g->addVertex(v1);
	g->addVertex(v10);
	g->addVertex(v8);
	g->addVertex(v7);
	g->addVertex(v5);
	g->addVertex(v6);
	g->addVertex(v2);
	g->addVertex(v3);
	g->addVertex(v9);
	g->addVertex(v4);

	g->addEdge(v1, v2);
	g->addEdge(v1, v6);
	g->addEdge(v1, v5);

	g->addEdge(v2, v3);
	g->addEdge(v2, v6);

	g->addEdge(v3, v6);
	g->addEdge(v3, v4);
	g->addEdge(v3, v7);

	g->addEdge(v4, v8);

	g->addEdge(v5, v9);
	g->addEdge(v5, v10);

	g->addEdge(v7, v8);

	g->addEdge(v9, v10);

	//std::cout << v1.getVertexColour()<< std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	
	std::vector<Vertex> v;
	g->clearGraph();
	v = g->findArticulationPoints(v1, 1, v);
	std::cout << "Rozmiar wyniku: " << v.size() <<  std::endl;

	for (auto it = v.begin(); it != v.end(); ++it) {
		(*it).printVertex();
		std::cout << std::endl;
	}/**/
	//Graph g2 = (g->sortVerticesViaDFS(v1));
	//g->sortVerticesViaDFS(v1).printVertices();
	g->printVertices();
	//g->printEdges();
	

	system("pause");
	return 0;
}