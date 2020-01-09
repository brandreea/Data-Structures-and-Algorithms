//We have a project that takes a certain amount of time. Let n be that number of hours
//In order to finish the project, we can divide it into tasks.
//Let a, b and c be the number of hours required for very difficult, 
//mediumly difficult and not at all difficult tasks.
//What is the maximum number of consequent tasks that the project can be divided in?
//Note: we can use and infinite number of any of the three types of tasks.
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream fin("data.in");

const int NMAX=5000;
int n, a, b, c;
int D[NMAX+5];
int t[NMAX + 5];
void read()
{
	fin >> n >> a >> b >> c;
}
void dp()
{

	for (int i = 1; i <= n; i++)
		D[i] = -1;
	for (int i = 1; i <= n; i++)
	{
		if (i - a >= 0 && D[i - a] != -1)
			D[i] = max(D[i], D[i - a] + 1);
		if (i - b >= 0 && D[i - b] != -1)
			D[i] = max(D[i], D[i - b] + 1); 
		if (i - c >= 0 && D[i - c] != -1)
			D[i] = max(D[i], D[i - c] + 1);

	}
	cout<< D[n];
}
int main()
{	
	read();
	dp();
	return 0;
}


