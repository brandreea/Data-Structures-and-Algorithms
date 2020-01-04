#include <iostream>
#include <list>
#include <fstream>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");
class Graph
{
private:
    int V;
    list<int> *adj;
    void bridgeUtil(int u, bool visited[], int disc[],int low[], int parent[]);
    void APUtil(int u, bool visited[], int disc[],int low[], int parent[], bool ap[]);
public:
    Graph(int v);
    void addEdge(int u, int v);
    void bridge();
    void AP();
};
Graph::Graph(int v)
{
    this->V=v;
    adj=new list<int>[V+1];
    //cout<<V<<"\n";
}
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
    //cout<<"Added "<<u<<v<<"\n";
}
void Graph::bridgeUtil(int u, bool visited[], int disc[],int low[], int parent[])
{
    static int time=0;
    visited[u]=true;
    time++;
    disc[u]=time;
    low[u]=time;
    //cout<<"For node u:\n";
    for(std::list<int>::iterator it=adj[u].begin(); it!=adj[u].end();++it)
    {
        int aux=*it;
        //cout<<aux<<" ";
        if(!visited[aux])
        {
            parent[aux]=u;
            bridgeUtil(aux,visited,disc, low, parent);
            if(low[u]>low[aux])
                low[u]=low[aux];
            if(low[aux]>disc[u])
                fout<<u<<" "<<aux<<"\n";

        }
        else
        {
            if(aux!=parent[u])
                if(low[u]>disc[aux])
                low[u]=disc[aux];
        }
    }

}
void Graph::bridge()
{
    bool *visited=new bool[V+1];
    int *disc=new int[V+1];
    int *low=new int[V+1];
    int *parent=new int[V+1];

    for(int i=1;i<=V;i++)
    {
        parent[i]=-1;
        visited[i]=false;
    }
    for(int i=1;i<=V;i++)
        if(visited[i]==false)
        bridgeUtil(i,visited,disc,low,parent);

}
void Graph::APUtil(int u, bool visited[], int disc[], int low[], int parent[],bool ap[])
{
    static int time=0;
    visited[u]=true;
    time++;
    int children=0;
    disc[u]=time;
    low[u]=time;

    for(std::list<int>::iterator it=adj[u].begin();it!=adj[u].end();++it)
    {
        int aux=*it;
        if(!visited[aux])
        {
            children++;
            parent[aux]=u;
            APUtil(aux,visited,disc,low,parent,ap);
            if(low[u]>low[aux])
                low[u]=low[aux];
            //conditia 1:daca nu este radacina
            //conditia 2:??
            if(parent[u]==-1 &&children>1)
                ap[u]=true;
            if(parent[u]!=-1&& low[aux]>=disc[u])
                ap[u]=true;

        }
        else if(aux!=parent[u])
            if(disc[aux]<low[u])
            low[u]=disc[aux];
    }

}
void Graph::AP()
{
    bool *visited=new bool[V+1];
    bool *ap=new bool[V+1];
    int *parent=new int[V+1];
    int *low=new int[V+1];
    int *disc=new int[V+1];

    for(int i=1;i<=V;i++)
    {
        visited[i]=false;
        ap[i]=false;
        parent[i]=-1;
    }
    for(int i=1;i<=V;i++)
        if(!visited[i])
        APUtil(i,visited,disc,low,parent,ap);
    for(int i=1;i<=V;i++)
        if(ap[i])
            fout<<i<<"\n";
}
int main()
{
    int N,M;
    fin>>N>>M;
    Graph G(N);
    for(int i=0;i<M;i++)
    {
        int x,y;
        fin>>x>>y;
        G.addEdge(x,y);

    }
    fout<<"Muchii critice:\n";
    G.bridge();
    fout<<"Noduri critice:\n";
    G.AP();
    return 0;
}
