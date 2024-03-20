#pragma once
#include "PQueue.h"
enum class ColorNode
{
	visited,
	unvisited,
	finished
};
class graphAM
{
public:
	graphAM();
	graphAM(int n);
	~graphAM();
	int getNumVertices() { return n; }
	int getDegree(int u);
	int getIndex(int u, int v);
	bool existEdge(int u, int v);
	void setDirectedEdge(int u, int v, int w);
	void setDirectedEdge(int u, int v);
	void setUndirectedEdge(int u, int v, double w);
	void setUndirectedEdge(int u, int v);
	void removeDirectedEdge(int u, int v);
	void removeUndirectedEdge(int u, int v);
	bool selfLoops();
	bool isUndirecteted();
	void display();
	double getWeight(int u, int v);
	void setCurrentVertex(int u);
	bool getNextAdj(int u, int& out);
	void BFS(int s);
	void BFSHelper(int source, graphAM* G, ColorNode*& color, int*& dist, int*& pi);
	void DFS();
	void DFSVisit(int u, graphAM* G, ColorNode* color, int* discovery, int* finished, int* pi, int t);
	void DFSHelper(graphAM* G, ColorNode*& color, int*& discovery, int*& finished, int*& pi);
	void Djikstra(int s, double*& d, int*& pi);
private:
	int n;
	int* M; // matrix is represented as a 1d array of size n*n getindex is used to keep track of where each row starts and stops in the 1d array
	int* current; //used for traveseral purposes
};
