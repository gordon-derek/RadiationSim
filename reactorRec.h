//Filename: reactorRec.h
//Author: Derek Gordon
//Date: 2/2/2012
//Purpose: To declare a struct that
//	will handle all the characteristics
//	of our 3-dimensional array or reactor.

#ifndef REACTOR_REC
#define REACTOR_REC

struct ReactorRec
{
	short numOccupants;	//amount of ACTIVE particles in that cell
	bool core;			//is the area of the reactor the core or shield
	short born;			//amount of particles born in that cell
	short dead;			//amount of particles that died in that cell
	short escaped;		//amount of particles that escaped reactor from current cell
};//End Struct

#endif