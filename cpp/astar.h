// astar.h
// The definition of class Astar
// Class Astar inherits from class BFSearch.

#include "bfsearch.h"

#ifndef ASTAR_H
#define ASTAR_H

class PriorityQ;
class HashTable;
class Node;
class NodeX;

class Astar : public BFSearch
{
	public:
		Astar( int*, int* );
		~Astar();

		virtual void Search();

	private:
		void  SetUp( int*, int* );
		void  SetInitState( int* );
		void  SetGoalState();
		void  InitSearch();
		void  ExpandNode( Node* );
		bool  IsGoal( Node* );
		void  GenerateNodes( NodeX* );
		char* GenerateState( int, int, int, char* );
		void  AddNode( char*, NodeX* );
		bool  CheckRow( int );
		bool  CheckCol( int );

		PriorityQ* m_open;		// open list
		HashTable* m_closed;	// closed list
};

#endif
