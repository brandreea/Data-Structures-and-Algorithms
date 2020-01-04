//activities problem, but this time with various durations for each activity
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("data.in");

struct act
{
	int inc, sf, prof;
};
//sort according to ending hour
bool cmp(act a1, act a2)
{
	return (a1.sf < a2.sf);
}
struct sol
{
	int val, last;
};
vector<act>A;
int ult(int n, int index)
{
	int st = 0, dr = index - 1;
	while (st <= dr)
	{
		int mid = (st + dr) / 2;
		if (A[mid].sf <= A[index].inc)
		{
			if (A[mid + 1].sf <= A[index].inc)
				st = mid + 1;
			else
				return mid;
		}
		else
			dr = mid - 1;
	}

	return -1;

}
void pd(int n)
{
	sort(A.begin(), A.end(), cmp);
	sol dp[100];
	dp[0].val = A[0].prof;
	dp[0].last = 0;

	for (int i = 1; i < n; i++)
	{
		dp[i].last = i;
		int inc=A[i].prof;
		int ultim = ult(n,i);
		if (ultim != -1)
		{
			inc = A[i].prof + dp[ultim].val;
			
		}
		dp[i].val = max(inc, dp[i - 1].val);
		if (inc > dp[i - 1].val && ultim != -1)
		{
			dp[i].last = ultim;
		}
		else if(ultim!=-1)
		{ 
			dp[i].last = i-1;
			
		}
	

	}
	
	cout << dp[n - 1].val<<"\n";
	int k = n - 1;
	//finding a set of activities of maximum profit
	cout << A[k].inc << " " << A[k].sf << "\n";
	do
	{
		k = dp[k].last;
		while (k > 0 && dp[k].last == dp[k - 1].last)
			k--;

		cout << A[k].inc << " " << A[k].sf << "\n";

		
	} while (dp[k].last != k);
}
int main()
{	
	
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		act aux;
		fin >> aux.inc >> aux.sf >>aux.prof;
		A.push_back(aux);
	}
	pd(n);
	return 0;
}


