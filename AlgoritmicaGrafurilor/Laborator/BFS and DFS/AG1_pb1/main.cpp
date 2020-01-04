/*Se dă o rețea neorientată cu n noduri și o listă de noduri
reprezentând puncte de control pentru rețea. Se citește un nod de
la tastatură. Să se determine cel mai apropiat punct de control de
acesta și un lanț minim până la acesta O(n+m)*/
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");
const int NMAX=13;
const int MMAX=13;
int t[13];
bool viz[13];
void BFS(set<int>v[], int n, int m, int st)
{

    queue<int>q;
    q.push(st);
    viz[st]=1;
    while(!q.empty())
    {
        int aux=q.front();
        q.pop();
        cout<<aux<<" ";
        if(viz[aux]==false)
            viz[aux]=true;
        for(std::set<int>::iterator it=v[aux].begin();it!=v[aux].end();++it)
        {
            int x=*it;
            //cout<<x<<" ";
            if(viz[x]==false)
            {
                //cout<<"time to push...\n";
                viz[x]=true;
                q.push(x);
                t[x]=aux;
            }
        }
        //cout<<q.empty();

    }


}
int main()
{
    set<int>a[NMAX];
    int n,m;
    fin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y;
        fin>>x>>y;
        a[x].insert(y);
        a[y].insert(x);
    }
    int nt, tur[NMAX];
    fin>>nt;
    for(int i=0;i<nt;i++)
        fin>>tur[i];
    for(int i=1;i<=n;i++)
    {
        for(std::set<int>::iterator it=a[i].begin(); it!=a[i].end();++it)
            cout<<*it<<" ";
        cout<<"\n";
    }
    int nod;
    int minim=15,iminim=0;
    cin>>nod;
    BFS(a,n,m,nod);
    for(int i=0;i<nt;i++)
    {
        int num=0,p=tur[i];
        while(p!=nod)
        {
            p=t[p];
            num++;
        }
        if(num<minim)
        {
            minim=num;
            iminim=i;
        }

    }
    int p=tur[iminim];
    fout<<minim<<"\n";
    while(p!=nod)
    {
        fout<<p<<" ";
        p=t[p];
    }
    fout<<nod;
     for(int i=1;i<=n;i++)
    {
        a[i].clear();

    }

    return 0;
}
