// main.cpp

#include <iostream>
#include <ctype.h>
#include "viewer.h"
#include "solver.h"

using namespace std;

int main( int argc, char** argv )
{
	Viewer v( argc, argv );
	Solver s( &v );

	v.Attach( &s );
	s.Solve();
	s.Notify();

	return 0;
}
