//the edit distance between 2 words
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("edist.in");
ofstream fout("edist.out");
const int NMAX=20000;



int dif(char x, char y, int c)
{
	if (x == y) return 0;
	return c;
}
int d[2][NMAX + 2];
int main()
{
	int N, M, K;

	int c1, c2, c3;
	

	char s1[NMAX + 2], s2[NMAX + 2];
	fin >> s1 >> s2;
	N = strlen(s1);
	M = strlen(s2);
	fin >> c1 >> c2 >> c3;
	//boarding matrix
	for (int i = 0; i <= M; i++)
	{	
		d[0][i] = i;
	
	}
	d[0][0] = 0;
	d[1][0] = 1;

	
	//building matrix
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			d[1][j] = min(min(d[0][j] + c1, d[1][j - 1] + c2), d[0][j - 1] + dif(s1[i - 1], s2[j - 1],c3));
			
		}
		for (int j = 0; j <= M; j++)
			d[0][j] = d[1][j];
		d[1][0] = i;
	}
	
	
	fout << d[1][M];
	return 0;
}

