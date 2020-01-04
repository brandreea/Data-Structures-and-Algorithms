#include <iostream>
#include <fstream>

#include <queue>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");
/*Se dă o matrice n*m (n,m <= 1000), cu p <= 100 puncte marcate cu 1 (restul valorilor din
matrice vor fi 0). Distanța dintre 2 puncte ale matricei se măsoară în locații străbătute mergând
pe orizontală și pe verticală între cele 2 puncte (distanța Manhattan). Se dă o mulțime M de q
puncte din matrice (q <= 1000000). Să se calculeze cât mai eficient pentru fiecare dintre cele q
puncte date, care este cea mai apropiată locație marcată cu 1 din matrice. (Licență iunie 2015)
*/
const int NMAX=15;
const int MMAX=15;
struct Point
{
    int x,y;
    bool index;
};
void BFS(bool a[20][20], int n, int m, Point st)
{
    queue<Point>q;
    q.push(st);
    cout<<"Start: "<<st.x<<" "<<st.y<<":\n";
    bool ok=false, viz[20][20];
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
        viz[i][j]=false;
    viz[st.x][st.y]=true;
    while(!ok)
    {
        Point aux=q.front(), temp;
       cout<<aux.x<<" "<<aux.y<<"\n";
        if(aux.index==true)
        {
            cout<<"temp is true";
            ok=1;
        }
        else
        {
            q.pop();
        if(!viz[aux.x+1][aux.y]&&aux.x<n)
        {
            temp=aux;
            temp.x++;
            temp.index=a[temp.x][temp.y];
            viz[temp.x][temp.y]=true;
            q.push(temp);
        }
        if(!viz[aux.x][aux.y+1]&&aux.y<m)
        {   temp=aux;
            temp.y++;
            temp.index=a[temp.x][temp.y];
            viz[temp.x][temp.y]=true;
            q.push(temp);
        }
        if(!viz[aux.x-1][aux.y]&&aux.x>1)
        {
            temp=aux;
            temp.x--;
            temp.index=a[temp.x][temp.y];
            viz[temp.x][temp.y]=true;
            q.push(temp);
        }
        if(!viz[aux.x][aux.y-1]&&aux.y>1)
        {
            temp=aux;
            temp.y--;
            temp.index=a[temp.x][temp.y];
            viz[temp.x][temp.y]=true;
            q.push(temp);
        }
        }
    }
    Point aux=q.front();
    q.pop();
    int mhdist;
    if(st.x<aux.x)
                mhdist=aux.x-st.x;
    else mhdist=st.x-aux.x;
    if(st.y<aux.y)
        mhdist=mhdist+aux.y-st.y;
    else mhdist=mhdist+st.y-aux.y;
        fout<<mhdist<<" ["<<aux.x<<" , "<<aux.y<<"]\n";
        while(!q.empty())
            q.pop();

}
int main()
{
    bool a[20][20];
    int n,m,qm=0;
    //Point q[400];
    fin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            fin>>a[i][j];
            cout<<a[i][j];
        }
    int x,y;
    cout<<qm;
    while(fin>>x>>y)
    {
        Point aux;
        aux.x=x;
        aux.y=y;
        aux.index=a[x][y];
        //cout<<aux.x<<" "<<aux.y<<"\n";
        BFS(a,n,m,aux);

    }
    return 0;
}
