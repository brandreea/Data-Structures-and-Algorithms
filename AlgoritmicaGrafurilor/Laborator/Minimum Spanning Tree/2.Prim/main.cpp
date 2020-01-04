#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("grafpond.in");
ofstream fout("grafpon.out");
int minKey(int key[], bool tSet[], int V)
{
    int minim=INT_MAX, minI;
    for(int v=1; v<=V;v++)
        if(tSet[v]==false && key[v]<minim)
    {
        minim=key[v];
        minI=v;
    }
    return minI;

}
int printMST(int parent[], int graph[100][100], int V)
{
fout<<"Edge    Weight\n";
for (int i = 2; i <=V; i++)
    fout<< parent[i]<<" "<<i<<"   "<<graph[i][parent[i]]<<"\n";
}
void Prim(int graph[100][100], int V)
{
    int parent[V+1];
    int key[V+1];
    bool tSet[V+1];

    for(int i=1;i<=V;i++)
    {
        key[i]=INT_MAX;
        tSet[i]=false;
    }
    key[1]=0;
    parent[1]=-1;
    for(int i=1;i<=V-1;i++)
    {
        int u=minKey(key,tSet,V);
        tSet[u]=true;
        for(int v=0;v<=V;v++)
            if(graph[u][v] &&tSet[v]==false &&graph[u][v]<key[v])
        {
            parent[v]=u;
            key[v]=graph[u][v];
        }
    }
    printMST(parent,graph,V);
}
int main()
{
    int G[100][100];
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
        G[i][j]=0;
    int V,E;
    fin>>V>>E;
    for(int i=0;i<E;i++)
    {
        int x,y,c;
        fin>>x>>y>>c;
        G[x][y]=c;
        G[y][x]=c;
        cout<<"reading...\n";
    }
    Prim(G,V);
    return 0;
}
