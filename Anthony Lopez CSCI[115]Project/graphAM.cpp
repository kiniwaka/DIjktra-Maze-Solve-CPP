
#include "graphAM.h"
#include <iostream>
#include <queue>
using namespace std;
graphAM::graphAM()
{
	n = 0;
	M = nullptr;
	current = nullptr;

}
graphAM::graphAM(int num)
{
	n = num;
	M = new int[n * n];
	for (int i = 0; i < n * n; i++)
		M[i] = 0;
	current = new int[n];
	for (int i = 0; i < n; i++)
		current[i] = 0;
}
graphAM::~graphAM()
{
	delete[] M;
	delete[] current;
}
int graphAM::getIndex(int u, int v) //provides the index of the matrix which is represented as a 1d array 
{
	return u * n + v;
}
bool graphAM::existEdge(int u, int v)
{
	return (M[getIndex(u, v)] != 0);
}
int graphAM::getDegree(int u)
{
	int degree = 0;
	for (int v = 0; v < n; v++)
		if (existEdge(u, v))
			degree++;
	return degree;
}
void graphAM::setDirectedEdge(int u, int v, int w)
{
	M[getIndex(u, v)] = w;
}
void graphAM::setDirectedEdge(int u, int v)
{
	M[getIndex(u, v)] = 1;
}
void graphAM::setUndirectedEdge(int u, int v, double w)
{
	M[getIndex(u, v)] = w;
	M[getIndex(v, u)] = w;
}
void graphAM::setUndirectedEdge(int u, int v)
{
	M[getIndex(u, v)] = 1;
	M[getIndex(v, u)] = 1;
}
void graphAM::removeDirectedEdge(int u, int v)
{
	M[getIndex(u, v)] = 0;
}
void graphAM::removeUndirectedEdge(int u, int v)
{
	M[getIndex(u, v)] = 0;
	M[getIndex(v, u)] = 0;
}
bool graphAM::selfLoops()
{
	int u = 0;
	while (u < n)
	{
		if (M[getIndex(u, u)] != 0)
			return true;
		u++;
	}
	return false;
}
bool graphAM::isUndirecteted()
{
	int v, u = 0;
	while (u < n)
	{
		v = u;
		while (v < n)
		{
			if (M[getIndex(u, v)] != M[getIndex(v, u)])
				return false;
			v++;
		}
		u++;
	}
	return !selfLoops();
}
void graphAM::display()
{
	int x = 0;
	cout << " :";
	for (int v = 0; v < n; v++)
		cout << v << "\t";
	cout << endl;
	for (int u = 0; u < n; u++)
	{
		cout << u << ":";
		for (int v = 0; v < n; v++)
		{
			cout << M[x] << "\t";
			x++;
		}
		cout << endl;
	}

}
double graphAM::getWeight(int u, int v)
{
	return M[getIndex(u, v)];
}
void graphAM::BFS(int s)
{
	cout << "BFS" << endl;
	ColorNode* color;
	int* dist, * pi;
	BFSHelper(s, this, color, dist, pi);
	for (int u = 0; u < n; u++)
	{
		cout << "from " << s << " to " << u << " distance=" << dist[u] << " pi=" << pi[u] << endl;
	}
	delete[] color;
	delete[] dist;
	delete[] pi;
}
void graphAM::BFSHelper(int source, graphAM* G, ColorNode*& color, int*& dist, int*& pi)
{
	int n = G->getNumVertices();
	if (!((source >= 0) && (source < n)))
		cout << "source unusable" << endl;
	else
	{
		queue<int> Q;
		color = new ColorNode[n];
		dist = new int[n];
		pi = new int[n];
		for (int u = 0; u < n; u++)
		{
			color[u] = ColorNode::unvisited;
			dist[u] = 0;
			pi[u] = 0;
		}
		color[source] = ColorNode::visited;
		dist[source] = 0;
		pi[source] = 0;
		Q.push(source);
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			for (int v = 0; v < n; v++)
			{
				if (G->existEdge(u, v))
					if (color[v] == ColorNode::unvisited)
					{
						color[v] = ColorNode::visited;
						dist[v] = dist[u] + 1;
						pi[v] = u;
						Q.push(v);
					}
			}
			color[u] = ColorNode::finished;
		}
	}

}
void graphAM::setCurrentVertex(int u)
{
	current[u] = -1;
}
bool graphAM::getNextAdj(int u, int& out)
{
	int v = current[u] + 1;
	out = -1;
	bool found = false;
	while ((!found) && (v < n))
	{
		if (existEdge(u, v))
		{
			found = true;
			out = v;
		}
		v++;
	}
	current[u] = out;
	return found;
}
void graphAM::DFSVisit(int u, graphAM* G, ColorNode* color, int* discovery, int* finished, int* pi, int t)
{
	color[u] = ColorNode::visited;
	t++;
	discovery[u] = t;
	G->setCurrentVertex(u);
	int v;
	while (G->getNextAdj(u, v))
	{
		if (v != -1)
			if (color[v] == ColorNode::unvisited)
			{
				pi[v] = u;
				DFSVisit(v, G, color, discovery, finished, pi, t);
			}

	}
	color[u] = ColorNode::finished;
	t++;
	finished[u] = t;

}
void graphAM::DFS()
{
	cout << "DFS" << endl;
	ColorNode* color;
	int* discovery, * finished, * pi;
	DFSHelper(this, color, discovery, finished, pi);
	for (int u = 0; u < n; u++)
	{
		cout << u << ": (" << discovery[u] << ", " << finished[u] << " )  Pi=" << pi[u] << endl;
	}
}
void graphAM::DFSHelper(graphAM* G, ColorNode*& color, int*& discovery, int*& finished, int*& pi)
{
	int n = G->getNumVertices();
	color = new ColorNode[n];
	discovery = new int[n];
	finished = new int[n];
	pi = new int[n];
	for (int u = 0; u < n; u++)
	{
		color[u] = ColorNode::unvisited;
		discovery[u] = 0;
		finished[u] = 0;
		pi[u] = 0;
	}
	int t = 0;
	for (int u = 0; u < n; u++)
	{
		if (color[u] == ColorNode::unvisited)
			DFSVisit(u, G, color, discovery, finished, pi, t);
	}

}
void graphAM::Djikstra(int source, double*& d, int*& pi)
{
	d = new double[n];
	pi = new int[n];
	PQueue* pq = new PQueue(n);
	for (int u = 0; u < n; u++)
	{
		d[u] = DBL_MAX;
		pi[u] = -1;
	}
	d[source] = 0;
	for (int u = 0; u < n; u++)
		pq->push(u, d[u]);
	for (int i = 0; i < n; i++)
	{
		myData out = pq->pop();
		int u = out.index;
		setCurrentVertex(u);
		int v;
		while (getNextAdj(u, v))
		{
			double w = getWeight(u, v);
			if (d[v] > d[u] + w)
			{
				d[v] = d[u] + w;
				pi[v] = u;
				pq->decreaseKey(v, d[v]);
			}
		}
	}
	delete pq;

}