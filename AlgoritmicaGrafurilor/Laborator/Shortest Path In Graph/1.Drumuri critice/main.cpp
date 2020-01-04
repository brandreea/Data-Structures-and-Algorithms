//this is also dag algorithm
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
using namespace std;
ifstream fin("topsort.in");
ofstream fout("topsort.out");

class Graph
{
private:
    int V;
    list< pair<int, int> > *adj;
    void topSort(int u, bool viz[], stack<int> &St);
public:
    Graph(int v);
    void addEdge(int u, int v, int c);
    void longestPath(int st);
};
Graph::Graph(int v)
{
    V=v;
    adj=new list< pair<int, int> >[V+1];

}
void Graph::addEdge(int u, int v, int c)
{
    adj[u].push_back({v,c});
}
void Graph::topSort(int u, bool viz[], stack<int> &St)
{
    viz[u]=true;
    for(std::list< pair<int, int> >::iterator it=adj[u].begin();it!=adj[u].end();++it)
    {
        int x=(*it).first;
        if(!viz[x])
            topSort(x, viz, St);
    }
    St.push(u);

}
void Graph::longestPath(int st)
{
    stack<int> Stack;
    int d[V+1],t[V+1];
    bool *viz=new bool[V+1];

    for(int i=1;i<=V;i++)
        viz[i]=false;

    for(int i=1;i<=V;i++)
        if(viz[i]==false)
        {
            topSort(i,viz,Stack);
        }
    for(int i=1;i<=V;i++)
       {
           d[i]=-999999;
           t[i]=i;
       }
    d[st]=0;

    while(!Stack.empty())
    {
        int u=Stack.top();
        Stack.pop();
        if(d[u]!=-999999)
        for(std::list< pair<int, int> >::iterator it=adj[u].begin();it!=adj[u].end();++it)
        {
            int v=(*it).first;
            int c=(*it).second;
            if(d[v]<d[u]+c)
               {
                    d[v]=d[u]+c;
                    t[v]=u;
               }
        }

    }
    int minimi=0, minimv=0;
    for(int i=1;i<=V;i++)
        if(d[i]>minimv)
        {
            minimi=i;
            minimv=d[i];
        }
        int c=minimi;
    while(t[minimi]!=minimi)
    {
        fout<<minimi<<" ";

        minimi=t[minimi];
    }
    fout<<st<<"\n";
    for(int i=1;i<=V;i++)
    if(d[i]==-999999)
    fout<<"0 ";
    else
        fout<<d[i]<<" ";


}
int main()
{
    int v,e, *d;
    fin>>v;
    d=new int[v+1];
    //read duration
    Graph g(v);
    for(int i=1;i<=v;i++)
    {
        fin>>d[i];
    }
    //read edges
    fin>>e;
    for(int i=1; i<=e;i++)
    {
        int u,v;
        fin>>u>>v;
        g.addEdge(u,v,d[u]);
    }
    g.longestPath(1);
    delete[] d;
    return 0;
}
