// bfsearch.h
// The definition of class BFSearch (Best First Search)

#ifndef BFSEARCH_H
#define BFSEARCH_H

class BitRecord;
class Node;

class BFSearch
{
	public:
		BFSearch();
		virtual ~BFSearch();

		virtual void Search() = 0;

		void ConstructPath( int* );
		int  FindPathLng();

	protected:
		void TraceMoves( Node*, int&, int&, int*, int );

		BitRecord* m_bBrd;  // bitwise game board
		Node*      m_gNode; // goal node pointer
		char* m_initState;
		char* m_goalState;
};

#endif
