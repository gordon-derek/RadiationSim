//Implementation File
//Filename: particleClass.cpp
//Project: RadiationSim
//Author: Derek Gordon
//Date: 2/3/2012
//Purpose: To implement the methods declared in particleClass.h.
//	These methods are used to make modifications to the properties of
//	our particleRec.
//
//Assumptions: None
//
//Error Handling: None

#include "particleClass.h"

ParticleClass::ParticleClass()
{
	//cycle through the array
	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		//set default values
		particle[i].energy = 0;
		particle[i].escaped = false;
		particle[i].prevDir = NONE;
	}//end for

}//End Default constructor

/***************************************************************/

bool ParticleClass::IsActive(/* in */ int particleNum)			//particle index
{
	return (particle[particleNum].energy > 0);
}//End IsActive

/***************************************************************/

void ParticleClass::SetEnergy(/* in */ int inEnergy)			//inputted energy
{
	for(int i = 0; i < MAX_PARTICLES; i++)
	{
		particle[i].energy = inEnergy;
	}//end for
}//End SetInActive

/***************************************************************/

void ParticleClass::DecEnergy(/* in */ int particleNum,			//particle index
							  /* in */ int decNum)				//number to dec energy by
{
	particle[particleNum].energy = particle[particleNum].energy - decNum;
}

/***************************************************************/

int ParticleClass::GetEnergy(/* in */ int particleNum)			//particle index
{
	return particle[particleNum].energy;
}//End SetInActive

/***************************************************************/

bool ParticleClass::IsEscaped(/* in */ int particleNum)			//particle index
{
	return particle[particleNum].escaped;
}//End IsEscaped

/***************************************************************/

void ParticleClass::SetEscaped(/* in */ int particleNum)		//particle index
{
	particle[particleNum].escaped = true;
}//End SetEscaped

/***************************************************************/

DirectionEnum ParticleClass::GetPrevDir(/* in */int particleNum)//particle index
{
	return particle[particleNum].prevDir;
}//End GetPrevDir

/***************************************************************/

void ParticleClass::SetPrevDir(/* in */ int particleNum,		//particle index
							   /* in */ DirectionEnum prevDir)	//previous direction traveled
{
	particle[particleNum].prevDir = prevDir;
}//End SetPrevDir

/***************************************************************/

LocationRec ParticleClass::GetCurLoc(/* in */ int particleNum)	//particle index
{
	return particle[particleNum].curLoc;
}//End GetCurLoc

/***************************************************************/

void ParticleClass::SetCurLoc(/* in */ int particleNum,			//particle index
							  /* in */ LocationRec loc)			//new location of particle
{
	//insert into travel records
	particle[particleNum].locList.Insert(loc);
	//set current location
	particle[particleNum].curLoc = loc;
}//End SetCurLoc

/***************************************************************/

int ParticleClass::RetrieveLocCt(/* in */ int particleNum,		//particle index
					   /* in */ LocationRec loc)	//location within reactor
{
	return particle[particleNum].locList.Retrieve(loc);
}//End RetrieveLocCt