// Astar.cpp
// The implementation of class Astar

#include <iostream>
#include "constants.h"
#include "bitRecord.h"
#include "heuristics.h"
#include "manhattanDist.h"
#include "misplacedTiles.h"
#include "priorityQ.h"
#include "hashTable.h"
#include "node.h"
#include "nodeX.h"
#include "astar.h"

Astar::Astar( int* msg, int* brd ) : BFSearch()
{
	m_open = NULL;
	m_closed = NULL;
	if( msg != NULL && brd != NULL )
		SetUp( msg, brd );
}

Astar::~Astar()
{
	delete m_closed;
	delete m_open;
	delete m_bBrd;
}

void Astar::SetUp( int* msg, int* brd )
{
	Heuristics* pH;

	m_bBrd = new BitRecord( msg[ DIMSPECR ], msg[ DIMSPECC ] );
	if( msg[ HEURTYPE ] != OPTSET )
		pH = (Heuristics*)new ManhattanDist( m_bBrd );
	else
		pH = (Heuristics*)new MisplacedTiles( m_bBrd );
	m_open = new PriorityQ( pH );
	m_closed = new HashTable( m_bBrd );
	SetInitState( brd );
	SetGoalState();
}

void Astar::SetInitState( int* brd )
{
	// creates and stores initial state

	m_bBrd->GenRecord( brd );
	m_initState = m_bBrd->ReleaseRecord();
}

void Astar::SetGoalState()
{
	// creates and stores goal state

	int sq = ( m_bBrd->GetRows() )*( m_bBrd->GetCols() );
	int* brd = new int[ sq ];

	for( int i = 0; i < sq; i++ )
		brd[ i ] = i;
	m_bBrd->GenRecord( brd );
	m_goalState = m_bBrd->ReleaseRecord();
	delete [] brd;
}

void Astar::Search()
{
	// does the A* search

	Node* pNode;

	InitSearch();
	pNode = m_open->Dequeue();
	while( pNode != NULL && !IsGoal( pNode ) )
	{
		ExpandNode( pNode );
		pNode = m_open->Dequeue();
	}

	m_gNode = pNode;
}

void Astar::InitSearch()
{
	// prepares for A* serch

	char* state = m_bBrd->DupRecord( m_initState );
	Node* pNode = NULL;

	pNode = new Node( 0, state );
	m_open->Enqueue( pNode );
}

void Astar::ExpandNode( Node* pNode )
{
	NodeX* pNodeX = NULL;

	pNodeX = new NodeX( pNode );
	delete pNode;
	m_closed->Insert( pNodeX );
	GenerateNodes( pNodeX );
}

bool Astar::IsGoal( Node* pNode )
{
	if( pNode == NULL )
		return false;
	if( m_bBrd->IsEqual( m_goalState, pNode->GetState() ) )
		return true;

	return false;
}

void Astar::GenerateNodes( NodeX* pNodeX )
{
	int nulR, nulC;
	char* dup = NULL;
	char* state = pNodeX->GetState();

	m_bBrd->FindNull( nulR, nulC, state );
	for( int i = 0; i < GENMAX; i++ )
	{
		dup = GenerateState( i, nulR, nulC, state );
		if( dup != NULL )
			AddNode( dup, pNodeX );
	}
}

char* Astar::GenerateState( int dir, int nulR, int nulC, char* state )
{
	// generates a new state from the parent state

	int nxtR = nulR + ( dir - 1 )%2;
	int nxtC = nulC + ( dir - 2 )%2;
	char* dup = NULL;

	if( CheckRow( nxtR ) && CheckCol( nxtC ) )
	{
		dup = m_bBrd->DupRecord( state );
		m_bBrd->SwapFields( nxtR, nxtC, nulR, nulC, dup );
	}

	return dup;
}

void Astar::AddNode( char* pState, NodeX* pNodeX )
{
	// adds a node to open list if it is not
	// found in closed list

	int g;
	Node* pNode;

	if( m_closed->Search( pState ) == NULL )
	{
		g = pNodeX->GetG() + 1;
		pNode = new Node( g, pState, (Node*)pNodeX );
		m_open->Enqueue( pNode );
	}
	else
		delete [] pState;
}

bool Astar::CheckRow( int r )
{
	if( r >= 0 && r < m_bBrd->GetRows() )
		return true;

	return false;
}

bool Astar::CheckCol( int c )
{
	if( c >= 0 && c < m_bBrd->GetCols() )
		return true;

	return false;
}
