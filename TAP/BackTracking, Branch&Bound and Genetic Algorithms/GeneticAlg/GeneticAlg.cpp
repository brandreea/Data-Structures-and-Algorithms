//genetic alg to determine the maximum of f function
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

ifstream fin("genetic.in");
ofstream fout("genetic.out");

int population_dim, precision, sequence_no;
double recombination_prob, mutation_prob;
double qi[30],pi[30],u[30];
bool selected[30];
vector<int>forMating;

struct domain
{
	double l, r;
} D;


struct Chromozome
{
	short int bit[24];
	double fit;
	double x;
	bool operator!=(const Chromozome& other)
	{
		for (int i = 0; i < 24; i++)
		{
			if (bit[i] != other.bit[i])
				return true;
		}
		return false;
	}
} current_population[30], next_generation[30];

//function to maximise
double f(double x)
{
	return -x*x + x + 2;
}
//reading data
void read()
{
	fin >> D.l >> D.r >> population_dim >> precision >> recombination_prob >> mutation_prob >> sequence_no;

}
//comverting a sequence of genes to a floating point number in the domain
double chromeToInt(Chromozome a)
{
	double aux= 0, p=1;
	for (int i = 0; i < 24; i++)
	{
		aux = aux + p * a.bit[i];
		p = p * 2;
	}
	double mid = (D.r -D.l);
	aux = aux*mid/ (double)16777216 +D.l;

	return aux;
}
//create initial population
void createPopulation()
{
	cout << "Initial population\n";
	for (int j = 0; j < population_dim; j++)
	{
		for (int i = 0; i < 24; i++)
		{
			int random = rand()+rand()%4;
			random = random % 2;
			current_population[j].bit[i] = random;
		}
		double val = chromeToInt(current_population[j]);
		current_population[j].fit = f(val);
		cout << j+1<< ": ";

		for (int i = 0; i < 24; i++)
			cout << current_population[j].bit[i];
		cout << " x= " << val << " f(x)=" << current_population[j].fit << "\n";
		current_population[j].x = val;
	}
	cout << "\n";
}
//utility fuction to sum fitness
double sumUtil()
{
	double s = 0;
		for (int i = 0; i < population_dim; i++)
			s = s + current_population[i].fit;
	return s;
}
//selection probability
void probChrom(int sq)
{	
	double s = sumUtil();
	if(sq==0)cout << "Selection Probability\n";
	for (int i = 0; i < population_dim; i++)
	{	
		pi[i] = (double)current_population[i].fit /(double)s;

		if (sq == 0)
		cout <<"cromozom "<<i+1<<": "<< pi[i]<<"\n";
	}

	if (sq == 0)
	cout << "\n";
}

void cumullativeProbabilities(int sq)
{	

	if (sq == 0)
	{
		cout << "Cumullative Probabilities:\n";
		cout << pi[0] << " ";
	}
	qi[0] = pi[0];
	for (int i = 1; i < population_dim; i++)
	{
		qi[i] = qi[i - 1] + pi[i];
		if(sq==0) cout << qi[i] << " ";
	}
	if(sq==0) cout << "\n";
}
//function to find a chromosome that satisfies probability requests
int findChromosome(double ui)
{	
	int r=population_dim-1, l=0, mid=0;
	bool found = false;
	while(r >= l &&!found) {
		mid = (r+ l) / 2;
		if (qi[mid] <= ui && ui<qi[mid+1])
		{
			 return mid;
		}
		if (qi[mid] > ui)
			r = mid - 1;
		else l=mid+1;
	}
	return mid;
}
//utility function to show data
void showPop()
{
	for (int j = 0; j < population_dim; j++)
	{
		cout << j + 1 << ": ";
		for (int i = 0; i < 24; i++)
			cout << current_population[j].bit[i];
		cout << " x= " << current_population[j].x << " f(x)=" << current_population[j].fit << "\n";
	}
	cout << "\n";
}
//generate the random u
void generateU(int sq)
{	
	unsigned short int ui;
	for (int i = 0; i < population_dim; i++)
	{
		ui = rand();
		double ui2=0;
		ui2 = ui*2/ (double)65536;
		int c = findChromosome(ui2);
		if(sq==0)cout << "u= " << ui2 << " selectam cromozomul " << c<<"\n";
		next_generation[i] = current_population[c];
		u[i] = ui2;
	}
	if (sq == 0)
	{
		cout << "Dupa selectie\n";

		showPop();
		cout << "\n";
		cout << "Probailitatea de incrucisare: " << recombination_prob << "\n";
	}
	
}
//selections
void pickChroms(int sq)
{	
	if (forMating.size() > 0)
	{
		forMating.clear();
	}
	generateU(sq);
	for (int j = 0; j < population_dim; j++)
	{
		if (sq == 0) {
			cout << j + 1 << ": ";
			for (int i = 0; i < 24; i++)
				cout << next_generation[j].bit[i];
			cout << " u=" << u[j];
		}
		if (u[j] < recombination_prob)
		{
			if(sq==0)cout << "<" << recombination_prob << " participa la incrucisare";
			forMating.push_back(j);
		}

		if(sq==0)cout << "\n";
	}
	//recombination
	if(sq==0)cout << "\nRecombinarea:\n";
	while(!forMating.empty())
	{
		for(int j=1;j<forMating.size();j++)
			if (next_generation[forMating[0]] != next_generation[forMating[j]])
			{
				int rand_cut = rand() % 24;
				short int aux;
				for (int k = 0; k <= rand_cut; k++)
				{
					aux = next_generation[forMating[0]].bit[k];
					next_generation[forMating[0]].bit[k] = next_generation[forMating[j]].bit[k];
					next_generation[forMating[j]].bit[k] = aux;
				}
				next_generation[forMating[0]].x = chromeToInt(next_generation[forMating[0]]);
				next_generation[forMating[j]].x = chromeToInt(next_generation[forMating[j]]);
				next_generation[forMating[0]].fit = f(next_generation[forMating[0]].x);
				next_generation[forMating[j]].fit = f(next_generation[forMating[j]].x);

				forMating.erase(forMating.begin() + j);
				
				break;
			}
		forMating.erase(forMating.begin());
	}
	if(sq==0)
	showPop();

}
//mutation
void mutate()
{	
	
	
	//cout << "Probabilitatea de mutatie " << mutation_prob << "\n";
	for (int i = 0; i < population_dim; i++)
	{
		bool modif = false;
		for (int j = 0; j < 24; j++)
		{	

			unsigned short int ui = rand();
			double ui2 = 0;
			ui2 = ui * 2 / (double)65536;

			if (ui2 < mutation_prob)
			{
				next_generation[i].bit[j] = 1 - next_generation[i].bit[j];
				modif = true;
			
			}
		}
		if (modif)
		{
			next_generation[i].x = chromeToInt(next_generation[i]);
			next_generation[i].fit = f(next_generation[i].x);
		}

	}

}
void maxim()
{	
	double m=INT_MIN;
	double s = 0;
	for (int i = 0; i < population_dim; i++)
	{
		if (next_generation[i].fit > m)
			m = next_generation[i].fit;
		s += next_generation[i].fit;
	}
	cout << m<<" "<<(double)s/population_dim<<"\n";



}
void GeneticAlg()
{
	for (int i = 0; i < sequence_no; i++)
	{
		//showPop();
		probChrom(i);
		cumullativeProbabilities(i);
		pickChroms(i);
		mutate();
		maxim();
		for (int j = 0; j < population_dim; j++)
			current_population[j] = next_generation[j];
	}
}
int main()
{
	
	read();
	createPopulation();
	GeneticAlg();
	
	return 0;
}

