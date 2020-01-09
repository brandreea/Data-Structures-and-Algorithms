//Let v be an array with n elements and let m and p (m>p>0) be two positive integers.
//What is the length of longest sequence s of numbers (ordered as in the initial array)
//such that any two consecutive numbers s[i] and s[i+1] respect the following condition:
//    -either (s[i]+s[i+1])%m=p or (|s[i]-s[i+1]|)%m=p 
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("data.in");

int n, m, p;
const int NMAX = 5000;
int v[NMAX + 5];
int D[NMAX + 5];
int t[NMAX + 5];
void read()
{
	fin >> n >> m >> p;
	for (int i = 0; i < n; i++)
		fin >> v[i];
}
void dp()
{
	for(int i=0;i<n;i++)
		for (int j = 0; j < i; j++)
		{
			if ((v[i]+ v[j]) % m == p || abs(v[j]-v[i])%m==p)
				D[i] = max(D[i], D[j] + 1);
		}
	for (int i = 0; i < n; i++)
		cout << D[i] << " ";
}
int main()
{
	read();
	dp();
	return 0;
}


