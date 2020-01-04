//Activities problem, with the restriction that each activity only last 1h (1 unit)
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("data.in.txt");


struct activitate
{
	int profit;
	int timp;
	int poz;
	//sort activities according to time
	friend bool operator >(const activitate& a, const activitate& b)
	{
		if (a.timp > b.timp)
			return 1;
		if (a.timp == b.timp)
			if (a.profit > b.profit)
				return 1;
		return 0;
	}
	//sort activities according to profit in priority queue
	friend bool operator <(const activitate& a, const activitate& b)
	{
		if (a.profit < b.profit)
			return 1;
		if (a.profit == b.profit)
			if (a.timp < b.timp)
				return 1;
		return 0;
	}
};
int main()
{
	int n;
	vector<activitate>A;
	int MAXHR = 0;
	fin >> n;
	int x, y;
	for (int i = 0; i < n; i++)
	{
		fin >> x >> y;
		if (y > MAXHR)
			MAXHR = y;
		A.push_back({ x,y,i + 1 });
	}
	//sortam 
	sort(A.begin(), A.end(),greater<activitate>());


	//store all activities eligible to be booked for the last hour
	//and that have not been paired up yet

	priority_queue<activitate >nealocate;
	vector<activitate>solutii;

	//last hour when an activity was booked
	int lasthr = A[0].timp;
	
	solutii.push_back(A[0]);
	int maxprof = A[0].profit;
	
	for (int i =1; i <n && lasthr>1; i++)
	{
		if (A[i].timp < lasthr)
		{
			//while there is a difference between the last booked hr and the current hr
			//book activities with highest profit

			while (lasthr > A[i].timp&& !nealocate.empty())
			{
				lasthr--;
				solutii.push_back(nealocate.top());
				nealocate.pop();
			}
			//add the current activity and repeat the process
			nealocate.push(A[i]);
			solutii.push_back(nealocate.top());
			maxprof = maxprof + nealocate.top().profit;
			nealocate.pop();
			lasthr--;
			
		}
		//if they are equal from the beginning, we are on an hour that is already booked
		//add in priority queue
		else nealocate.push(A[i]);
		
	}
	
	//if we still have hrs, book them
	while (lasthr > 1 && !nealocate.empty())
	{
		lasthr--;
		solutii.push_back(nealocate.top());
		nealocate.pop();
	}
	for (int i = 0; i<solutii.size(); i++)
		cout << solutii[i].poz << " ";
	return 0;
}