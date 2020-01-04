//given a set of cubes with color and edge dimension, build the highest tower considering that:
//no two cubes have the same edge dimension
//cube c1={col1, edge1} can be put above c2={col2,edge2} only if edge1<edge2 and col1!=col2

#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>

using namespace std;

ifstream fin("fisier.in.txt");

//structure for a cube
struct cub
{
	int culoare;
	int latura;
	int poz;
	//sort decreasinly according to edge
	friend bool operator > (const cub& a, const cub& b)
	{
		return a.latura > b.latura;
	}
};
int main()
{
	int x, y;
	//number of cuber, number of colors
	int n, p;
	fin >> n >> p;
	vector<cub>cuburi;
	for(int i=0;i<n;i++)
	{
		fin >> x >> y;
		cuburi.push_back({ y,x,i+1});
	}


	sort(cuburi.begin(), cuburi.end(),greater<cub>());
	 
	
	int lastcol=cuburi[0].culoare;
	
	//building solution
	vector<cub>solutie;
	int s = cuburi[0].latura;
	solutie.push_back(cuburi[0]);

	
	for (int i = 1; i < n; i++)
	{	
		//general step: add the first cube with a color different to the 
		//one of the last cube added
		if (lastcol != cuburi[i].culoare)
		{
			solutie.push_back(cuburi[i]);
			s = s + cuburi[i].latura;
			lastcol = cuburi[i].culoare;
		}

	}
	

	cout << solutie.size() << " " << s << "\n";
	for (int i = 0; i < solutie.size(); i++)
		cout << solutie[i].poz << " ";

	return 0;
}
