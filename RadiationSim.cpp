//Filename: RadiationSim.cpp
//Project: RadiationSim
//Author: Derek Gordon
//Date: 2/10/2012
//Statement of Purpose: 
//
//Input: The amount of particles that will be placed within the reactor
//	and the amount of energy each particle will have.
//
//Processing: The program will run a loop which on each pass through, given
//	there are still alive particles remaining within the reactor, will move
//	each particle 1 sq meter at a time and decrease energy accordingly to location
//	and amount of other inhabitants are within the same location.
//
//Output: The statistics for the amount born, remaining(dead), and escaped are outputted
//	for the reactor's statistics.  Then the particle's statistics will be outputted.
//	Including the location in which it died/escaped along with every location it has visited
//	more than once.
//
//Error Handling: All user inputs are tested to be valid numbers, if not user is asked to
//	reinput until correct values are obtained.
//
//Assumptions:
//	Maximum size of the reactor will be 15 x 15 x 15
//	Maximum number of particles will be 100
//	Maximum energy for a given particle is 100


#include "particleClass.h"	//for particles
#include "reactorClass.h"	//for reactor
#include <fstream>			//for file input/output
#include <iostream>			//for screen input/output
#include <iomanip>			//for formatting output
#include <string>			//for testing input
using namespace std;


void PlaceParticles(/* in */ ParticleClass& particle,	//particles to be placed
					/* in/out */ ReactorClass& reactor,	//reactor to be placed in
					/* in */ int particleNum);	//amount of particles in use
//Sets the initial positions of each particle within the core of the reactor

void MoveParticles(/* in */ ParticleClass& particle,	//particles to be placed
				   /* in */ ReactorClass& reactor,		//reactor to be placed in
				   /* in */ int particleNum);			//amount of particles in use
//Checks particles to make sure they are active and not escaped then moves the particles
//through the reactor once.

bool CheckStrForInt(/* in */ const char * str);//string inputted from cin
//	Checks what the user has inputted to make sure that it is a valid integer
//	before using it in the list.  Returns true if the inputted value is an integer, false otherwise

bool ParticlesLeft(/* in */ ParticleClass& particle,	//particles to be checked
				   /* in */ int particleNum);			//number of particles in use
//	Checks if there is still atleast 1 particle that has an energy > 0 and has not escaped the reactor.

void PrintSummary(/* in */ ParticleClass& particle,	//particles to be placed
				   /* in */ ReactorClass& reactor,		//reactor to be placed in
				   /* in */ int particleNum,			//amount of particles in use
				   /* out */ ostream& outFile);		//file to output to
//	Prints the summary of the particles lives within the reactor.
void main()
{
	//declare class objects
	ReactorClass reactor;	//3d array/nuclear reactor
	ParticleClass particle;	//to insert into reactor
	
	srand(987645321);

	ofstream outFile;
	string inNum;			//inputted value before being converted	
	int particleNum;		//amount of particles being used
	int energy;				//amount of energy each particle will have

	outFile.open("results.dat");

	outFile << "Cube: " << MAX_ROW << " X " << MAX_COL << " X " << MAX_DEP << endl;

	cout << "How Many Particles would you like to create: ";
	getline(cin, inNum);	//priming read

	particleNum = atoi(inNum.c_str());
	//if the user is inputting a value not within range
	while(!CheckStrForInt(inNum.c_str()) || (particleNum > MAX_PARTICLES || particleNum < 0))
	{
		//continue through the loop until a valid number is inputted
		system("cls");
		cout << "Invalid Amount\n How Many Particles would you like to create(1 to "
			<< MAX_PARTICLES << "): ";
		getline(cin, inNum);	//modify lcv
		particleNum = atoi(inNum.c_str());
	}//end while
	outFile << particleNum << " Particles with ";
	cout << "How much energy should the particles have: ";
	getline(cin,inNum);	//priming read
	energy = atoi(inNum.c_str());
	//if user is trying to set an invalid energy
	while(energy > MAX_ENERGY || energy <= 0)
	{
		//continue through loop until valid energy is inputted
		system("cls");
		cout << "Invalid Amount\n How much energy should the particles have(1 to "
			<< MAX_ENERGY << "): ";
		getline(cin,inNum);	//priming read
		energy = atoi(inNum.c_str());
	}//end while

	particle.SetEnergy(energy);
	outFile << energy << " Energy" << endl << endl;

	//place particles at initial location
	PlaceParticles(particle, reactor, particleNum);

	//continue to move all active particles until they
	// have all escaped or died.
	while(ParticlesLeft(particle, particleNum))
		MoveParticles(particle, reactor, particleNum);

	//now that all particles have escaped or died. Print the stats of
	//the particles and reactor.
	PrintSummary(particle, reactor, particleNum,outFile);
	
	//close file output printed to
	outFile.close();

}//end main

/*****************************************************************************************/

//Pre: particle and reactor classes have been initialized
//	the amount of particles have been specified
//Post: The particles are placed in their starting positions within the core
//Purpose: to place the particles in their starting positions in the core of the reactor
void PlaceParticles(/* in */ ParticleClass& particle,	//particles to be placed
					/* in */ ReactorClass& reactor,		//reactor to be placed in
					/* in */ int particleNum)
{
	LocationRec loc;	//location within the reactor
	for(int i = 0; i < particleNum; i++)
	{
		//Generate start locations within the core only
		loc.row = (rand() % (MAX_ROW - (SHIELD_SIZE * 2)) + 2);
		loc.col = (rand() % (MAX_COL - (SHIELD_SIZE * 2)) + 2);
		loc.dep = (rand() % (MAX_DEP - (SHIELD_SIZE * 2)) + 2);
		particle.SetCurLoc(i, loc);	//set current location to loc
		reactor.IncBorn(loc);		//increment amount born in that current loc
		reactor.IncOccupants(loc);	//increment occupants for that specific loc
	}//end for
}//End PlaceParticle

/*****************************************************************************************/

//Pre: particle and reactor classes have been initialized
//	the amount of particles have been specified
//Post: All active(alive and !escaped) particles move 1 sq meter
//	throughout the reactor
//Purpose: To move all active particles 1 sq meter through the reactor
void MoveParticles(/* in */ ParticleClass& particle,	//particles to be placed
				   /* in */ ReactorClass& reactor,		//reactor to be placed in
				   /* in */ int particleNum)			//amount of particles in use
{
	LocationRec loc;	//location within the reactor
	DirectionEnum dir;	//direction to travel
	bool core;			//is location in reactor a core or shield
	for(int i = 0; i < particleNum; i++)
	{
		if(particle.IsActive(i) && !particle.IsEscaped(i))
		{
			loc = particle.GetCurLoc(i);	//get current location of particle
			dir = DirectionEnum(rand() % 6);//get direction it will travel out of location

			//calculate new location for particle based on direction traveling
			switch(int(dir))
			{
			case 0: loc.dep++; break;
			case 1: loc.dep--; break;
			case 2: loc.col++; break;
			case 3: loc.col--; break;
			case 4: loc.row--; break;
			case 5: loc.row++; break;
			}//end switch

			//if movement is going into or within core
			core = reactor.IsCore(loc);

			//check if the location particle is moving to is within reactor
			if(loc.dep >= MAX_DEP || loc.dep < 0 ||
				loc.col >= MAX_COL || loc.col < 0 ||
				loc.row >= MAX_ROW || loc.row < 0)
			{//not within reactor if particle has enough energy it escapes
				if(dir == particle.GetPrevDir(i))
					particle.DecEnergy(i,SAME_DIR_SH);
				else	//change in direction of travel
					particle.DecEnergy(i,DIR_CHANGE_SH);

				//particle had enough energy to leave the reactor
				if(particle.GetEnergy(i) >= 0)
				{
					particle.SetPrevDir(i,dir);	//set exciting direction
					particle.SetEscaped(i);	//particle has escaped the reactor
					reactor.IncEscaped(particle.GetCurLoc(i));//increment escaped
					reactor.DecOccupants(particle.GetCurLoc(i));//dec # of active occupants in location
				}
				else//particle died before move was completed
				{
					reactor.DecOccupants(particle.GetCurLoc(i));//dec # of active occupants in location
					reactor.IncDead(particle.GetCurLoc(i));
				}//end else
			}//end if
			else//movement is still going to be within reactor
			{
				if(core)
				{
					if(dir == particle.GetPrevDir(i))
						particle.DecEnergy(i,SAME_DIR_CORE);
					else	//change in direction of travel
						particle.DecEnergy(i,DIR_CHANGE_CORE);

					//particle had enough energy to move the reactor
					if(particle.IsActive(i))
					{
						particle.SetPrevDir(i,dir);	//set exciting direction

						//particle is leaving location so occupants gets decremented
						reactor.DecOccupants(particle.GetCurLoc(i));
						particle.SetCurLoc(i,loc);	//particle has moved to new location
						//for every other particle inhabiting this location he loses more energy
						particle.DecEnergy(i, reactor.GetOccupants(loc));
						if(particle.IsActive(i))
							reactor.IncOccupants(loc);
						else
							reactor.IncDead(loc);

					}//end if
					else//particle died before move was completed or just had enough to move
					{
						if(particle.GetEnergy(i) == 0)
						{
							//particle had enough energy to move but died after movement
							reactor.DecOccupants(particle.GetCurLoc(i));
							reactor.IncOccupants(loc);
							particle.SetPrevDir(i,dir);
							particle.SetCurLoc(i,loc);
						}//end if
						reactor.IncDead(particle.GetCurLoc(i));
						reactor.DecOccupants(particle.GetCurLoc(i));
					}
				}//end if

				else//movement is not completely within core
				{
					if(dir == particle.GetPrevDir(i))
						particle.DecEnergy(i,SAME_DIR_SH);
					else	//change in direction of travel
						particle.DecEnergy(i,DIR_CHANGE_SH);


					//particle had enough energy to leave the reactor
					if(particle.IsActive(i))
					{
						particle.SetPrevDir(i,dir);	//set exciting direction

						//particle is leaving location so occupants gets decremented
						reactor.DecOccupants(particle.GetCurLoc(i));
						particle.SetCurLoc(i,loc);	//particle has moved to new location
						//for every other particle inhabiting this location he loses more energy
						particle.DecEnergy(i, reactor.GetOccupants(loc));

						//particle still has energy
						if(particle.IsActive(i))
							reactor.IncOccupants(loc);

						else
							reactor.IncDead(loc);
					}//end if
					else//particle died before move was completed or had just enough to move
					{
						if(particle.GetEnergy(i) == 0)
						{
							//particle had enough energy to move but died just after movement
							reactor.DecOccupants(particle.GetCurLoc(i));
							reactor.IncOccupants(loc);
							particle.SetPrevDir(i,dir);
							particle.SetCurLoc(i,loc);
						}//end if
						reactor.IncDead(particle.GetCurLoc(i));
						reactor.DecOccupants(particle.GetCurLoc(i));
					}//end else
				}//end else

			}//end else

		}//end if

	}//end for

}//End Move Particle

/*****************************************************************************************/

//Pre: char * str has been populated by a cin statement
//Post: true is returned if the entire string is infact a number false otherwise
//Purpose: to make sure the inputted string is infact an integer as asked
bool CheckStrForInt(/* in */ const char * str)//string inputted from cin
{

	// is the string empty?
	if (strlen(str) == 0)
		return false;
	//is the string larger then an int
	else if(strlen(str) > 10)
		return false;

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return false; // not a digit
		str++; // move to next character
	}//while
	return true; // all string values were digits
}//End CheckStrForInt

/*****************************************************************************************/

//Pre: particleClass has been initialized.
//	particleNum contains the user defined number of particles
//Post: whether any of the particles are active or not.
//Purpose: to return whether there is atleast 1 active particle in the reactor.
bool ParticlesLeft(/* in */ ParticleClass& particle,	//particles to be checked
				   /* in */ int particleNum)			//number of particles in use
{
	for(int i = 0; i < particleNum; i++)
	{
		//there is a particle that has not escaped and still has an energy > 0
		if(particle.IsActive(i) && !particle.IsEscaped(i))
			return true;
	}//end for

	return false;
}//End ParticlesLeft

/*****************************************************************************************/

//Pre: particle and reactor classes have been instantiated.
//	particleNum contains the number of user defined particles to use.
//	outFile contains the file that we will be writing the output to.
//	The function ParticlesLeft has returned false thus the simulation is over.
//Post:	A nicely formatted output of statistics of the reactor and particles
//	is written to the file for later view.
//Purpose: To create a formatted output for the user to read the statistics of the reactor
//	and particles.
void PrintSummary(/* in */ ParticleClass& particle,	//particles to be placed
				   /* in */ ReactorClass& reactor,		//reactor to be placed in
				   /* in */ int particleNum,			//amount of particles in use
				   /* out */ ostream& outFile)			//file being outputted to
{
	LocationRec loc;	//location within reactor
	int locCt;			//amount of times particle visited location
	int ct = 0;			//general counter for seeing if particle has visited any locations more than once
	int coreCt = 0;		//how many particles still in core
	int shieldCt = 0;	//how many particles still in shield
	int escapeCt = 0;	//how many particles escaped
	float avg;			//averages of particles

	//cycle through the reactor
	for(int i = 0; i < MAX_ROW; i++)
	{
		//add one to level to make it more readable
		//gets rid of a level 0 in printout
		outFile << "Level " << i+1 << endl;
		for(int j = 0; j < MAX_COL; j++)
		{
			for(int k = 0; k < MAX_DEP; k++)
			{
				loc.row = i;
				loc.col = j;
				loc.dep = k;
				
				//current location is not in the core
				//so no particles could be born
				if(!reactor.IsCore(loc))
				{
					//increment amount of deaths within shield
					shieldCt += reactor.GetDead(loc);
					outFile << "**  ";
				}//end if

				//particles can be born
				else
				{	
					//increment the amount of deaths within the core
					coreCt += reactor.GetDead(loc);
					//output the number of particles that could be born
					outFile << "B" << reactor.GetBorn(loc) << "  ";
				}//end else
			}//end for

			outFile << endl;
			
			//cycle through same spots outputting other statistics
			for(int k = 0; k < MAX_DEP; k++)
			{
				loc.row = i;
				loc.col = j;
				loc.dep = k;
				//output how many particles died within that location
				outFile << "R" << reactor.GetDead(loc) << "  ";
			}//end for

			outFile << endl;
			//cycle through same spots outputting other statistics
			for(int k = 0; k < MAX_DEP; k++)
			{
				loc.row = i;
				loc.col = j;
				loc.dep = k;
				//output how many particles escaped from that location
				outFile << "E" << reactor.GetEscaped(loc) << "  ";
			}//end for
			outFile << endl << endl;
		}//end for
		outFile << endl;
	}//end for

	//cycle through the particles
	for(int p = 0; p < particleNum; p++)
	{
		//increment count for every particle that has escaped the reactor
		if(particle.IsEscaped(p))
			escapeCt++;
	}//end for

	//Get Statistics and print
	avg = float(coreCt) / particleNum * 100;	//calculate percent particles remaining in core
	outFile << "Statistics" << endl;
	outFile << setw(5) << "% of Particles Remaining in core: " << fixed << setprecision(2) << avg << "%" << endl;

	avg = float(shieldCt) / particleNum * 100;	//calculate percent of particles remaining in shield
	outFile << setw(5) << "% of Particles Remaining in Shield: " << fixed << setprecision(2) << avg << "%" << endl;
	
	avg = float(escapeCt) / particleNum * 100;	//calculate percent of particles that escaped
	outFile << setw(5) << "% of Particle's That Escaped: " << fixed << setprecision(2) << avg << "%" << endl;
	outFile << endl << endl;

	//Output Particles 
	outFile << "Particles:" << endl << endl;
	for(int p = 0; p < particleNum; p++)
	{
		//add one to particlenum to make look better for user
		//removes a Particle 0, now Particle 1.
		outFile << "Particle " << p+1 << endl;

		//particle has escaped give the location he escaped
		if(particle.IsEscaped(p))
			outFile << "Escaped From Location " << particle.GetCurLoc(p).row << "  "
			<< particle.GetCurLoc(p).col << "  " << particle.GetCurLoc(p).dep << endl << endl;
		//give the location he died
		else
			outFile << "Died in Location " << particle.GetCurLoc(p).row << "  "
			<< particle.GetCurLoc(p).col << "  " << particle.GetCurLoc(p).dep << endl << endl;
		
		//output his full travel log including the amount of times he visited each location
		outFile << "Locations Visited More Than Once" << endl;
		for(int i = 0; i < MAX_ROW; i++)
		{
			for(int j = 0; j < MAX_COL; j++)
			{
				for(int k = 0; k < MAX_DEP; k++)
				{
					loc.row = i;
					loc.col = j;
					loc.dep = k;

					//get the amount of times the particle visited this location
					locCt = particle.RetrieveLocCt(p,loc); 

					//only output as a location visited if the count returned is > 0 
					if(locCt > 0)
					{
						ct++;
						outFile << setw(2) << loc.row << "  " << setw(2) << loc.col << "  " << setw(2) << loc.dep << " | " <<  locCt << " Times" << endl;
					}//end if
				}//end for

			}//end for
		}//end for
		if(ct == 0)
			outFile << "NONE";
		ct = 0;
		outFile << endl << endl;
	}//end for
	
}//end PrintSummary