// Viewer.cpp
// The implementation of class Viewer

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "constants.h"
#include "viewer.h"
#include "solver.h"
#include "solution.h"

using namespace std;

Viewer::Viewer( int count, char** opts )
{
	m_message = NULL;
	m_initState = NULL;

	SetMessage( count, opts );
	ReadBrdInfo();
}

Viewer::~Viewer()
{
	m_solver = NULL;
	if( m_message != NULL )
		delete [] m_message;
	if( m_initState != NULL )
		delete [] m_initState;
}

void Viewer::Attach( Solver* pSol )
{
	m_solver = pSol;
}

void Viewer::SetMessage( int count, char** opts )
{
	m_message = new int[ MSGMAX ];
	for( int i = 0; i < MSGMAX; i++ )
		m_message[ i ] = 0;
	for( int j = 1; j < count; j++ )
	{
		if( strcmp( opts[ j ], IDAOPT ) == 0 )
			m_message[ SRCHTYPE ] = OPTSET;
		else if( strcmp( opts[ j ], MTOPT ) == 0 )
			m_message[ HEURTYPE ] = OPTSET;
		else if( strcmp( opts[ j ], VBSOPT ) == 0 )
			m_message[ DISPTYPE ] = OPTSET;
		else if( strcmp( opts[ j ], RFOPT ) == 0 )
			m_message[ RDFLSPEC ] = OPTSET;
		else if( strcmp( opts[ j ], WFOPT ) == 0 )
			m_message[ WTFLSPEC ] = OPTSET;
		else if( strcmp( opts[ j ], DIMOPT ) == 0 )
			m_message[ DIMSPECR ] = OPTSET;
	}
}

void Viewer::ReadBrdInfo()
{
	if( m_message[ RDFLSPEC ] == OPTSET )
		ReadFile();
	else
		ReadConsole();
}

void Viewer::ReadFile()
{
	int i;
	int sq;
	char fname[ FILEMAX ];
	ifstream inFile;

	cout << "Input Filename : ";
	cin.getline( fname, FILEMAX );
	inFile.open( fname );

	if( m_message[ DIMSPECR ] == OPTSET )
	{
		inFile >> m_message[ DIMSPECR ];
		inFile >> m_message[ DIMSPECC ];
	}
	else
	{
		m_message[ DIMSPECR ] = DEFROWS;
		m_message[ DIMSPECC ] = DEFCOLS;
	}
	sq = m_message[ DIMSPECR ]*m_message[ DIMSPECC ];
	m_initState = new int[ sq ];
	for( i = 0; i < sq && !inFile.eof(); i++ )
		inFile >> m_initState[ i ];

	if( i < sq )
	{
		cout << endl;
		cout << "Insufficient Input : Aborting!" << endl << endl;
		exit( 1 );
	}
}

void Viewer::ReadConsole()
{
	int sq;
	char clr;

	if( m_message[ DIMSPECR ] == OPTSET )
		GetDimension();
	else
	{
		m_message[ DIMSPECR ] = DEFROWS;
		m_message[ DIMSPECC ] = DEFCOLS;
	}
	sq = m_message[ DIMSPECR ]*m_message[ DIMSPECC ];
	m_initState = new int[ sq ];
	cout << "Initial State : ";
	for( int i = 0; i < sq; i++ ) {
		cin >> m_initState[ i ];
		cout << "entered " << m_initState[ i ] << endl;
	}
	cin.get( clr );
}

void Viewer::GetDimension()
{
	char clr;

	cout << "Rows : ";
	cin >> m_message[ DIMSPECR ];
	cout << "Cols : ";
	cin >> m_message[ DIMSPECC ];
	cin.get( clr );
}

void Viewer::OutputSolution()
{
	Solution* sol = m_solver->GetSolution();

	if( m_message[ DISPTYPE ] != OPTSET )
		ShowShortSolution( sol );
	else
		ShowLongSolution( sol );

	if( m_message[ WTFLSPEC ] == OPTSET )
		SaveSolution( sol );
}

void Viewer::ShowShortSolution( Solution* sol )
{
	int n = sol->GetCount();
	int* path = sol->GetMoves();

	cout << endl;
	cout << "Number of Moves : " << n << endl;
	for( int i = 0; i < n; i++ )
		cout << path[ i ] << " ";
	cout << endl << endl;
}

void Viewer::ShowLongSolution( Solution* sol )
{
	int rows = m_message[ DIMSPECR ];
	int cols = m_message[ DIMSPECC ];
	int nulR = rows;
	int nulC = cols;
	int nxtR, nxtC;
	int n = sol->GetCount();
	int* path = sol->GetMoves();

	cout << endl;
	cout << "Number of Moves : " << n << endl;
	cout << endl;
	ShowBoard( m_initState, rows, cols );
	FindTile( 0, m_initState, nulR, nulC );
	nxtR = nulR;
	nxtC = nulC;
	for( int i = 0; i < n; i++ )
	{
		ScanForTile( path[ i ], m_initState, rows, cols, nxtR, nxtC );
		GetNextState( m_initState, cols, nulR, nulC, nxtR, nxtC );
		cout << "Next Move : " << path[ i ] << endl;
		cout << endl;
		ShowBoard( m_initState, rows, cols );
		nulR = nxtR;
		nulC = nxtC;
	}
}

void Viewer::ShowBoard( int* brd, int r, int c )
{
	int wd = FindWidth( r, c );

	DrawBorder( wd*c + c + 1 );
	for( int i = 0; i < r; i++ )
		DrawRow( brd, i, c, wd );
	DrawBorder( wd*c + c + 1 );
}

int Viewer::FindWidth( int r, int c )
{
	int n = 1;
	int i;

	for( i = 0; n <= r*c; i++ )
		n *= 10;

	return i;
}

void Viewer::DrawBorder( int lng )
{
	for( int i = 0; i < lng; i++ )
		cout << "-";
	cout << endl;
}

void Viewer::DrawRow( int* brd, int r, int c, int w )
{
	cout << "|";
	for( int i = 0; i < c; i++ )
	{
		cout << setw( w ) << brd[ r*c + i ];
		if( i < c - 1 )
			cout << " ";
	}
	cout << "|" << endl;
}

void Viewer::FindTile( int tile, int* brd, int& r, int& c )
{
	int i = 0;

	while( brd[ i ] != tile )
		i++;
	r = i/c;
	c = i%c;
}

void Viewer::ScanForTile( int tile, int* brd, int R, int C, int& r, int& c )
{
	int row = r;
	int col = c;

	for( int i = 0; i < 4; i++ )
	{
		row = r + ( i - 1 )%2;
		col = c + ( i - 2 )%2;
		if( row >= 0 && row < R && col >= 0 && col < C )
			if( brd[ row*C + col ] == tile )
			{
				r = row;
				c = col;
				return;
			}
	}
	r = -1;
	c = -1;
}

void Viewer::GetNextState( int* brd, int C, int r0, int c0, int r1, int c1 )
{
	brd[ r0*C + c0 ] = brd[ r1*C + c1 ];
	brd[ r1*C + c1 ] = 0;
}

void Viewer::SaveSolution( Solution* sol )
{
	int n = sol->GetCount();
	int* path = sol->GetMoves();
	char fname[ FILEMAX ];
	ofstream outFile;

	cout << "Output Filename : ";
	cin.getline( fname, FILEMAX );
	outFile.open( fname );

	outFile << n << endl;
	for( int i = 0; i < n; i++ )
		outFile << path[ i ] << " ";

	cout << "Solution saved in file \""
		 << fname << "\"" << endl << endl;
}
