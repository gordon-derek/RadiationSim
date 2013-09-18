//Implementation File
//Filename: reactorClass.cpp
//Project: RadiationSim
//Author: Derek Gordon
//Date: 2/3/2012
//Purpose: To implement the methods declared in particleClass.h.
//	These methods are used to make modifications to the properties of
//	our particleRec.
//
//Assumptions: MAX_ROW, MAX_COL, and MAX_DEP will not exceed 15.
//
//Error Handling: None

#include "reactorClass.h"

ReactorClass::ReactorClass()
{
	//now that reactor is created, set default values
	for(int i = 0; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COL; j++)
		{
			for(int k = 0; k < MAX_DEP; k++)
			{
				reactor[i][j][k].born = 0;
				reactor[i][j][k].dead = 0;
				reactor[i][j][k].numOccupants = 0;
				reactor[i][j][k].escaped = 0;
				
				//if within the outer 2 square meters of reactor
				//make a core
				if(i >= SHIELD_SIZE && i < (MAX_ROW - 2))
				{
					if(j >= SHIELD_SIZE && j < (MAX_COL - 2))
					{
						if(k >= SHIELD_SIZE && k < (MAX_DEP - 2))
							reactor[i][j][k].core = true;
					
						else
							reactor[i][j][k].core = false;
					}//end if
					else
						reactor[i][j][k].core = false;
				}//end if
				else
					reactor[i][j][k].core = false;
			}//end for
		}//end for
	}//end for
}//end default constructor

short ReactorClass::GetOccupants(/* in */ LocationRec loc)	//location on reactor
{
	return reactor[loc.row][loc.col][loc.dep].numOccupants;
}//end GetOccupants

void ReactorClass::IncOccupants(/* in */ LocationRec loc)		//location on reactor
{
	reactor[loc.row][loc.col][loc.dep].numOccupants++;
}//end IncOccupants

void ReactorClass::DecOccupants(/* in */ LocationRec loc)		//location on reactor
{
	reactor[loc.row][loc.col][loc.dep].numOccupants--;
}//end DecOccupants

bool ReactorClass::IsCore(/* in */ LocationRec loc)
{
	return reactor[loc.row][loc.col][loc.dep].core;
}//end IsCore

short ReactorClass::GetBorn(/* in */ LocationRec loc)		//location on reactor
{
	return reactor[loc.row][loc.col][loc.dep].born;
}//end GetBorn

void ReactorClass::IncBorn(/* in */ LocationRec loc)			//location on reactor
{
	reactor[loc.row][loc.col][loc.dep].born++;
}//end IncBorn

short ReactorClass::GetDead(/* in */ LocationRec loc)		//location in reactor
{
	return reactor[loc.row][loc.col][loc.dep].dead;
}//End GetDead

void ReactorClass::IncDead(/* in */ LocationRec loc)			//location on reactor
{
	reactor[loc.row][loc.col][loc.dep].dead++;
}//End IncDead

short ReactorClass::GetEscaped(/* in */ LocationRec loc)		//location in reactor
{
	return reactor[loc.row][loc.col][loc.dep].escaped;
}//End GetEscaped

void ReactorClass::IncEscaped(/* in */ LocationRec loc)		//location in reactor
{
	reactor[loc.row][loc.col][loc.dep].escaped++;
}//End IncEscaped