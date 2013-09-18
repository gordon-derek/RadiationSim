//Filename: dynordlist.h
//Author: Derek Gordon
//Date: 2/12/2012
//Project: RadiationSim
//Purpose: a doubly circular linked list slimmed
//	down to fit the needs of RadiationSim. This
//	List will be keeping track of the amount of times
//	each location is visited by a particle.  using nodes
//	it will cycle through the list keeping order by row
//	with col then dep being the tie breakers.
//
//*****************Summary Of Methods*******************************//
//
//	OrdListClass();
//	-default constructor. Creates an empty doubly circular linked list.
//
//	~OrdListClass();
//	-deconstructor. Returns the memory used by the list to the system.
//
//	bool IsFull();
//	-checks whether the list is full and returns to the client(always false in linked list).
//
//	bool IsEmpty();
//	-checks whether the list is empty and returns to the client.
//
//	bool EndOfList();
//	-checks whether currPos is = to tail meaning we are at the end of list.
//
//	bool BeginningOfList();
//	-checks whether currPos is = to tail->next meaning we are at the beginning of the list.
//
//	bool Find(/* in */LocationRec loc);			//location within reactor
//	-searches the list for specified location.
//
//	void Insert(/* in */ LocationRec loc);		//location within reactor
//	-inserts the specified location into the list if its not found, if found
//	the count record is incremented by 1. Maintains order.
//
//	int Retrieve(/* in */ LocationRec loc);		//location within reactor
//	-returns the amount of times the specified location has been inserted into the list.
//
//	void FirstPosition();
//	-moves currPos to the first position in list or tail -> next.
//
//	void LastPosition();
//	-moves currPos to the last position in list or tail.
//
//	void NextPosition(); 
//	-moves currPos to the next position in list or currPos -> next.
//
//	void PrevPosition(); 
//	-moves currPos to the previous position in list or currPos -> prev.
//
//	void Clear();
//	-deletes all entries into the list making the list empty.
//
//	node* Allocate();
//	-makes sure there is enough memory to create a new node. Throws bad_alloc error if not.
//
//*********************************************************************************************/

#include "locationRec.h"
#include "exceptions.h"

//forward declaration
struct  node;
//will be created within the class implementation file

// Class Declarations 
class OrdListClass 
{
	public: 
		
		
		OrdListClass(); 
		//Pre: None
		//Post:	An OrdListClass object is created with an empty list.
		//Purpose: creates an OrdListClass object


		~OrdListClass();
		//Pre: Object exists
		//Post: Object's memory returned to system.
		//Purpose: returns OrdListClass object's memory to system.

		bool IsFull();
		//Pre: List exists
		//Post: True is returned if list is full, false otherwise
		//Purpose: to return whether the list is full to the client
		

		bool IsEmpty();
		//Pre:list exists
		//Post True is returned if list is empty, false otherwise
		//Purpose: returns true if list is Empty, false otherwise


		bool EndOfList();
		//Pre:List exists
		//Post: true is returned if currPos is at the end of the list(last element), false otherwise
		//Purpose: returns true if currPos points to end of list(tail)
		

		bool BeginningOfList();
		//Pre:List exists
		//Post: true is returned if currPos is at the beginning of the list(first element), false otherwise
		//Purpose: returns true if currPos points to the beginning of the list(first element)

		
		bool Find(/* in */LocationRec loc);			//location within reactor
		//Pre:		target contains a keyType value to search OrdList for. 
		//Post:		If target is found within the OrdList, true is returned and 
		//				currPos is set to the element's location in the list. If target is 
		//				not found, false is returned and currPos is set to the 
		//				location where the record would have appeared had it been in the 
		//				List.
		//Purpose: finds position of key within the OrdList. 


		void Insert(/* in */ LocationRec loc);		//location within reactor
		//Pre: currPos contains location at which to insert new element;  (find has been called)
		//			where (0 <= currPos <= length) 
		//		find has been called with target, so that currPos contains either the position of a currently
		//		existing element with the same key as target exists or the position
		//		where target should be added.
		//Post: target has been inserted into the OrdList at the location specified by currPos. 
		//Purpose: inserts target into OrdList at position specified by PDM currPos. 

		int Retrieve(/* in */ LocationRec loc);		//location within reactor
		//Pre: loc contains a valid location within the reactor.
		//Post: find is called and if found the amount of times this loc
		//	has been inserted is returned.
		//Purpose: to return the amount of times a particle has visited the
		//	specific location in the reaction

		void FirstPosition();
		//Pre: List exists
		//Post currPos is set to first element in the list
		//Purpose: sets currPos to beginning of list
		

		void LastPosition();
		//Pre: List exists
		//Post currPos is set to last element in the list
		//Purpose: sets currPos to end of list



		void NextPosition(); 
		//Pre: List exists 
		//Post: currPos is set to next element in list 
		//Purpose: sets currPos to next element in list
		

	
		void PrevPosition(); 
		//Pre: List exists 
		//Post: currPos is set to previous element in list 
		//Purpose: sets currPos to previous element in list
		


		void Clear();
		//Pre: List exists
		//Post: List has been cleared and memory returned to system
		//Purpose: Clears the list

	

	protected:

		node* Allocate();  //returns a new node with both pointers set to null.
							//throws bad_alloc exception
		
	private:
		node* tail;			//circular in nature
							//tail->next equivalent of head
							//tail->next-prev gets back to tail

		node* currPos;		//traversal  pointer




};//end OrdListClass 
