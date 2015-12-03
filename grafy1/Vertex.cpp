#include "Vertex.h"

#include <iostream>

Vertex::Vertex(int n)
{
	mVertexNumber = n;
	mVertexColour = '\0';
	mDepthInDFS = 0;
	mLowpoint = 0;
	mParent = nullptr;
}

Vertex::Vertex(int n, char c)
{
	mVertexNumber = n;
	mVertexColour = c;
	mDepthInDFS = 0;
	mLowpoint = 0;
	mParent = nullptr;
}


Vertex::~Vertex()
{
}

int Vertex::getVertexNumber()
{
	return mVertexNumber;
}

char Vertex::getVertexColour() {
	return mVertexColour;
}

int Vertex::getDepthInDFS()
{
	return mDepthInDFS;
}

int Vertex::getLowpoint()
{
	return mLowpoint;
}

Vertex * Vertex::getParent()
{
	return mParent;
}

int Vertex::getNumberOfChildren()
{
	return mNumberOfChildren;
}

void Vertex::setDepthInDFS(int d)
{
	mDepthInDFS = d;
}

void Vertex::setVertexColour(char c)
{
	mVertexColour = c;
}

void Vertex::setLowpoint(int l)
{
	mLowpoint = l;
}

void Vertex::setParent(Vertex * v)
{
	mParent = v;
}

void Vertex::setNumberOfChildren(int n)
{
	mNumberOfChildren = n;
}

void Vertex::printVertex()
{
	std::cout << mVertexNumber << " , coloured " << mVertexColour << " , depth: " << mDepthInDFS << " , low = " << mLowpoint;
}

void Vertex::printVertexNumber()
{
	std::cout << this->mVertexNumber;
}
