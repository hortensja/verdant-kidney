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
	int vPos = v->getVertexPosition();

	mVerticesList[vPos].setVertexColour('a');
	mVerticesList[vPos].setDepthInDFS(depth);
	mVerticesList[vPos].setLowpoint(depth);

	int numberOfChildren = 0;
	bool isArticulationPoint = false;
	std::cout << "Processing vertex : ";
	mVerticesList[vPos].printVertex();
	std::cout << std::endl;

	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if (isConnectedDirectly(v, &(*it))) {
			if (!((*it).getVertexColour())) {
				//push(stack, u, v)
				mVerticesList[it->getVertexPosition()].setParent(v);
				artPt = findArticulationPoints(&(*it), depth + 1, artPt);
				++numberOfChildren;
				if ((*it).getLowpoint()>=mVerticesList[vPos].getDepthInDFS()) {
					isArticulationPoint = true;
					//output
				}
				mVerticesList[vPos].setLowpoint(SuerpMatemateka::min(mVerticesList[vPos].getLowpoint(), mVerticesList[it->getVertexPosition()].getLowpoint()));
			}
			else if (mVerticesList[vPos].getParent()!=nullptr && (*it).getVertexName() != mVerticesList[vPos].getParent()->getVertexName()){
				mVerticesList[vPos].setLowpoint(SuerpMatemateka::min(mVerticesList[vPos].getLowpoint(), mVerticesList[it->getVertexPosition()].getDepthInDFS()));
			}
		}
	}
	if ((mVerticesList[vPos].getParent() != nullptr && isArticulationPoint) || (mVerticesList[vPos].getParent() == nullptr && numberOfChildren>1)) {
		artPt.push_back(*v);
	}
	return artPt;
}

std::vector<Vertex> Graph::biCompSearch(Vertex *v, int depth, std::vector<Vertex> biComp)
{
	int vPos = v->getVertexPosition();

	bool isOutputEligible = true;

	mVerticesList[vPos].setVertexColour('b');
	depth++;
	mVerticesList[vPos].setDepthInDFS(depth);
	mVerticesList[vPos].setLowpoint(depth);


	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if (isConnectedDirectly(v, &(*it))) {
			if (!((*it).getVertexColour())) {
				biComp.push_back(*v);
				biComp.push_back(*it);
				mVerticesList[it->getVertexPosition()].setParent(v);
				biComp = biCompSearch(&(*it), depth, biComp);
				if ((*it).getLowpoint() >= mVerticesList[vPos].getDepthInDFS()) {
					std::cout << "New biconnected component:\n";
					if (!biComp.empty()) {
						do {
							biComp.back().printVertexNumber();
							Vertex temp1 = biComp.back();
							std::cout << "->";
							biComp.pop_back();
							biComp.back().printVertexNumber();
							Vertex temp2 = biComp.back();
							biComp.pop_back();
							std::cout << "\t";
							if ((temp1.getVertexName() == v->getVertexName() && temp2.getVertexName() == it->getVertexName()) || (temp1.getVertexName() == it->getVertexName() && temp2.getVertexName() == v->getVertexName())) {
								isOutputEligible = false;
							}
						} while (isOutputEligible);
					}
					std::cout << std::endl;
					
				}
				mVerticesList[vPos].setLowpoint(SuerpMatemateka::min(mVerticesList[vPos].getLowpoint(), mVerticesList[it->getVertexPosition()].getLowpoint()));
			}
			else if (!(v->getParent()==&(*it)) && (v->getDepthInDFS()>it->getDepthInDFS())) {
				biComp.push_back(*v);
				biComp.push_back(*it);
				mVerticesList[vPos].setLowpoint(SuerpMatemateka::min(mVerticesList[vPos].getLowpoint(), mVerticesList[it->getVertexPosition()].getDepthInDFS()));
			}
		}
	}
	return biComp;
}

void Graph::findBiconnectedComponents()
{
	std::vector<Vertex> artPt;
	std::vector<Vertex> biComp;
	this->clearGraph();
	for (auto it = mVerticesList.begin(); it != mVerticesList.end(); ++it) {
		if (!(it->getVertexColour()))
			biComp = biCompSearch(&(*it), -1, biComp);
	}
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
