// ManhattanDist.cpp
// The implementation of class ManhattanDist

#include <stdlib.h>
#include "bitRecord.h"
#include "manhattanDist.h"

ManhattanDist::ManhattanDist( BitRecord* bBrd ) : Heuristics( bBrd )
{
	int rows = m_bBrd->GetRows();
	int cols = m_bBrd->GetCols();

	CreateTable( rows, cols );
	InitTable( rows, cols );
}

ManhattanDist::~ManhattanDist()
{
	int i, j;
	int rows = m_bBrd->GetRows();
	int cols = m_bBrd->GetCols();

	for( i = 0; i < rows; i++ )
		for( j = 0; j < cols; j++ )
			delete [] m_tbl[ i ][ j ];
	for( i = 0; i < rows; i++ )
		delete [] m_tbl[ i ];
	delete [] m_tbl;
}

void ManhattanDist::CreateTable( int rows, int cols )
{
	// builds 3D-array for a table

	int i, j;
	int sq = rows*cols;

	m_tbl = new int**[ rows ];
	for( i = 0; i < rows; i++ )
		m_tbl[ i ] = new int*[ cols ];
	for( i = 0; i < rows; i++ )
		for( j = 0; j < cols; j++ )
			m_tbl[ i ][ j ] = new int[ sq ];
}

void ManhattanDist::InitTable( int rows, int cols )
{
	// creates a look-up table which contains
	// MH dist value for each tile position

	int i, j, k, r, c;
	int sq = rows*cols;

	for( i = 0; i < rows; i++ )
		for( j = 0; j < cols; j++ )
			for( k = 0; k < sq; k++ )
			{
				if( k == 0 )
					m_tbl[ i ][ j ][ k ] = 0;
				else
				{
					r = k/cols;
					c = k%cols;
					m_tbl[ i ][ j ][ k ] = abs( i - r ) + abs( j - c );
				}
			}
}

int ManhattanDist::ComputeH( char* rec )
{
	int i, j, k;
	int rows = m_bBrd->GetRows();
	int cols = m_bBrd->GetCols();
	int h = 0;

	m_bBrd->SetRecord( rec );
	for( i = 0; i < rows; i++ )
		for( j = 0; j < cols; j++ )
		{
			k = m_bBrd->GetField( i, j );
			h += m_tbl[ i ][ j ][ k ];
		}
	m_bBrd->ReleaseRecord();

	return h;
}
