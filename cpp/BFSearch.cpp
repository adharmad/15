// BFSearch.cpp
// The implementation of class BFSearch

#include <iostream>
#include "bitRecord.h"
#include "node.h"
#include "bfsearch.h"

BFSearch::BFSearch()
{
	m_bBrd = NULL;
	m_gNode = NULL;
	m_initState = NULL;
	m_goalState = NULL;
}

BFSearch::~BFSearch()
{
	if( m_gNode != NULL )
		delete m_gNode;
	if( m_initState != NULL )
		delete m_initState;
	if( m_goalState != NULL )
		delete m_goalState;
}

int BFSearch::FindPathLng()
{
	return m_gNode->GetG();
}

void BFSearch::ConstructPath( int* path )
{
	// Recursive call to TraceMoves constructs
	// the path (moves of tiles) from the initial
	// to the goal state.

	int nulR, nulC;
	int n = m_gNode->GetG();

	TraceMoves( m_gNode, nulR, nulC, path, n - 1 );
}

void BFSearch::TraceMoves( Node* pNode, int& nulR, int& nulC, int* mv, int i )
{
	Node* pParent = pNode->GetParent();

	if( pParent == NULL )
		m_bBrd->FindNull( nulR, nulC, pNode->GetState() );
	else
	{
		TraceMoves( pParent, nulR, nulC, mv, i - 1 );
		mv[ i ] = m_bBrd->GetField( nulR, nulC, pNode->GetState() );
		m_bBrd->FindNull( nulR, nulC, pNode->GetState() );
	}
}
