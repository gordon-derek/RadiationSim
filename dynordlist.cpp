//Project: RadiationSim
//Filename: dynordlist.cpp
//Author: Derek Gordon
//Date: 11/26/2011
//Date Modified: 2/12/2012
//Purpose: To implement all of the methods declared
//		in the header file.
//Assumptions: 
//		keys passed in abide to the set rules by the client
//Error Handing:
//		Retrieve on Empty
//		Out of Memory on Allocating for a new node

#include "dynordlist.h"
#include <cstring>

//definition of struct declared in dynordlist.h
struct node
{
	node* prev;//previous position in the list
	LocationRec loc;	//location particle has visited
	int count;			//amount of times particle has visited loc
	node* next;//next position in the list
};//end struct



OrdListClass::OrdListClass()
{
	tail = NULL;
	currPos = NULL;
}//end constructor

/********************************************************************************/

OrdListClass::~OrdListClass()
{
	Clear();//clear list
	//delete remaining objects
	delete tail;
	delete currPos;
}//end destructor

/********************************************************************************/

bool OrdListClass::IsFull()
{
	return false;
}//end IsFull

/********************************************************************************/

bool OrdListClass::IsEmpty()
{
	return (tail == NULL);
}

/********************************************************************************/

bool OrdListClass::EndOfList()
{
	return (currPos == tail);
}//end IsEmpty

/********************************************************************************/

bool OrdListClass::BeginningOfList()
{
	return ( currPos == (tail -> next));
}//end BeginningOfList()

/********************************************************************************/

bool OrdListClass::Find(/* in */ LocationRec loc)
{
	
	if(IsEmpty())//no items to find
		return false;
	else
		FirstPosition();//sets currPos to first position

		//loc is same as tail record
		if(loc.row == tail -> loc.row &&
			loc.col == tail -> loc.col &&
			loc.dep == tail -> loc.dep)
		{
			currPos = tail;
			return true;
		}//end else if
		
		//loc is less then smallest loc in list
		else if(loc.row < tail -> next -> loc.row ||
				(loc.row == tail -> next -> loc.row && loc.col < tail -> next -> loc.col) || 
				(loc.row == tail -> next -> loc.row && loc.col == tail -> next -> loc.col && loc.dep < tail -> next -> loc.dep))
		{
			//set to be inserted at first location in list
			currPos = tail -> next;
			return false;
		}//end else if

		//loc is greater then largest loc in list
		else if(loc.row > tail -> loc.row ||
				(loc.row == tail -> loc.row && loc.col > tail -> loc.col) || 
				(loc.row == tail -> loc.row && loc.col == tail -> loc.col && loc.dep > tail -> loc.dep))
		{
			//set to be inserted at last location in list
			currPos = tail;
			return false;
		}//end else if


	while(!EndOfList())
	{//cycle through the list

		//target location row is less than currPos loc row
		if(loc.row < currPos -> loc.row)
		{
			//not in list 
			currPos = currPos -> prev;
			return false;
		}

		//target location row is greater than currPos loc row
		else if(loc.row > currPos -> loc.row)
			currPos = currPos -> next;	//check next position
		

		//row is equal to current positions row
		else if(loc.row == currPos -> loc.row)
		{
			//col is smaller than current positions col
			if(loc.col < currPos -> loc.col)
			{
				//not in list go to prev position
				currPos = currPos -> prev;
				return false;
			}//end if
			
			//col is larger than current positions col
			else if(loc.col > currPos -> loc.col)
			{
				//go to next position
				currPos = currPos -> next;
			}//end else if

			else//col is equal to current positions col
			{
				//loc is smaller then current position
				if(loc.dep < currPos -> loc.dep)
				{
					//not in list go to previous position
					currPos = currPos -> prev;
					return false;
				}//end if

				//loc is larger then current position
				else if(loc.dep > currPos -> loc.dep)
					currPos = currPos -> next;	//go to next position
				
				else//loc is same as current positions record
					return true;
			}//end else
		}//end if
		

	}//end while
		

	return false;

}//end find

/********************************************************************************/

void OrdListClass::Insert(/* in */ LocationRec target)
{
	if(Find(target))
		currPos -> count++;
	else
	{
		//always false in linked list
		if(!IsFull())
		{
			//create a new node if possible
			node* newNode = Allocate();
			//get the inserting record
			newNode -> loc = target;
			newNode -> count = 1;

			//no current records in list
			if(IsEmpty())
			{
				//tail and currPos are the same
				//both pointing to themselves to remain circular
				tail = newNode;
				currPos = tail;
				tail -> next = tail;
				tail -> prev = tail;
			}//end if

			//being inserted at last location in list
			else if(currPos == tail)
			{
				//insert new node after currPos
				//maintain previous and next nodes to point to and from newNode
				newNode -> next = currPos -> next;
				newNode -> prev = currPos;
				currPos -> next = newNode;
				newNode -> next -> prev = newNode;
				tail -> next = newNode;
				//set the newly inserted node as the tail
				tail = newNode;
			}//end else if

			//being inserted at first position in list
			else if(currPos == tail -> next)
			{
				if(currPos -> loc.row < target.row ||
				   currPos -> loc.row == target.row && currPos -> loc.col < target.col ||
				   currPos -> loc.row == target.row && currPos -> loc.col == target.col && currPos -> loc.dep < target.dep)
				{
					newNode -> next = currPos -> next;
					newNode -> prev = currPos;
					currPos -> next = newNode;
				}
				else
				{
					//insert newNode before currPos
					//maintain previous and next nodes to point to and from newNode
					newNode -> next = tail -> next;
					tail -> next = newNode;
					newNode -> prev = tail;
					newNode -> next -> prev = newNode;
				}
			}//end else if

			//anywhere else in the list
			else
			{
				//insert new node after currPos
				//maintain previous and next nodes to point to and from newNode
				newNode -> next = currPos -> next;
				newNode -> prev = currPos;
				currPos -> next = newNode;
			}//end else

		}//end if

	}//end else
}//end insert

/********************************************************************************/

int OrdListClass::Retrieve(/* in */ LocationRec loc)
{
	//location has been visited
	if(Find(loc))
		return currPos -> count;	//output amount of times visited
	else//location not visited or visited 0 times.
		return 0;

}//end Retrieve

/********************************************************************************/

void OrdListClass::FirstPosition()
{
	currPos = tail -> next;
}//End FirstPosition

/********************************************************************************/

void OrdListClass::LastPosition()
{
	currPos = tail;
}//End LastPosition

/********************************************************************************/

void OrdListClass::NextPosition()
{
	currPos = currPos -> next;
}//End NextPosition

/********************************************************************************/

void OrdListClass::PrevPosition()
{
	currPos = currPos -> prev;
}//End PrevPosition

/********************************************************************************/

void OrdListClass::Clear()
{
	
	if(!IsEmpty())
	{//there are records in the list
		FirstPosition();
		while (!IsEmpty())
		{//cycle through the list
			
			//at the final position to be deleted
			if(currPos == tail)
			{
				delete currPos;
				//set nodes to null to show empty list
				currPos = NULL;
				tail = NULL;
			}//end if
			else//multiple records still in list
			{
				//maintain prev and next nodes to skip around currPos being deleted
				tail -> next = currPos -> next;
				currPos -> prev -> next = currPos -> next;
				currPos = currPos -> next;
				currPos -> prev = currPos -> prev -> prev;
				if(currPos -> prev != tail)
				{
					delete currPos -> prev;
				}//end if
			}//end else
		}//end while
	}//end if
	

}//end Clear

/********************************************************************************/

node* OrdListClass::Allocate()
{
	try
	{
		//if there is not enough memory for new node will throw exception
		node* newNode = new node;

		return newNode;
	}//end try
	catch(bad_alloc)
	{
		ExceptionClass exception;
		exception.HandleExc("System is Out of Memory: Closing");
	}//end catch

}//end Allocate