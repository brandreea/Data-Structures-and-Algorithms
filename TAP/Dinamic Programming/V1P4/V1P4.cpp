
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("data.in");
struct innt
{
	int val, valadd;
};
innt m[100][100];

int main()
{
	int n, k;
	fin >> n >> k;
	int ni[100];
	vector<vector<int> >v(n,vector<int>(0) );
	for (int i = 0; i < n; i++)
	{
		fin >> ni[i];
		for (int j = 0; j < ni[i]; j++)
		{
			int x;
			fin >> x;
			cout << "trying to push " << x << "...\n";
			v[i].push_back(x);
		}

	}

	//the dp matrix
	for (int j = 0; j < v[0].size(); j++)
	{
		m[0][v[0][j]].val = 1;
		m[0][v[0][j]].valadd = v[0][j];
		cout << m[0][v[0][j]].valadd;
	}
	for (int i = 1; i < n; i++)
	{
		//mark no
		/*for (int j = 0; j < v[i].size(); j++)
		{
			m[i][v[i][j]].val = 1;
			m[i][v[i][j]].valadd = v[i][j];
			cout << m[i][v[i][j]].valadd;
		}*/
		cout << "\n";
		if (i > 0)
		{
			//update sum using dp recurrence rule
			for (int j = 0; j < v[i].size(); j++)
			{
				for (int ki = 0; ki <=k; ki++)
				{
					if ( m[i-1][ki].val!=0 && (ki+v[i][j])<=k)
					{
						m[i][ki + v[i][j]].val= m[i - 1][ki].val + 1;
						if (m[i][ki + v[i][j]].val ==( m[i - 1][ki].val + 1))
							m[i][ki + v[i][j]].valadd = v[i][j];
					}

				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <=k; j++)
			cout << m[i][j].val<< " ";
		cout << endl;
	}
	if (m[n - 1][k].val == n)
	{
		cout << "DA";
		int j=k;
		for (int i = n - 1; i >= 0; i--)
		{
			cout << m[i][j].valadd << " ";
			
			j= j - m[i][j].valadd;
			cout << j << " \n";
		}
	}
	else cout << "NU";
	return 0;

}

