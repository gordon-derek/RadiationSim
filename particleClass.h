//Specification File
//Filename: particleClass.h
//Project: RadiationSim
//Author: Derek Gordon
//Date: 2/3/2012
//Purpose: To declare the methods used to drive the
//	particle class.  These methods are implemented to check and/or
//	change the properties of the Private Data Member or particleRec.
//
//Assumptions: None
//
//Error Handling: All Error Handling will be done within the class implementation file
//
//*****************-Summary of Methods-*****************************************/
//
//	ParticleClass();
//	-default constructor, initializes all the properties of the particles
//	to the default values.
//
//	bool IsActive(/* in */int particleNum);				//particle index
//	-checks the particleNum's active property and returns true if the particle
//	is still active, false otherwise.
//
//	void DecEnergy(/* in */ int particleNum,		//particle index
//				   /* in */ int decNum);			//amount to decrement
//	-decrements the specific particle's energy property
//
//	void SetEnergy(/* in */int particleNum,				//particle index
//				   /* in */ int inEnergy);				//inputted energy to assign	
//	-sets the particleNum's energy property to the inputted energy.
//
//	int GetEnergy(/* in */int particleNum);				//particle index
//	-gets the particleNum's energy property and returns the value to the client.
//
//	bool IsEscaped(/* in */int particleNum);			//particle index
//	-gets the particleNum's escaped property and returns the value to the client.
//
//	void SetEscaped(/* in */int particleNum);			//particle index
//	-sets the particleNum's escaped property to true signifying the the particle
//	has escaped the reactor.
//
//	DirectionEnum GetPrevDir(/* in */int particleNum);	//particle index
//	-gets the particleNum's previous direction traveled. Used for calculating the
//	energy used in the next move the particle makes.
//
//	void SetPrevDir(/* in */ int particleNum,			//particle index
//					/* in */ DirectionEnum prevDir);	//previous direction particle traveled
//	-sets the particleNum's previous direction traveled to prevDir which is the particles
//	most recent direction of travel.
//
//	LocationRec GetCurLoc(/* in */ int particleNum);	//particle index
//	-gets the particles current location in the reactor and returns it to the client.
//
//	void SetCurLoc(/* in */ int particleNum,			//particle index
//				   /* in */ LocationRec loc);			//new location of particle
//	-sets the particles current location in the reactor to loc.
//
//	int RetrieveLocCt(/* in */ int particleNum,		//particle index
//					  /* in */ LocationRec loc);		//location within reactor
//	-retrieves the amount of times the specified particle has visited a certain location
//********************************************************************************/



#include "particleRec.h"		//struct of a particle

const int MAX_PARTICLES = 100;	//maximum particles allowed in reactor
const int MAX_ENERGY = 100;		//maximum energy each particle can have

//core movement
const int SAME_DIR_CORE = 1;	//if same direction in core 1 unit of energy dissipated
const int DIR_CHANGE_CORE = 2;	//different direction in core 2 units of energy dissipated

//lead shield movement
const int SAME_DIR_SH = 4;		//same direction in shield 4 units of energy dissipated
const int DIR_CHANGE_SH = 8;	//different direction in shield 8 units of energy dissipated

//array of particles 
typedef ParticleRec ParticleArr[MAX_PARTICLES];

class ParticleClass
{
public:

	ParticleClass();
	//default constructor
	//Pre: class has been instantiated
	//Post: class object has been initialized with default values
	//		energy = 0
	//		escaped = false
	//		prevDir = NONE
	//Purpose: To initialize the class object and set all properties
	//	to their default values.
	

	bool IsActive(/* in */int particleNum);		//particle index
	//Pre: particleNum contains a valid particle number
	//Post: true is returned if if the particle is still active or has energy
	//Purpose: to see whether the particle still has energy or not


	void SetEnergy(/* in */ int inEnergy);		//inputted energy to assign
	//Pre: inEnergy contains a valid value 
	//Post: the energy property for the particles is set
	//Purpose: to set the energy for all the particles


	void DecEnergy(/* in */ int particleNum,		//particle index
				   /* in */ int decNum);			//number to dec energy by
	//Pre: particleNum contains a valid particle number 
	//Post: the energy property for the particles is decramented
	//Purpose: to decrement the energy of a particle


	int GetEnergy(/* in */int particleNum);	//particle index
	//Pre: particleNum contains a valid particle number
	//Post: the amount of energy the particle has is returned
	//Purpose: to get the particles energy and return it to the client


	bool IsEscaped(/* in */int particleNum);	//particle index
	//Pre: particleNum contains a valid particle number
	//Post: whether the particle has escaped the reactor or not is returned
	//Purpose: to return the true/false on whether the particle has escaped


	void SetEscaped(/* in */int particleNum);	//particle index
	//Pre: particleNum contains a valid particle number
	//Post: the escaped property of the particle is set to true
	//Purpose: to show that the given particle has escaped the reactor


	DirectionEnum GetPrevDir(/* in */int particleNum);	//particle index
	//Pre: particleNum contains a valid particle number
	//Post: the previous direction the particle traveled is returned
	//Purpose: to get the previous direction the particle traveled to get to current location


	void SetPrevDir(/* in */ int particleNum,			//particle index
					/* in */ DirectionEnum prevDir);	//previous direction particle traveled
	//Pre: particleNum contains a valid particle number
	//	prevDir contains a valid direction
	//Post: the previous direction is set to the particle properties
	//Purpose: to set the particles previous direction traveled


	LocationRec GetCurLoc(/* in */ int particleNum);	//particle index
	//Pre: particleNum contains a valid particle number
	//Post: current location for that particle is returned
	//Purpose: to return the current location of the specific particle to the client


	void SetCurLoc(/* in */ int particleNum,			//particle index
				   /* in */ LocationRec loc);			//new location of particle
	//Pre: particleNum contains a valid particle number,
	//	loc contains a valid location in the reactor
	//Post: particleNum's current location is updated to loc
	//Purpose: to update the particle's location on movement.


	int RetrieveLocCt(/* in */ int particleNum,		//particle index
					   /* in */ LocationRec loc);		//location within reactor
	//Pre: particleNum contains a valid particle number,
	//	loc contains a valid location in the reactor
	//Post: The amount of times a particle has visited loc is returned
	//Puspose: To return the amount of visits a particle has made to a specific location

private:
	//PDM, array that will hold all the particles and their properties
	ParticleArr particle;
};//End Class