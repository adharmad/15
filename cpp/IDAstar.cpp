// IDAstar.cpp
// The implementation of class IDAstar

#include <iostream>
#include "constants.h"
#include "bitRecord.h"
#include "heuristics.h"
#include "manhattanDist.h"
#include "misplacedTiles.h"
#include "nodeStack.h"
#include "node.h"
#include "nodeX.h"
#include "idastar.h"

using namespace std;

IDAstar::IDAstar( int* msg, int* brd )
{
	m_stk = NULL;
	m_heu = NULL;
	if( msg != NULL && brd != NULL )
		SetUp( msg, brd );
}

IDAstar::~IDAstar()
{
	delete m_stk;
	delete m_heu;
	delete m_bBrd;
}

void IDAstar::SetUp( int* msg, int* brd )
{
	m_bBrd = new BitRecord( msg[ DIMSPECR ], msg[ DIMSPECC ] );
	if( msg[ HEURTYPE ] != OPTSET )
		m_heu = (Heuristics*)new ManhattanDist( m_bBrd );
	else
		m_heu = (Heuristics*)new MisplacedTiles( m_bBrd );
	m_stk = new NodeStack();
	SetInitState( brd );
	SetGoalState();
}

void IDAstar::SetInitState( int* brd )
{
	// creates and stores initial state

	m_bBrd->GenRecord( brd );
	m_initState = m_bBrd->ReleaseRecord();
}

void IDAstar::SetGoalState()
{
	// creates and stores goal state

	int sq = ( m_bBrd->GetRows() )*( m_bBrd->GetRows() );
	int* brd = new int[ sq ];

	for( int i = 0; i < sq; i++ )
		brd[ i ] = i;
	m_bBrd->GenRecord( brd );
	m_goalState = m_bBrd->ReleaseRecord();
	delete [] brd;
}

void IDAstar::Search()
{
	int currF = m_heu->ComputeH( m_initState );
	int nextF = -1;
	NodeX* pNode = NULL;

	// loop for iterative deepening
	while( pNode == NULL && currF != nextF )
	{
		cout << "cutoff = " << currF << endl;

		pNode = MakeSearch( currF, nextF );
		currF = nextF;
		nextF = -1;
	}

	m_gNode = (Node*)pNode;
}

NodeX* IDAstar::MakeSearch( int currF, int& nextF )
{
	// performs the search in one iteration

	int f;
	NodeX* pNode = NULL;

	m_stk->MakeStack();
	InitSearch();
	pNode = m_stk->Pop();
	for(; pNode != NULL; pNode = m_stk->Pop() )
	{
		if( !WasExpanded( pNode ) )
		{
			f = ComputeF( pNode );
			SetNextF( f, currF, nextF );
			if( f <= currF )
			{
				if( IsGoal( pNode ) )
				{
					m_stk->PopOff();
					return pNode;
				}
				ExpandNode( pNode );
				continue;
			}
		}
		m_stk->PopOff();
		delete pNode;
	}
	m_stk->KillStack();

	cout << "Iterative cycle complete" << endl;

	return pNode;
}

void IDAstar::InitSearch()
{
	// prepares for a search

	char* state = m_bBrd->DupRecord( m_initState );
	NodeX* pNode = NULL;

	pNode = new NodeX( 0, state );
	m_stk->Push( pNode );
}

bool IDAstar::WasExpanded( NodeX* pNode )
{
	// checks if a node has already
	// been expanded

	if( pNode->GetG() < 0 )
		return true;

	return false;
}

int IDAstar::ComputeF( NodeX* pNode )
{
	int g = pNode->GetG();
	int h = m_heu->ComputeH( pNode->GetState() );

	return g + h;
}

void IDAstar::SetNextF( int f, int currF, int& nextF )
{
	// sets the cutoff value for
	// the next iteration

	if( nextF < 0 && f > currF )
		nextF = f;
	else if( f < nextF && f > currF )
		nextF = f;
}

void IDAstar::ExpandNode( NodeX* pNode )
{
	GenerateNodes( pNode );
	pNode->SetG( -1 );
}

bool IDAstar::IsGoal( NodeX* pNode )
{
	if( pNode == NULL )
		return false;
	if( m_bBrd->IsEqual( m_goalState, pNode->GetState() ) )
		return true;

	return false;
}

void IDAstar::GenerateNodes( NodeX* pNode )
{
	int nulR, nulC;
	char* nextState = NULL;
	char* currState = pNode->GetState();		// current state
	char* prevState = FindParentState( pNode ); // previous state

	m_bBrd->FindNull( nulR, nulC, currState );
	for( int i = 0; i < GENMAX; i++ )
	{
		nextState = GenerateState( i, nulR, nulC, currState );
		nextState = PruneBranch( prevState, nextState );
		if( nextState != NULL )
			AddNode( nextState, pNode );
	}
}

char* IDAstar::GenerateState( int dir, int nulR, int nulC, char* state )
{
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

char* IDAstar::FindParentState( NodeX* pNode )
{
	Node* pParent = pNode->GetParent();

	if( pParent != NULL )
		return pParent->GetState();

	return NULL;
}

char* IDAstar::PruneBranch( char* prev, char* curr )
{
	if( prev == NULL )
		if( curr != NULL )
			if( m_bBrd->IsEqual( prev, curr ) )
			{
				delete curr;
				curr = NULL;
			}

	return curr;
}

void IDAstar::AddNode( char* pState, NodeX* pNode )
{
	// puts a node on the stack

	NodeX* pChild;
	int g = pNode->GetG() + 1;

	pChild = new NodeX( g, pState, (Node*)pNode );
	m_stk->Push( pChild );
}

bool IDAstar::CheckRow( int r )
{
	if( r >= 0 && r < m_bBrd->GetRows() )
		return true;

	return false;
}

bool IDAstar::CheckCol( int c )
{
	if( c >= 0 && c < m_bBrd->GetCols() )
		return true;

	return false;
}
