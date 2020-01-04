// BranchBound geeksforgeeks approach to knapsack problem
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("bb.in");

struct obj
{
	int v;
	float w;
	friend bool operator >(const obj& a, const obj& b)
	{
		double r1 = (double)a.v / a.w;
		double r2 = (double)b.v / b.w;
		return r1 > r2;
	}
};
struct node
{
	int level, profit,bound;
	float w;
};

vector<obj>o;
int n;
void read()
{
	fin >> n;
	obj aux;
	for (int i = 0; i < n; i++)
	{
		fin >> aux.w >> aux.v;
		o.push_back(aux);
	}
}
int bound(node N, int W)
{
	if (N.w > W) return 0;
	int profit_bound = N.profit, l=N.level+1,tWeight=N.w;

	while ((l < n) && tWeight + o[l].w <= W)
	{
		tWeight += o[l].w;
		profit_bound += o[l].v;
		l++;
	}

	if (l < n)
		profit_bound += (W - tWeight) * o[l].v /
		o[l].w;

	return profit_bound;
}
int rucksack(int W)
{
	sort(o.begin(), o.end(), greater<obj>());
	queue<node>Q;
	node u, v;
	u.level = -1;
	u.profit = u.w = 0;
	Q.push(u);

	int maxProfit = 0;
	while (!Q.empty())
	{
		u = Q.front();
		Q.pop();

		if (u.level == -1)
			v.level = 0;

		if (u.level == n - 1)
			continue;
		
		v.level = u.level + 1;
		v.w = u.w + o[v.level].w;
		v.profit = u.profit + o[v.level].v;

		if (v.w<= W && v.profit > maxProfit)
			maxProfit = v.profit;

		v.bound = bound(v,W);

		if (v.bound > maxProfit)
			Q.push(v);

		v.w = u.w;
		v.profit = u.profit;
		v.bound = bound(v,W);
		if (v.bound > maxProfit)
			Q.push(v);
	}

	return maxProfit;

}

int main()
{
	read();
	cout<<rucksack(10);
	return 0;
}
