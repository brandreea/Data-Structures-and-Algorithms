//SAT PROBLEM where p is a positive integrer x and n(p) is -x

#include <iostream>
#include <fstream>


using namespace std;

ifstream fin("sat.in");

int lit[10];
int clauses[10][10];
int n,nclause;
bool truthValues[10];

int module(int x)
{
	if (x < 0) return -x;
	return x;
}
void read()
{
	fin >> n;
	for (int i = 0; i < n; i++)
		fin >> lit[i];
	fin >> nclause;

	for (int i = 0; i < n; i++)
	{
		int nlit;
		fin >> nlit;
		for (int j = 1; j <= nlit; j++)
			fin >> clauses[i][j];

		clauses[i][0] = nlit;
	}
}
//generate next truth values
bool nextTruth()
{		
	
	int trace = 1, newdigit=0;
	for (int i = n - 1; i >= 1 && trace!=0; i--)
	{
		newdigit = (truthValues[i] + trace)%2;
		if (truthValues[i] + trace > 1)
			trace = 1;
		else trace = 0;
		truthValues[i] = newdigit;
	}
	if (trace > 0 && truthValues[0] == true)
	{
		return 0;
	}
	truthValues[0] = truthValues[0] + trace;
	return 1;

}
//testing the sat
void sat()
{
	
	bool ok = true;
	while (ok)
	{
		if (nextTruth())
		{
			bool p = true;
			
			for (int i = 0; p && i < nclause; i++)
			{
				bool s = false;
				for (int j = 1; s != true && j <= clauses[i][0]; i++)
					if (truthValues[module(clauses[i][j])] && clauses[i][j] > 0)
						s = true;
					else if (clauses[i][j] < 0 && !truthValues[module(clauses[i][j])])
						s = true;
				if (!s)
					p = false;

			}
			if (p)
			{
				cout << "SAT\n The truth values or each literal are:\n";
				for (int i = 0; i < n; i++)
					cout << "x" << i+1 << ": " << truthValues[i] << "\n";
				return;
			
			}


		}
		else ok = false;
	}
	cout << "UNSAT";

}
int main()
{
	read();
	sat();
	/*for (int i = 0; i < 4; i++)
	{
		nextTruth();
		for (int j = 0; j < n; j++)
			cout << truthValues[j] << " ";
		cout << endl;
	}*/
	return 0;
}


