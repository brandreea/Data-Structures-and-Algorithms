//problem 4 in the pdf
//this is a GeeksForGeeks implementation
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin("data.in");
float min(float x, float y)
{
	return (x < y) ? x : y;
}

struct Punct
{
	int x, y;
};
Punct V[100];
Punct Vx[100];
Punct Vy[100];

int cX(const void* a, const void* b)
{
	Punct* p1 = (Punct*)a, * p2 = (Punct*)b;
	return (p1->x - p2->x);
}

int cY(const void* a, const void* b)
{
	Punct* p1 = (Punct*)a, * p2 = (Punct*)b;
	return (p1->y - p2->y);
}

float distance(Punct a, Punct b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
float stripIt(Punct strip[], int size, float d)
{
	float minim = d;
	for (int i = 0; i < size; ++i)
		for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minim; ++j)
			if (distance(strip[i], strip[j]) < minim)
				minim = distance(strip[i], strip[j]);

	return minim;
}
float bruteForce(Punct P[], int n)
{
	float minim = 9999999;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (distance(P[i], P[j]) < minim)
				minim = distance(P[i], P[j]);
	return minim;
}
float closest(Punct Px[], Punct Py[], int n)
{

	if (n <= 3)
		return bruteForce(Px, n);

	int med = n / 2;
	Punct midP = Px[med];



	Punct Pyl[100];
	Punct Pyr[100];

	int li = 0, ri = 0;
	for (int i = 0; i < n; i++)
	{
		if (Py[i].x <= midP.x)
			Pyl[li++] = Py[i];
		else
			Pyr[ri++] = Py[i];
	}


	float dst, ddr;
	dst= closest(Px, Pyl, med);
	ddr = closest(Px + med, Pyr, n - med);


	float dmin;
	dmin= min(dst, ddr);

	Punct strip[100];
	int k = 0;
	for (int i = 0; i < n; i++)
		if (abs(Py[i].x - midP.x) < dmin)
		{
			strip[k] = Py[i];
			k++;
		}


	return min(dmin, stripIt(strip, k, dmin));
}
int main()
{
	int n;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		int x,y;
		fin >> x>>y;
		V[i].x = x;
		V[i].y = y;
		Vx[i].x = x;
		Vx[i].y = y;
		Vy[i].x = x;
		Vy[i].y = y;

	}
	qsort(Vx, n, sizeof(Punct), cX);
	qsort(Vx, n, sizeof(Punct), cY);
	cout<<sqrt(closest(Vx, Vy,n));
	return 0;
}

