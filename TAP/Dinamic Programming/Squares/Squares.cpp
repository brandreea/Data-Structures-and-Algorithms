// We are given a matrix of dimensions n x m.
// the values in the matrix are either  1 or 0.
// what is the biggest dimension of a square (submatrix formed with elements that are adjacent
// verticaly, horizontaly or diagonaly) consisting only of 0s?

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("data.in");
int n,p;
const int NMAX = 5000;
int D[NMAX + 5][NMAX + 5];
int m[NMAX + 5][NMAX + 5];

void read()
{
	fin >> n>>p;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
		{
			fin >> m[i][j];
			if (m[i][j] == 1)
				D[i][j] = INT_MAX;
		}
}
void dp()
{	
	int maxim = INT_MIN;
	for(int i=n-1;i>=0;i--)
		for (int j = p-1; j >= 0; j--)
		{
			bool pos = true;
			if (D[i][j] != INT_MAX)

			{
				if (D[i][j + 1] == INT_MAX || D[i + 1][j] == INT_MAX || D[i + 1][j + 1] == INT_MAX)
					pos = false;
				if (pos)
					D[i][j] = min(D[i][j + 1], min(D[i + 1][j], D[i + 1][j + 1])) + 1;
				else D[i][j] = 1;
				if (D[i][j] > maxim)
					maxim = D[i][j];
			}
		}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p; j++)
			cout << D[i][j] << " ";
		cout << "\n";
	}
	cout << "Maxim: " << maxim;

}
int main()
{
	read();
	dp();
	return 0;
}


