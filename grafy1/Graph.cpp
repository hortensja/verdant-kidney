#include "Graph.h"
#include "SuerpMatemateka.h"


Graph::Graph()
{
}

Graph::~Graph()
{
}

int Graph::getNumberOfVertices()
{
	return mVerticesList.size();
}

int Graph::getNumberOfEdges()
{
	int temp = 0;
	for (auto it = mAdjacencyMatrix.begin(); it != mAdjacencyMatrix.end(); ++it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			temp++;
		}
	}
	return (temp / 2);//for undirected graphs
}

int Graph::findVertex(Vertex *v)
{
	//returns position in mVerticesList of a vertex
	int i = 0;
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if ((*it).getVertexName() == v->getVertexName())
			return i;
		i++;
	}
	return -1;
}

int Graph::findVertex(std::string s)
{
	//returns position in mVerticesList of a vertex
	int i = 0;
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if ((*it).getVertexName() == s)
			return i;
		i++;
	}
	return -1;
}

bool Graph::isConnectedDirectly(Vertex *v1, Vertex *v2)
{
	int v1Position = v1->getVertexPosition();

	for (auto it = mAdjacencyMatrix[v1Position].begin(); it != mAdjacencyMatrix[v1Position].end(); ++it) {
		if ((*it).getVertexName() == v2->getVertexName())
			return true;
	}

	return false;
}

void Graph::addVertex(Vertex *v)
{
	if (this->findVertex(v) < 0) {
		v->setVertexPosition(mVerticesList.size());
		mVerticesList.push_back(*v);
		std::vector<Vertex> newV;
		mAdjacencyMatrix.push_back(newV);
	}
}

void Graph::addEdge(Vertex *v1, Vertex *v2)
{
	int v1Location = v1->getVertexPosition();
	int v2Location = v2->getVertexPosition();
	mAdjacencyMatrix[v1Location].push_back(*v2);
	mAdjacencyMatrix[v2Location].push_back(*v1);
}

void Graph::addEdge(std::string s1, std::string s2)
{
	int v1Location = this->findVertex(s1);
	int v2Location = this->findVertex(s2);
	mAdjacencyMatrix[v1Location].push_back(mVerticesList[v2Location]);
	mAdjacencyMatrix[v2Location].push_back(mVerticesList[v1Location]);
}

void Graph::printVertices()
{
	std::cout << "Vertices of a graph: \n";
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		(*it).printVertex();
		std::cout << std::endl;
	}
}

void Graph::printEdges()
{
	std::cout << "Edges of a graph: \n";
	int i = 0;
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		for (auto it2 = mAdjacencyMatrix[i].begin(); it2 != mAdjacencyMatrix[i].end(); ++it2) {
			std::cout << "[";
			(*it).printVertexNumber();
			std::cout << " , ";
			(*it2).printVertexNumber();
			std::cout << "]\n";
		}
		++i;
	}
}

void Graph::clearColours()
{
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		(*it).setVertexColour('\0');
	}
}

void Graph::clearDepths()
{
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		(*it).setDepthInDFS(0);
	}
}

void Graph::clearLowpoints()
{
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		(*it).setLowpoint(0);
	}
}

void Graph::clearParents()
{
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		(*it).setParent(nullptr);
	}
}

void Graph::clearGraph()
{
	this->clearColours();
	this->clearDepths();
	this->clearLowpoints();
	this->clearParents();
}

std::vector<Vertex> Graph::DFS(Vertex *v)
{
	std::vector<Vertex> dfsearchedVertices;

	std::vector<Vertex> verticesFound;

	this->clearGraph();

	dfsearchedVertices.push_back(*v);
	mVerticesList[v->getVertexPosition()].setVertexColour('d');
	std::cout << "First vertex : ";
	dfsearchedVertices.back().printVertex();
	std::cout << std::endl;

	int currDepth = 0;

	while (!dfsearchedVertices.empty()) {
		Vertex temp = dfsearchedVertices.back();
		temp.setDepthInDFS(++currDepth);
		mVerticesList[temp.getVertexPosition()].setDepthInDFS(currDepth);
		dfsearchedVertices.pop_back();
		verticesFound.push_back(temp);
		std::cout << "Now processing ";
		temp.printVertex();
		std::cout << std::endl;

		for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
			if (isConnectedDirectly(&temp, &(*it)) && !((*it).getVertexColour())) {
				dfsearchedVertices.push_back(*it);
				(*it).setVertexColour('d');
				//(*it).setDepthInDFS(++currDepth);
			}
		}
	}

	return verticesFound;
}

std::vector<Vertex> Graph::findArticulationPoints(Vertex *v, int depth, std::vector<Vertex> artPt)
{
	mVerticesList[v->getVertexPosition()].setVertexColour('a');
	mVerticesList[v->getVertexPosition()].setDepthInDFS(depth);
	mVerticesList[v->getVertexPosition()].setLowpoint(depth);

	int numberOfChildren = 0;
	bool isArticulationPoint = false;
	std::cout << "First vertex : ";
	mVerticesList[v->getVertexPosition()].printVertex();
	std::cout << std::endl;

	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if (isConnectedDirectly(v, &(*it))) {
			if (!((*it).getVertexColour())) {
				mVerticesList[it->getVertexPosition()].setParent(v);
				artPt = findArticulationPoints(&(*it), depth + 1, artPt);
				++numberOfChildren;
				if ((*it).getLowpoint()>=mVerticesList[v->getVertexPosition()].getDepthInDFS()) {
					isArticulationPoint = true;
				}
				mVerticesList[v->getVertexPosition()].setLowpoint(SuerpMatemateka::min(mVerticesList[v->getVertexPosition()].getLowpoint(), mVerticesList[it->getVertexPosition()].getLowpoint()));
			}
			else if (mVerticesList[v->getVertexPosition()].getParent()!=nullptr && (*it).getVertexName() != mVerticesList[v->getVertexPosition()].getParent()->getVertexName()){
				mVerticesList[v->getVertexPosition()].setLowpoint(SuerpMatemateka::min(mVerticesList[v->getVertexPosition()].getLowpoint(), mVerticesList[it->getVertexPosition()].getDepthInDFS()));
			}
		}
	}
	if ((mVerticesList[v->getVertexPosition()].getParent() != nullptr && isArticulationPoint) || (mVerticesList[v->getVertexPosition()].getParent() == nullptr && numberOfChildren>1)) {
		artPt.push_back(*v);
	}
	return artPt;
}


Graph Graph::sortVerticesViaDFS(Vertex *v)
{
	Graph gCopy = *this;
	gCopy.mVerticesList = DFS(v);
	for (auto it = gCopy.mVerticesList.begin(); it != gCopy.mVerticesList.end(); ++it) {
		gCopy.mAdjacencyMatrix[gCopy.findVertex(&(*it))] = this->mAdjacencyMatrix[it->getVertexPosition()];
	}
	return gCopy;
}

Graph Graph::createDFSTreeFromGraph(Vertex * v)
{
	Graph tree = this->sortVerticesViaDFS(v);



	return tree;
}
