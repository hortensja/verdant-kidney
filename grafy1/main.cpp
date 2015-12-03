#include "Vertex.h"
#include "Graph.h"


int main() {

	Graph *g = new Graph();

	/*Vertex *v1 = new Vertex(1);
	Vertex *v2 = new Vertex(2);
	Vertex *v3 = new Vertex(3);
	Vertex *v4 = new Vertex(4);
	Vertex *v5 = new Vertex(5);
	Vertex *v6 = new Vertex(6);
	Vertex *v7 = new Vertex(7);
	Vertex *v8 = new Vertex(8);
	Vertex *v9 = new Vertex(9);
	Vertex *v10 = new Vertex(10);*/

	Vertex **v = new Vertex*[10];

	for (size_t i = 0; i < 10; i++)
	{
		v[i] = new Vertex(i + 1);
		g->addVertex(v[i]);
	}

	/*g->addVertex(v1);
	g->addVertex(v10);
	g->addVertex(v8);
	g->addVertex(v7);
	g->addVertex(v5);
	g->addVertex(v6);
	g->addVertex(v2);
	g->addVertex(v3);
	g->addVertex(v9);
	g->addVertex(v4);*/

	g->addEdge(v[0], v[1]);
	g->addEdge(v[0], v[5]);
	g->addEdge(v[0], v[4]);

	g->addEdge(v[1], v[2]);
	g->addEdge(v[1], v[5]);

	g->addEdge(v[2], v[5]);
	g->addEdge(v[2], v[3]);
	g->addEdge(v[2], v[6]);

	g->addEdge(v[3], v[7]);

	g->addEdge(v[4], v[8]);
	g->addEdge(v[4], v[9]);

	g->addEdge(v[6], v[7]);

	g->addEdge(v[8], v[9]);

	//std::cout << v1.getVertexColour()<< std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	
	std::vector<Vertex> w;
	g->clearGraph();
	w = g->findArticulationPoints(v[0], 1, w);
	std::cout << "Sizeof result: " << w.size() <<  std::endl;
	std::cout << "Articulation points: " << std::endl;

	for (auto it = w.begin(); it != w.end(); ++it) {
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