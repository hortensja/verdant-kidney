#pragma once
class Vertex
{
public:
	Vertex(int n);
	Vertex(int n, char c);
	~Vertex();
	
	int getVertexNumber();
	char getVertexColour();
	int getDepthInDFS();
	int getLowpoint();
	Vertex * getParent();
	int getNumberOfChildren();


	void setDepthInDFS(int d);
	void setVertexColour(char c);
	void setLowpoint(int l);
	void setParent(Vertex *v);
	void setNumberOfChildren(int n);

	void printVertex();
	void printVertexNumber();


protected:
	int mVertexNumber;
	char mVertexColour;
	int mDepthInDFS;
	int mLowpoint;
	Vertex *mParent;
	int mNumberOfChildren;
	//int mParentNumber;
};

