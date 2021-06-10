// BitRecord.cpp
// The implementation of class BitRecord

#include <iostream>
#include "constants.h"
#include "bitRecord.h"

BitRecord::BitRecord( int rows, int cols )
{
	m_rec = NULL;
	m_cache = NULL;
	SetUp( rows, cols );
}

BitRecord::~BitRecord()
{
	DelRecord();
}

void BitRecord::SetUp( int rows, int cols )
{
	if( rows*cols == 0 )
	{
		m_rows = DEFROWS;
		m_cols = DEFCOLS;
	}
	else
	{
		m_rows = rows;
		m_cols = cols;
	}
	m_fSize = SizeField();
	m_rSize = SizeRecord();
	DelRecord();
}

void BitRecord::GenRecord( int* tbl )
{
	// creates a bitwise game state
	// based on an array of integers

	DelRecord();
	m_rec = new char[ m_rSize ];
	for( int i = 0; i < m_rSize; i++ )
		m_rec[ i ] = (char)0;
	if( tbl != NULL )
		FillRecord( tbl );
}

void BitRecord::DelRecord()
{
	if( m_rec != NULL )
	{
		delete [] m_rec;
		m_rec = NULL;
	}
}

void BitRecord::FillRecord( int* tbl )
{
	for( int i = 0; i < m_rows; i++ )
		for( int j = 0; j < m_cols; j++ )
			SetField( i, j, tbl[ i*m_cols + j ] );
}

char* BitRecord::DupRecord( char* rec )
{
	char* tmp = NULL;

	if( rec != NULL )
		Cache( rec );
	if( m_rec != NULL )
	{
		tmp = new char[ m_rSize ];
		for( int i = 0; i < m_rSize; i++ )
			tmp[ i ] = m_rec[ i ];
	}
	if( rec != NULL )
		Decache();

	return tmp;
}

void BitRecord::SetRecord( char* rec )
{
	m_rec = rec;
}

char* BitRecord::ReleaseRecord()
{
	char* tmp = m_rec;

	m_rec = NULL;

	return tmp;
}

char* BitRecord::SwapFields( int r1, int c1, int r2, int c2, char* rec )
{
	int f1, f2;

	if( rec != NULL )
		Cache( rec );
	f1 = GetField( r1, c1 );
	f2 = GetField( r2, c2 );
	SetField( r1, c1, f2 );
	SetField( r2, c2, f1 );
	if( rec != NULL )
		Decache();

	return rec;
}

char* BitRecord::SetField( int row, int col, int val, char* rec )
{
	int fInd = FindFieldInd( row, col );
	int bInd = FindBitInd( row, col );
	int mask = 1;

	if( rec != NULL )
		Cache( rec );
	mask <<= ( m_fSize - 1 );
	for( int i = 0; i < m_fSize; i++ )
	{
		if( val & mask )
			SetBit( fInd, bInd );
		else
			OffBit( fInd, bInd );
		mask >>= 1;
		IncBitInd( fInd, bInd );
	}
	if( rec != NULL )
		Decache();

	return rec;
}

int BitRecord::GetField( int row, int col, char* rec )
{
	int fInd = FindFieldInd( row, col );
	int bInd = FindBitInd( row, col );
	int mask = 1;
	int value = 0;

	if( rec != NULL )
		Cache( rec );
	for( int i = 0; i < m_fSize; i++ )
	{
		value <<= 1;
		if( GetBit( fInd, bInd ) )
			value |= mask;
		IncBitInd( fInd, bInd );
	}
	if( rec != NULL )
		Decache();

	return value;
}

bool BitRecord::IsEqual( char* pRec, char* pStd )
{
	bool matched = true;

	if( pStd != NULL )
		Cache( pStd );
	if( m_rec == NULL || pRec == NULL )
		matched = false;
	else
	{
		for( int i = 0; i < m_rSize; i++ )
			if( m_rec[ i ] != pRec[ i ] )
			{
				matched = false;
				break;
			}
	}
	if( pStd != NULL )
		Decache();

	return matched;
}

bool BitRecord::FindNull( int& r, int& c, char* rec )
{
	bool found = false;

	if( rec != NULL )
		Cache( rec );
	if( m_rec != NULL )
	{
		for( r = 0; r < m_rows && !found; r++ )
			for( c = 0; c < m_cols && !found; c++ )
				if( GetField( r, c ) == 0 )
				{
					found = true;
					r--;
					c--;
				}
	}
	if( rec != NULL )
		Decache();

	return found;
}

void BitRecord::Cache( char* rec )
{
	m_cache = m_rec;
	m_rec = rec;
}

int BitRecord::SizeField()
{
	int i = 0;
	int n = 1;
	int max = (m_rows)*(m_cols) - 1;

	for(; n < max; n *= 2, i++ );
	if( n == max )
		i++;

	return i;
}

int BitRecord::SizeRecord()
{
	int bits = (m_rows)*(m_cols)*(m_fSize);
	int bytes = bits/8;

	if( bits%8 )
		bytes++;

	return bytes;
}

int BitRecord::FindFieldInd( int row, int col )
{
	return m_fSize*( row*m_cols + col )/8;
}

int BitRecord::FindBitInd( int row, int col )
{
	return m_fSize*( row*m_cols + col )%8;
}

int BitRecord::IncBitInd( int& fInd, int& bInd )
{
	int overField = 0;

	bInd++;
	if( bInd == 8 )
	{
		bInd = 0;
		fInd++;
		overField = 1;
	}

	return overField;
}

void BitRecord::SetBit( int fInd, int bInd )
{
	char mask = (char)1;

	mask <<= ( 7 - bInd );
	m_rec[ fInd ] |= mask;
}

void BitRecord::OffBit( int fInd, int bInd )
{
	char mask = (char)1;

	mask <<= ( 7 - bInd );
	mask = (~mask);
	m_rec[ fInd ] &= mask;
}

int BitRecord::GetBit( int fInd, int bInd )
{
	char mask = (char)1;

	mask <<= ( 7 - bInd );
	if( m_rec[ fInd ] & mask )
		return 1;

	return 0;
}
