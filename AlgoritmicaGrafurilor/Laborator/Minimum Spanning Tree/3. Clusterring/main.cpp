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
    Graph(int v);
    void addEdge(int u, int v, int w);
    int Kruskal();
};
Graph::Graph(int v)
{
    this->E=0;
    this->V=v;
}
void Graph::addEdge(int u, int v, int w)
{
    edges.push_back({u,v,w});
    E++;
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
int Graph::Kruskal(char words[100][100])
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
        fout<<words[u]<<" "<<words[v]<<"\n";
        wh=wh+aux.c;
        ds.unionSet(setU,setV);

    }
    }

    return wh;
}
int distanta(char *s1, char *s2)
{
    int n1=strlen(s1);
    int n2=strlen(s2);
    int *ci1=new int[n2+1];
    int *ci=new int[n2+1];
    for(int j=0; j<=n2; j++)
        ci1[j]=j;
    for(int i=1; i<=n1; i++)
    {
        ci[0]=i;
        for(int j=1; j<=n2; j++)
            if(s1[i-1]==s2[j-1])
                ci[j]=ci1[j-1];
            else
                ci[j]=1+min(min(ci1[j],ci[j-1]),ci1[j-1]) ;
        for(int j=0; j<=n2; j++)
            ci1[j]=ci[j];
    }
    return ci[n2];
}
int main()
{
    int V,E;
    char words[100][100];
    int i=1;
    while(fin>>words[i])
        {
            if(words[i]!=" ")
                i++;
        }
    V=i;
    Graph G(V);
    for(int i=1;i<V;i++)
        for(int j=i+1;j<=V;j++)
    {
        int c=distanta(words[i], words[j]);
        G.addEdge(i,j,c);
    }
    int k=3;
    cout<<G.Kruskal(words);
    return 0;
}

