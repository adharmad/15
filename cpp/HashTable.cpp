// HashTable.cpp
// The implementation of class HashTable
// Class HashTable implements chaining.

#include "nodeX.h"
#include "bitRecord.h"
#include "hashTable.h"

HashTable::HashTable( BitRecord* pBrd, int size )
{
	m_bBrd = pBrd;
	m_size = size;
	m_count = -1;
	m_table = NULL;
	MakeTable();
}

HashTable::~HashTable()
{
	KillTable();
	m_bBrd = NULL;
}

void HashTable::MakeTable()
{
	// Initializes the nodeX array

	if( m_count != 0 )
	{
		if( m_table != NULL )
			KillTable();
		m_table = new NodeX*[ m_size ];
		for( int i = 0; i < m_size; i++ )
			m_table[ i ] = NULL;
		m_count = 0;
	}
}

void HashTable::KillTable()
{
	// Destructs the nodeX array

	if( m_table != NULL )
	{
		for( int i = 0; i < m_size; i++ )
			if( m_table[ i ] != NULL )
				DelField( m_table[ i ] );
		delete [] m_table;
		m_count = -1;
		m_table = NULL;
	}
}

void HashTable::DelField( NodeX* head )
{
	// Destroys a chain in the table

	NodeX* tmp = head;

	while( tmp != NULL )
	{
		head = head->GetNext();
		delete tmp;
		tmp = head;
	}
}

void HashTable::SetBoard( BitRecord* pBrd )
{
	m_bBrd = pBrd;
}

void HashTable::Insert( NodeX* pEntry )
{
	int key;
	NodeX* pNodeX = NULL;

	if( pEntry != NULL )
	{
		key = HashState( pEntry->GetState() );
		pNodeX = m_table[ key ];

		m_table[ key ] = pEntry;
		pEntry->SetNextTo( pNodeX  );
		m_count++;
	}
}

NodeX* HashTable::Search( char* pTarget )
{
	// Searches the table for the target state

	int key;
	NodeX* pNodeX = NULL;

	if( pTarget != NULL )
	{
		key = HashState( pTarget );
		pNodeX = m_table[ key ];

		while( pNodeX != NULL )
		{
			if( m_bBrd->IsEqual( pNodeX->GetState(), pTarget ) )
				break;
			pNodeX = pNodeX->GetNext();
		}
	}

	return pNodeX;
}

int HashTable::HashState( char* pState )
{
	// Hash function

	int rows = m_bBrd->GetRows();
	int cols = m_bBrd->GetCols();
	int shift = m_bBrd->GetFldSize();
	unsigned long n = 0;

	for( int i = 0; i < cols; i++ )
	{
		for( int j = 0; j < rows; j++ )
			n += (unsigned long)m_bBrd->GetField( j, i, pState );
		n <<= shift;
	}

	return (int)( n%m_size );
}
