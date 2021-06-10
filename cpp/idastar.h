// idastar.h
// The definition of class IDAstar
// Class IDAstar inherits from BFSearch

#include "bfsearch.h"

#ifndef IDASTAR_H
#define IDASTAR_H

class Heuristics;
class NodeStack;
class NodeX;

class IDAstar : public BFSearch
{
	public:
		IDAstar( int*, int* );
		~IDAstar();

		void SetUp( int*, int* );
		virtual void Search();

	private:
		NodeX* MakeSearch( int, int& );
		void   SetInitState( int* );
		void   SetGoalState();
		void   InitSearch();
		bool   WasExpanded( NodeX* );
		int    ComputeF( NodeX* );
		void   SetNextF( int, int, int& );
		bool   IsGoal( NodeX* );
		void   ExpandNode( NodeX* );
		void   GenerateNodes( NodeX* );
		char*  GenerateState( int, int, int, char* );
		char*  FindParentState( NodeX* );
		char*  PruneBranch( char*, char* );
		void   AddNode( char*, NodeX* );
		bool   CheckRow( int );
		bool   CheckCol( int );

		NodeStack*	m_stk;
		Heuristics* m_heu;
};

#endif
