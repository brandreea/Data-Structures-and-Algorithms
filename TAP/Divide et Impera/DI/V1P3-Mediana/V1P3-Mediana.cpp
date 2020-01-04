//finding the median of two sorted arrays with distinct dimensions
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("data.in");

double findMedian(int v1[], int n, int v2[], int m)
{	
	
	double med=0;
	int st = 0, dr = n,i=0,j=0;
	//perform modified binary search on both vectors
	//looking forward to 2 cuts, one in each vector, such as 
	//all the elements on the right of the cuts are larger than the median
	//all the elements on the left of the cuts are smaller than the median
	while (st <= dr) 
	{
		i = (st + dr) / 2;
		j =( (n + m+1) / 2)-i;
		if (i < n && j>0 && v2[j - 1] > v1[i])
			st = i + 1;
		else
			if (i > 0 && j<m && v2[j]<v1[i - 1])
				dr = i - 1;
			else
			{
				if (i == 0)
					med = v2[j - 1];
				else 
				if (j == 0)
					med=v1[i - 1];
				else
				if (v1[i - 1] > v2[j - 1])
					med= v1[i - 1];
				else med= v2[j - 1];
				break;
			}
		


	}
	//test if the total number of elements is even
	if ((n + m) % 2==1)
		return med;
	if (i == n)
		return (med + v2[j]) / 2.0;
	if (j == m)
		return (med + v1[i]) / 2.0;
	if (v1[i] < v2[j])
		return med + v1[i];
	else return med + v2[j];

}
int main()
{	
	int m, n,v1[100],v2[100];
	fin >> n;
	for (int i = 0; i < n; i++)
		fin >> v1[i];
	fin >> m;
	for (int i = 0; i < m; i++)
		fin >> v2[i];
	if (n < m)
		cout << findMedian(v1, n, v2, m);
	else cout << findMedian(v2, m, v1, n);
	return 0;
}

