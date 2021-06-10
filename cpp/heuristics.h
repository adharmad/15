// heuristics.h
// The definition of class heuristics

#include <iostream>

#ifndef HEURISTICS_H
#define HEURISTICS_H

class BitRecord;

class Heuristics
{
	public:
		Heuristics( BitRecord* );
		virtual ~Heuristics(){}

		virtual int ComputeH( char* ) = 0;

	protected:
		BitRecord* m_bBrd;
};

#endif
