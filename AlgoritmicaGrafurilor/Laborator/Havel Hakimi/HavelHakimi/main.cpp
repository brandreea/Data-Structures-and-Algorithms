#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
class Graph
{
private:
    int V;
    list<int> *adj;
public:
    Graph(int v);
    void addEdge(int u, int v);
    void show();

};
Graph::Graph(int v)
{
    V=v;
    adj=new list<int>[V+1];
}
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void Graph::show()
{
    for(int i=1;i<=V;i++)
    {
        for(std::list<int>::iterator a=adj[i].begin(); a!=adj[i].end();++a)
            if(*a>i)
            fout<<*a<<" "<<i<<"\n";
    }

}
bool sortbysec(const pair<int, int>&a, const pair<int, int>&b)
{
    return b.second<a.second;
}
void HavelHakimi(Graph &G, vector<pair<int,int> >deg, int V )
{
    bool isGraphic=true;
    for(int i=0;i<V ;i++)
    {
        for(int j=1;j<=deg[0].second && isGraphic;j++)
            {
                G.addEdge(deg[0].first,deg[j].first);
                cout<<"Added "<<deg[0].first<<" "<<deg[j].first<<"\n";
                deg[j].second--;
                if(deg[j].second<0)
                    {
                        isGraphic=false;
                    }
            }
        deg.erase(deg.begin());
        sort(deg.begin(), deg.end(), sortbysec);
        for(int i=0;i<deg.size();i++)
       {
           cout<<deg[i].second;
       }
       cout<<"\n";
    }
    if(isGraphic)
        G.show();
        else fout<<"isnot:(";
}

int main()
{
    int V;
    fin>>V;
    Graph G(V);
    vector<pair<int,int> >deg;
    for(int i=1;i<=V;i++)
    {
        int x;
        fin>>x;
        deg.push_back({0,x});
    }
    sort(deg.begin(), deg.end(), sortbysec);
    for(int i=0;i<deg.size();i++)
       {
           deg[i].first=i+1;
           cout<<deg[i].second<<deg[i].first<<"\n";
       }
    HavelHakimi(G,deg,V);
    return 0;
}
