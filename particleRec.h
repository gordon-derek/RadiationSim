//Filename: particleRec.h
//Author: Derek Gordon
//Date: 2/2/2012
//Purpose: To declare a struct that will hold
//	the basic characteristics of a particle to
//	be used within the class.
//		Declares a enumerated datatype to handle
//	the particles previous direction of travel.

#ifndef PARTICLE_REC
#define PARTICLE_REC

#include "locationRec.h"
#include "dynordlist.h"

//enumerated datatype to signify direction traveled
enum DirectionEnum{NORTH,SOUTH,EAST,WEST,UP,DOWN,NONE};

struct ParticleRec
{
	int energy;				//energy the particle has
	bool escaped;			//the particle has made it through the shield
	DirectionEnum prevDir;	//the previous direction the particle travelled
	LocationRec curLoc;		//the current location of the particle in reactor
	OrdListClass locList;	//keeps track of every location visited and amount of times
};//End Struct



#endif
