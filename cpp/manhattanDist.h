// manhattanDist.h
// The definition of class ManhattanDist
// Inherits from class Heuristics

#include "heuristics.h"

#ifndef MANHATTANDIST_H
#define MANHATTANDIST_H

class ManhattanDist : public Heuristics
{
	public:
		ManhattanDist( BitRecord* );
		~ManhattanDist();

		virtual int ComputeH( char* );

	private:
		void CreateTable( int, int );
		void InitTable( int, int );

		int*** m_tbl;
};

#endif
