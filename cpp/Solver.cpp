// Solver.cpp
// The implementation of class Solver

#include "constants.h"
#include "viewer.h"
#include "solver.h"
#include "solution.h"
#include "astar.h"
#include "idastar.h"

Solver::Solver( Viewer* vwr )
{
	m_search = NULL;
	m_viewer = vwr;
	if( m_viewer != NULL )
		SetUp();
}

Solver::~Solver()
{
	m_viewer = NULL;
	if( m_search != NULL )
		delete m_search;
	if( m_answer != NULL )
		delete m_answer;
}

void Solver::Attach( Viewer* vwr )
{
	m_viewer = vwr;
}

void Solver::SetUp()
{
	int* msg = m_viewer->GetMessage();
	int* brd = m_viewer->GetInitState();

	if( msg[ SRCHTYPE ] != OPTSET )
		m_search = (BFSearch*)new Astar( msg, brd );
	else
		m_search = (BFSearch*)new IDAstar( msg, brd );
}

void Solver::Solve()
{
	int  n;
	int* path;

	m_search->Search();
	n = m_search->FindPathLng();
	path = new int[ n ];
	m_search->ConstructPath( path );

	delete m_search;
	m_search = NULL;

	m_answer = new Solution( path, n );
}

void Solver::Notify()
{
	// notifies the completion of search
	// to the user interface

	m_viewer->OutputSolution();
}
