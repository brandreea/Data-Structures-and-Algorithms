//We are given a vector of n elements and a number q.
//An element v[i] is maximum point in v if:
//1)v[i-1]<v[i]>v[i+1] for 1<i<n
//2)v[i]>v[i+1] for i=1, v[i]>v[i-1] for i=n.
//What is the lenght of the longest sequence which contains exactly q maximum points?


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
const int NMAX = 5000;
int n, m, q;
int v[NMAX + 5];
ifstream fin("data.in");
int isMaxim[NMAX + 5][NMAX + 5];
int longestDecSeq[NMAX + 5];
//1->the only maximum length seqences ending in v[i] have v[i] as maximum point
//2->the only maximum length sequences ending in v[i] do not have it as maximum point
//3->we have found two distinct sequences, one for which v[i] is maximum point
//  and one for which it isn't, both of maximum length

int D[NMAX + 5][NMAX + 5];
void read()
{
	fin >> n >> q;
	for (int i = 0; i < n; i++)
		fin >> v[i];
}
void dpUtil()
{
	//yet another dp ::::)
	//at least works O(n^2) and doesn't ruin complexity
	//a dp subproblem for finding the longest increasing sequence that has v[i] as only maximum point 
        //this function is only used in initialising the first column of the matrix
        
	longestDecSeq[0] = 1;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (v[i] > v[j])
				longestDecSeq[i] = max(longestDecSeq[i], longestDecSeq[j] + 1);
	for (int i = 0; i < n; i++)
		cout << longestDecSeq[i] << " ";
	cout << "\n";

}
int dp()
{

	//init matrix
	dpUtil();
	D[0][0] = 1;
	isMaxim[0][0] = 1;
	for (int i = 1; i < n; i++)
	{	
		
		for (int j = i - 1; j >= 0; j--)
			if ((v[j] == v[i] &&isMaxim[j][0]!=1)||v[i]<v[j])
			{
				//cout << v[j] << ">" << v[i] << "\n";
				if (D[i][0] < D[j][0] + 1)
				{
					D[i][0] = D[j][0]+1;
					isMaxim[i][0] = 2;
				}
				else if (D[i][0] == D[j][0] + 1 && (isMaxim[i][0]==1 || isMaxim[i][0]==3))
				{
					
					isMaxim[i][0] = 3;
				}
				
			}
			else
			{
				
				//Finding the longest (not necessarily strictly)decreasing sequence for which v[i] is a maximum point
				int d = longestDecSeq[i];
				if (D[i][0] < d)
				{
					isMaxim[i][0] = 1;
					D[i][0] = d;
				}
				else if (D[i][0] == d &&(isMaxim[i][0] == 2 || isMaxim[i][0] == 3))
				{
					isMaxim[i][0] = 3;
				}
				
				
			}
			 
			
	}
	//actual dp
	for(int qi=1;qi<q;qi++)
		for (int i = 2*qi; i < n; i++)
		{	
			//case 1: v[i] is not a maximum point
			//search through the sequences already having qi maximums
			for (int j = i - 1; j >= 0; j--)
			{	//if v[i] can be added without modifying the number of maximums 
				if ((v[i] == v[j]&& isMaxim[j][qi] != 1)||v[i]<v[j])
				{	
					if (D[i][qi] < D[j][qi] + 1)
					{
						D[i][qi] = D[j][qi] + 1;
						isMaxim[i][qi] = 2;
					}
					else if (D[i][qi] == D[j][qi] + 1 &&(isMaxim[i][qi]==1 ||isMaxim[i][qi]==3))
					{
						isMaxim[i][qi] = 3;
					}
				}
			}
			//case 2: v[i] is a maximum point
			//search through the sequences only having qi-1 maximums
			for (int j = i - 1; j >= 0; j--)
				//if v[i] would be a maximum point and v[j] wasn't anyway
				if (v[i] > v[j] && isMaxim[j][qi - 1] != 1)
				{
					if (D[i][qi] < D[j][qi-1] + 1)
					{
						D[i][qi] = D[j][qi-1] + 1;
						isMaxim[i][qi] = 1;
					}
					else if (D[i][qi] == D[j][qi-1] + 1 && (isMaxim[i][qi] == 2 || isMaxim[i][qi]==3) )
					{
						isMaxim[i][qi] = 3;
					}

				}
		}
	
	for (int i = 0; i < n; i++)
	{
		for (int qi = 0; qi < q; qi++)
			cout << D[i][qi] << " ";
		cout << "\n";
		
	}
	//return maximum
	int maxim = INT_MIN;
	for (int i = 0; i < n; i++)
		if (D[i][q - 1] > maxim)
			maxim = D[i][q - 1];
	return maxim;
}
int main()
{
	read();
	cout << dp();
	return 0;
}

