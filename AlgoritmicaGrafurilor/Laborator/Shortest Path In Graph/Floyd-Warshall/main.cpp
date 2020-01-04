#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");
const int VALMAX=1005;

class Graph
{
private:
    int V;
    int adj[105][105];
public:
    Graph(int v);
    void addEdge(int u, int v, int c);
    void RoyFloyd();
};
Graph::Graph(int v)
{
    V=v;
    for(int i=1;i<=V;i++)
        for(int j=0;j<=V;j++)
        adj[i][j]=0;
}
void Graph::addEdge(int u, int v, int c)
{
    adj[u][v]=c;
    //adj[v][u]=c;
}
void Graph::RoyFloyd()
{
    //cout<<"Works";
    int roads[V+5][V+5];
    for(int i=1;i<=V;i++)
        for(int j=1;j<=V;j++)
        {
            roads[i][j]=adj[i][j];
            if(adj[i][j]==0 && i!=j)
                roads[i][j]=VALMAX;
        }
   for(int k=1;k<=V;k++)
        for(int i=1;i<=V;i++)
            for(int j=1;j<=V;j++)
                {
                    if(roads[i][k]+roads[k][j]<roads[i][j])
                        roads[i][j]=roads[i][k]+roads[k][j];
                }
    for(int i=1;i<=V;i++)
        {
            for(int j=1; j<=V;j++)
                fout<<roads[i][j]<<" ";
            fout<<"\n";
            }
}
int main()
{
    int v;
    fin>>v;
    cout<<v;

    Graph g(v);
    for(int i=1;i<=v;i++)
        for(int j=1;j<=v;j++)
    {
        int c;
        fin>>c;
        g.addEdge(i,j,c);
    }
    g.RoyFloyd();
    return 0;
}
