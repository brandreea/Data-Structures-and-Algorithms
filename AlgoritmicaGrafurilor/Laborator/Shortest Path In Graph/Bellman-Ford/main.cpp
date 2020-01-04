#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <climits>
using namespace std;

ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");
const int NMAX=50005;
const int MMAX=25005;
#define suplim INT_MAX/2;

class Graph
{
    int V;
    list< pair<int, int> > *adj;
    int *d,*viz;
    bool *inq;

public:
    Graph(int v);
    void addEdge(int u, int v, int c);
    void BellmanFord(int st);
    ~Graph();
};
Graph::Graph(int v)
{
    V=v;
    adj=new list< pair <int, int> >[V+3];

    d=new int[V+1];
    viz=new int[V+1];
    inq=new bool[V+1];

    for(int i=1;i<=V;i++)
    {
        d[i]=suplim;
        viz[i]=0;
        inq[i]=false;
    }

}
void Graph::addEdge(int u, int v, int c)
{

    adj[u].push_back({c,v});
}
void Graph:: BellmanFord(int st)
{
    set< pair<int, int> > Q;
    d[st]=0;
    Q.insert({d[st],st});
    inq[st]=true;

    bool negcycl=false;
    while(!Q.empty() &&!negcycl)
    {
        int u=Q.begin()->second;
        cout<<"Node is "<<u<<"\n";

        viz[u]++;
        cout<<"viz[u] is "<<viz[u]<<"\n";
        if(viz[u]>=V)
            negcycl=true;
        else
        {
            Q.erase(Q.begin());
            inq[u]=false;
            for(std::list< pair<int, int> >:: iterator it=adj[u].begin(); it!=adj[u].end();++it)
            {
                int v=(*it).second;
                int p=(*it).first;
                if(d[v]>d[u]+p)
                {
                    d[v]=d[u]+p;
                    if(!inq[v])
                        Q.insert({d[v],v});

                }
            }
        }

    }
    if(!negcycl)
    {
         for(int i=2;i<=V;i++)
        {
            fout<<d[i]<<" ";
        }
    }
    else
        fout<<"Ciclu negativ!";

}
Graph::~Graph()
{
    delete[] d;
    delete[] viz;
    delete[] inq;
}
int main()
{
    int v,e;
    fin>>v>>e;
    Graph g(v);

    for(int i=1;i<=e;i++)
    {
        int u,v,c;
        fin>>u>>v>>c;
        g.addEdge(u,v,c);
    }
    g.BellmanFord(1);
    return 0;
}
