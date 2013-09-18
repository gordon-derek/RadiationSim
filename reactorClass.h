//Specification File
//Filename: reactorClass.h
//Project: RadiationSim
//Author: Derek Gordon
//Date: 2/3/2012
//Purpose: To declare the methods used to drive the
//	reactor class.  These methods are implemented to check and/or
//	change the properties of the Private Data Member or reactorRec.
//
//Assumptions: None
//
//Error Handling: All Error Handling will be done within the class implementation file
//
//*****************-Summary of Methods-*****************************************/
//
//	ReactorClass();
//	-default constructor, initializes all the properties of reactorRec
//	to the default values.
//
//	short GetOccupants(/* in */ LocationRec loc);	//location in reactor
//	-gets the reactorRec's number of occupants for that specific location
//	within the reactor.
//
//	void IncOccupants(/* in */ LocationRec loc);	//location in reactor
//	-increments the reactor's number of occupants for that specific location
//
//	void DecOccupants(/* in */ LocationRec loc);	//location in reactor
//	-decrements the reactor's number of occupants for that specific location
//	
//	bool IsCore( /* in */ LocationRec loc);			//location in reactor
//	-gets whether the specific location within the reactor is the core(where particles are born)
//
//	short GetBorn(/* in */ LocationRec loc);		//location in reactor
//	-gets the number of particles that were born at that specific location within the reactor.
//
//	void IncBorn(/* in */ LocationRec loc);			//location in reactor
//	-increments the number of particles that were born at that specific location within the reactor.
//
//	short GetDead(/* in */ LocationRec loc);		//location in reactor
//	-gets the number of particles that died at that specific location within the reactor.
//
//	void IncDead(/* in */ LocationRec loc);			//location in reactor
//	-increments the number of particles that died at the specific location within the reactor.
//
//	short GetEscaped(/* in */ LocationRec loc);		//location in reactor
//	-returns the number of particles that escaped the reactor from that specific location.
//
//	void IncEscaped(/* in */ LocationRec loc);		//location in reactor
//	-increments the number of particles that escaped the reactor from that specific location.
//*****************************************************************************/

//needed structs
#include "reactorRec.h"
#include "locationRec.h"

//constants/maximum size the reactor can be.
const int MAX_ROW = 7;
const int MAX_COL = 7;
const int MAX_DEP = 7;

//size of lead shield
const int SHIELD_SIZE = 2;

//3-dimensional array of ReactorRecs
typedef ReactorRec ReactorRecArr[MAX_ROW][MAX_COL][MAX_DEP];

class ReactorClass
{
public:


	ReactorClass();
	//default constructor
	//Pre: the class has been instantiated
	//Post: class object has been initialized with default values
	//		numOccupants = 0;
	//		bool core is calculated dependant on size of cube
	//		born = 0;
	//		dead = 0;
	//Purpose: To initialize the class object and set all properties to their
	//	default values

	short GetOccupants(/* in */ LocationRec loc);	//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the number of occupants in that location is returned
	//Purpose: to get the number of occupants in that specific location
	//	returned to the client.

	void IncOccupants(/* in */ LocationRec loc);		//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the property numOccupants for that specific location
	//	is incremented by 1.
	//Purpose: to increment the number of occupants in a specific location

	void DecOccupants(/* in */ LocationRec loc);		//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the property numOccupants for that specific location
	//	is decremented by 1.
	//Purpose: to decrement the number of occupants in a specific location

	bool IsCore( /* in */ LocationRec loc);		//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: whether the specific location is the core or shield is returned
	//	false for shield, true for core.
	//Purpose: to return whether or not the specific location in the reactor
	//	is the core or not.

	short GetBorn(/* in */ LocationRec loc);		//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the amount of particles born in that location is returned
	//	to the client.
	//Purpose: to return the number of particles that were born in that specific
	//	location.

	void IncBorn(/* in */ LocationRec loc);//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the property born for that specific location is incremented by 1
	//Purpose: to increase the number of particles born in that specific location

	short GetDead(/* in */ LocationRec loc);		//location in reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the amount of particles that died in this specific location is
	//	returned to the client.
	//Purpose: to return the class objects property dead for that specific location
	//	to the client.

	void IncDead(/* in */ LocationRec loc);			//location on reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the property dead for that specific location is incremented by 1
	//Purpose: to increment the number of particles dead in that specific location

	short GetEscaped(/* in */ LocationRec loc);		//location in reactor
	//Pre: loc contains a valid location in the reactor
	//Post: return the amount of particles that have escaped from that specific location
	//Purpose: to get the number of particles that have escaped from the reactor at that
	//	location and return it to the client

	void IncEscaped(/* in */ LocationRec loc);		//location in reactor
	//Pre: loc contains a valid location in the reactor
	//Post: the amount of particles that have escaped from that specific location is incremented
	//Purpose: to increment the amount of particles that have escaped from the reactor at
	//	location loc.

private:
	//three dimensional array pointer
	ReactorRecArr reactor;
};