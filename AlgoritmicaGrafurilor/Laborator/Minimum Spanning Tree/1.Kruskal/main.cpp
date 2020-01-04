#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpond.out");
struct Triplet
{
    int u, v,c;
    friend bool operator <(const Triplet &x, const Triplet &y)
    {
        return x.c<y.c;
    }
};

class Graph
{
private:
    int V,E;
    vector<Triplet > edges;
public:
    Graph(int v, int e);
    void addEdge(int u, int v, int w);
    int Kruskal();
};
Graph::Graph(int v, int e)
{
    this->E=e;
    this->V=v;
}
void Graph::addEdge(int u, int v, int w)
{
    edges.push_back({u,v,w});
}
class DisjointSets
{
    int *parent, *height;
    int n;
public:
    DisjointSets(int ne);
    int findSet(int u);
    void unionSet(int u, int v);

};
DisjointSets::DisjointSets(int ne)
{
    n=ne;
    parent=new int[n+1];
    height=new int[n+1];
    for(int i=0;i<=n;i++)
    {
        parent[i]=i;
        height[i]=0;
    }
}
int DisjointSets::findSet(int u)
{
    while(parent[u]!=u)
    u=parent[u];
    return parent[u];

}
void DisjointSets::unionSet(int u, int v)
{
    u=findSet(u);
    v=findSet(v);
    if(height[u]>height[v])
    {
        parent[v]=u;
    }
    else parent[u]=v;
    if(height[u]==height[v])
        height[v]++;
}
int Graph::Kruskal()
{
    sort(edges.begin(), edges.end());
    int wh=0;

    DisjointSets ds(V);

    for(std::vector<Triplet>::iterator it=edges.begin(); it!=edges.end();++it)
    {
        Triplet aux=*it;
        int u=aux.u;
        int v=aux.v;

        int setU=ds.findSet(u);
        int setV=ds.findSet(v);
        if(setU!=setV)
    {
        fout<<u<<" "<<v<<"\n";
        wh=wh+aux.c;
        ds.unionSet(setU,setV);

    }
    }

    return wh;
}
int main()
{
    int V,E;
    fin>>V>>E;
    Graph G(V,E);

    for(int i=0;i<E;i++)
    {
        int u, v, c;
        fin>>u>>v>>c;
        G.addEdge(u,v,c);
    }
    cout<<G.Kruskal();
    return 0;
}