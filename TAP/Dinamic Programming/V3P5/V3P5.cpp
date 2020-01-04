//two people are playing a game: out of a dequeue of numbers, alternatively
//they are making moves. a move consists of:
//either pop one number of the start/end of dequeue or both
//each player sums up the popped number. let's assume s1 is sum of player one, s2 sum of player 2.
//the one with the highr sum at the end wins
//both players can see all the numbers, but can only pop at the ends of the dequeue
//what is the minimum difference s1-s2 regardless of how player 2 moves
//considering that player 1 moves perfectly every time?
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin( "joculet.in");
ofstream fout("joculet.out");

vector<long long>input;

void read(int &n)
{
	fin >> n;

	for (int i = 0; i < n; i++)
	{
		int x;
		fin >> x;
		input.push_back(x);
	}
}

//2nd type of reccurence
//need to store the last two highest differences
int m[3][2001];
void pd(int n)
{	
	//case of one element
	if (n == 1)
	{
		fout << input[0];
		return;
	}
	//starting point
	for (int i = 0; i <n-1; i++)
	{
		m[0][i] = input[i];
		m[1][i] = max(input[i] - input[i + 1], input[i + 1] - input[i]);
	}
	m[0][n-1] = input[n-1];


	for (int l = 3; l <= n; l++) {
		//dp reccurence
		for (int i = 0; i< n - l + 1; i++) {
			m[2][i] = max(max(input[i] - m[1][i + 1], input[i + l - 1] - m[1][i]), input[i] + input[i + l - 1] - m[0][i + 1]);
		}

		//copy lines
		for (int i = 0; i <n; i++)
			m[0][i] = m[1][i];
		for (int i = 0; i <n; i++)
		{
			m[1][i] = m[2][i];
			m[2][i] = 0;
		}
	}
	fout << m[1][0];

}
int main()
{	

	int n;
	read(n);
	pd(n);

	return 0;
}
