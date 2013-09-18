#include "particleClass.h"
#include "reactorClass.h"
#include <iostream>
using namespace std;

void main()
{
	ReactorClass reactor;
	ParticleClass particle;
	LocationRec loc;
	cout << "Particle Class Test!\n\n";
	cout << "Test Default Constructor" << endl;

	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		cout << particle.GetEnergy(i) << "  ";
		cout << particle.IsActive(i) << "  ";
		cout << particle.GetPrevDir(i) << "  ";
		cout << particle.IsEscaped(i) << "  ";
		loc.row = rand() % 10;
		loc.col = rand() % 10;
		loc.dep = rand() % 10;
		particle.SetCurLoc(i,loc);
		cout << particle.GetCurLoc(i).row << " "
			<< particle.GetCurLoc(i).col << " "
			<< particle.GetCurLoc(i).dep << "  ";
		cout << endl;
	}

	particle.SetEnergy(85);

	cout << "Energy Set to 85 " << "Prevdir of Odd's To North" << endl;
	
	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		if(i % 2 != 0)
			particle.SetPrevDir(i,NORTH);
		cout << particle.GetEnergy(i) << "  ";
		cout << particle.IsActive(i) << "  ";
		cout << particle.GetPrevDir(i) << "  ";
		cout << endl;
	}

	bool core;
	cout << "Test Reactor Construction" << endl;
	for(int i = 0; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COL; j++)
		{
			for(int k = 0; k < MAX_DEP; k++)
			{
				loc.row = i;
				loc.col = j;
				loc.dep = k;
				core = reactor.IsCore(loc);
				cout << core << " ";
			}
			cout << endl;
		}
		cout<< endl;
	}

	cout << "\nBorn/Dead Methods\n\n";

	for(int i = 0; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COL; j++)
		{
			for(int k = 0; k < MAX_DEP; k++)
			{
				
				loc.row = i;
				loc.col = j;
				loc.dep = k;
				if(k%2 == 0)
					reactor.IncBorn(loc);
				cout << reactor.GetBorn(loc) << " ";
			}
			cout << endl;
		}
		cout<< endl;
	}
}