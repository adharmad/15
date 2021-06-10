// solver.h
// The definition of class Solver

#include <iostream>

#ifndef SOLVER_H
#define SOLVER_H

class Viewer;
class BFSearch;
class Solution;

class Solver
{
	public:
		Solver( Viewer* = NULL );
		~Solver();

		void Attach( Viewer* );
		void SetUp();

		void Solve();
		void Notify();

		Solution* GetSolution(){ return m_answer; }

	private:
		BFSearch* m_search;
		Solution* m_answer;
		Viewer*   m_viewer;
};

#endif
