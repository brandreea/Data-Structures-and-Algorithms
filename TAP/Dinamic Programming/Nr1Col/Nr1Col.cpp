//let v be an array of n elements and let q be an integer.
//we define the weight of a sequence (v[i],v[i+1],...,v[j]) as wi=(v[i]-v[j])^2.
//we define a separator in an array as follows: k is separator if we have
//(v[1],...,v[k]) as one sequence and (v[k+1],...,v[n]) as another.
//we define the total weight of the array as the sum of all weights of the sequences defined by separaters in it.
//what is the minimum wight of a given array that has exactly q-1 separators?
//(i.e. q sequences)considering they are optimally chosen?

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int NMAX = 5000;
ifstream fin("data.in");
ofstream fout("data.out");
int n,k;
int v[NMAX + 5], D[NMAX+5][NMAX+5];
void read()
{
	fin >> n>>k;
	for (int i = 0; i < n; i++)
		fin >> v[i];
}
int pond(int x, int y)
{
	return (x - y) * (x - y);
}
int dp()
{
	int minim = INT_MAX;
	for (int i = 0; i < n; i++)
		for (int ki = 0; ki < k; ki++)
			D[i][ki] = INT_MAX;
	for (int i = 0; i < n-1; i++)
		D[i][0] = pond(v[0], v[i]) + pond(v[i + 1], v[n-1]);

	for (int ki =1; ki < k-1; ki++)
	{	
		
		for (int i = ki; i < n-1; i++)
		{
			int local_min = INT_MAX;
	
			for (int j = 0; j <i; j++)
			{
				if (D[j][ki - 1] != INT_MAX)
				{	
					
					int d = D[j][ki - 1] - pond(v[j + 1], v[n - 1]) + pond(v[j + 1], v[i]) + pond(v[i + 1], v[n - 1]);
					D[i][ki] = min(D[i][ki], d);
				}
			}
		
		}
	}

	for (int i = 0; i < n; i++)
		if (D[i][k - 2] < minim)
			minim = D[i][k - 2];

	return minim;
	
}
int main()
{
	read();

	fout << dp();
	return 0;
}


