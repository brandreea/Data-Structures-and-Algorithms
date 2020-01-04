#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");


class Graph
{
    int V;
    list<pair <int, int> > *adj;
    int d[50000], t[50000];

public:
    Graph(int v);
   void  addNode(int u, int v, int c);
    void Dijkstra(int st);
};
Graph::Graph(int v)
{
    V=v;
    adj=new list<pair <int, int> >[V+1];
    for(int i=1;i<=V;i++)
        {
            d[i]=999999;
            t[i]=0;
        }
}
void Graph::addNode(int u, int v,int c)
{
    adj[u].push_back({c,v});
}
void Graph::Dijkstra(int st)
{
    d[st]=0;
    bool viz[V+1];
    set< pair<int, int> > Q;
    Q.insert({d[st],st});
    viz[st]=true;
    while(!Q.empty() )
    {
        int x;
        x=Q.begin()->second;
        Q.erase(Q.begin());
        viz[x]=false;
            for(std::list< pair<int, int> >::iterator pr=adj[x].begin(); pr!=adj[x].end();pr++)
            {
                int v=(*pr).second;
                int c=(*pr).first;

                if(d[v]>d[x]+c)
                {
                   // Q.erase({d[v],v});
                    d[v]=d[x]+c;
                    t[v]=x;
                    if(!viz[v])
                    {
                        Q.insert({d[v],v});
                    viz[v]=true;}
                }
            }
    }
    for(int i=2;i<=V;i++)
    {
        if(d[i]==999999)
            d[i]=0;
     fout<<d[i]<<" ";
    }
    fout<<"\n";
}
int main()
{
    int n, m;
    fin>>n>>m;
    Graph G(n);

    for(int i=0;i<m;i++)
    {
      int x, y, p;
      fin>>x>>y>>p;
      G.addNode(x,y,p);
    }
    G.Dijkstra(1);
    return 0;
}
