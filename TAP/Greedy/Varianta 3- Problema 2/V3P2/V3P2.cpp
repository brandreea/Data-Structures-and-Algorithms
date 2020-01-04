//maximum subset of vertices that are not adiacent
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
using namespace std;

ifstream fin("data.in");

int toPrint[100];
int sumofAll[100];
vector<int>sol;


//in sumofALL keeps track of sums up untill now
class Graph
{
	int V;
	list<int>* adj;
public:
	Graph(int v) 
	{	V = v; 
		adj = new list<int>[V+1];
	};


	void addEdge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	//DFS to mark find the subset
	void DFSsumofall( int u, int dad)
	{
		if (adj[u].size()==1 && dad!=0)
		{	//mark leaves
			cout << "Marked " << u << " as good to go\n";
			toPrint[u] = 1;
			sumofAll[u] = 1;
			return;
		}
		if (sumofAll[u])
			return;
		int excl = 0, incl = 1;
		
		//calculate sum excluding the vertex
		//calculate the sum including the vertex
		//all vertexes with incl>excl are part of the set
		for (auto i : adj[u])
		{
				if (i == dad)
					continue;
				else
					DFSsumofall(i,u);
				excl = excl + sumofAll[i];
				for (auto j : adj[i])
				{
					if (j == u)
						continue;
					else
						DFSsumofall(j, i);
					incl = incl + sumofAll[j];
				}
		}
		if (incl > excl)
		{
			toPrint[u] = 1;
			sumofAll[u] = incl;
		}
		else sumofAll[u] = excl;

		
	}

	
	void print()
	{
		for (int i = 1; i <=V; i++)
			if (toPrint[i] == 1)
				cout << i << " ";
	}
	
};
int main()
{
	int v, e;
	fin >> v >> e;
	Graph G(v);
	for (int i = 0; i < e; i++)
	{
		int u, v;
		fin >> u >> v;
		G.addEdge(u, v);
	}
	G.DFSsumofall(1,0);
	G.print();

	return 0;
}
