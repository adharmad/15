// MisplacedTiles.cpp
// The implementation of class MisplacedTiles

#include "bitRecord.h"
#include "misplacedTiles.h"

MisplacedTiles::MisplacedTiles( BitRecord* bBrd )
: Heuristics( bBrd ){}

int MisplacedTiles::ComputeH( char* rec )
{
	int i, j, n;
	int rows = m_bBrd->GetRows();
	int cols = m_bBrd->GetCols();
	int h = 0;

	for( i = 0; i < rows; i++ )
		for( j = 0; j < cols; j++ )
		{
			n = m_bBrd->GetField( i, j, rec );
			if( n != 0 && n != i*cols + j )
				h++;
		}

	return h;
}
