// PriorityQ.cpp
// The implementation of class PritorityQ

#include <iostream>
#include "bitRecord.h"
#include "heuristics.h"
#include "priorityQ.h"
#include "node.h"

PriorityQ::PriorityQ( Heuristics* pH, int size )
{
	m_size = size;
	if( m_size < 1 )
		m_size = INITSIZE;
	m_heap = NULL;
	m_hSize = -1;
	m_qSize = m_size;
	m_h = pH;
	MakeQueue();
}

PriorityQ::~PriorityQ()
{
	KillQueue();
	delete m_h;
}

void PriorityQ::MakeQueue()
{
	if( m_hSize != 0 )
	{
		if( m_heap != NULL )
			KillQueue();
		BuildQueue();
		m_hSize = 0;
	}
}

void PriorityQ::BuildQueue()
{
	m_heap = new Node*[ m_qSize ];
	for( int i = 0; i < m_qSize; i++ )
		m_heap[ i ] = NULL;
}

void PriorityQ::KillQueue()
{
	if( m_heap != NULL )
	{
		for( int i = 0; m_heap[ i ] != NULL; i++ )
			delete m_heap[ i ];
		delete [] m_heap;
		m_heap = NULL;
		m_hSize = -1;
		m_qSize = m_size;
	}
}

void PriorityQ::Enqueue( Node* pNode )
{
	if( m_hSize == m_qSize )
		ExpandQueue();

	int i = m_hSize++;
	int key = FindKey( pNode );

	while( i > 0 )
	{
		if( key >= FindKey( m_heap[ PARENT ] ) )
			break;
		m_heap[ i ] = m_heap[ PARENT ];
		i = PARENT;
	}
	m_heap[ i ] = pNode;
}

void PriorityQ::ExpandQueue()
{
	int size = m_qSize;
	Node** tmp = m_heap;

	m_qSize *= 2;
	BuildQueue();
	for( int i = 0; i < size; i++ )
		m_heap[ i ] = tmp[ i ];
	delete [] tmp;
}

Node* PriorityQ::Dequeue()
{
	Node* min = m_heap[ 0 ];

	if( min != NULL )
	{
		m_heap[ 0 ] = m_heap[ --m_hSize ];
		m_heap[ m_hSize ] = NULL;
		Heapify( 0 );
	}

	return min;
}

void PriorityQ::Heapify( int i )
{
	Node* tmp;
	int l = LEFT;
	int r = RIGHT;
	int min = i;

	if( l < m_hSize )
		if( FindKey( m_heap[ l ] ) < FindKey( m_heap[ i ] ) )
			min = l;
	if( r < m_hSize )
		if( FindKey( m_heap[ r ] ) < FindKey( m_heap[ min ] ) )
			min = r;
	if( min != i )
	{
		tmp = m_heap[ min ];
		m_heap[ min ] = m_heap[ i ];
		m_heap[ i ] = tmp;

		Heapify( min );
	}
}

int PriorityQ::FindKey( Node* pNode )
{
	int g = pNode->GetG();
	int h = m_h->ComputeH( pNode->GetState() );

	return g + h;
}
