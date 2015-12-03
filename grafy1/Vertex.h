#pragma once

#include <iostream>

class Vertex
{
public:
	Vertex(std::string n);
	Vertex(std::string n, char c);
	~Vertex();
	
	std::string getVertexName();
	int getVertexPosition();
	char getVertexColour();
	int getDepthInDFS();
	int getLowpoint();
	Vertex * getParent();
	int getNumberOfChildren();


	void setDepthInDFS(int d);
	void setVertexPosition(int p);
	void setVertexColour(char c);
	void setLowpoint(int l);
	void setParent(Vertex *v);
	void setNumberOfChildren(int n);

	void printVertex();
	void printVertexNumber();


protected:
	std::string mVertexName;
	int mVertexPosition;
	char mVertexColour;
	int mDepthInDFS;
	int mLowpoint;
	Vertex *mParent;
	int mNumberOfChildren;
	//int mParentNumber;
};

