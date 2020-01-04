//finding semnificative inversions in an array
//we consider a semnificative inversion between position i and j
//if V[i]>2*V[i]
//similar to merge sort

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("data.in");
vector<int>V;
int countInv(int st, int dr)
{
	if (st == dr)
		return 0;

	int nr = 0;
	//calculate inversions in each partition
	nr = nr + countInv(st, (st + dr) / 2);
	nr = nr + countInv((st + dr) / 2+1, dr);

	int i = st, j = (st+dr)/2+1;
	//calculate inversions between partitions
	while (i <= ((st + dr) / 2 + 1) && j <= dr)
	{
		if (V[i] > V[j] * 2)
		{
			nr = nr + (st + dr / 2) - i + 1;
			j++;
		}
		else i++;

	}

	i = st;
	j = (dr + st) / 2+1;
	vector<int>sorted;
	//sort them while counting 
	while(i<=(dr+st)/2 && j<=dr)
		
		{
			if (V[i] > V[j])
			{
				sorted.push_back(V[j++]);
			}
			else
				sorted.push_back(V[i++]);
		}
	while (i <= (st+dr)/2+1)
	{
		sorted.push_back(V[i++]);
	}

	while (j <= dr)
	{
		sorted.push_back(V[j++]);
	}
	int z = 0;
	for (int k = st; k <= dr; k++)
		V[k] = sorted[z++];
	return nr;

}
int main()
{
	int n;
	fin >> n;
	
	for (int i = 0; i < n; i++)
	{
		int x;
		fin >> x;
		V.push_back(x);
	}
	cout << countInv(0, V.size()-1);
	return 0;
}


