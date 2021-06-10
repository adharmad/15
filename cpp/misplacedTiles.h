// misplacedTiles.h
// The definition of class MisplacedTiles
// Inherits from class Heuristics

#include "heuristics.h"

#ifndef MISPLACEDTILES_H
#define MISPLACEDTILES_H

class MisplacedTiles : public Heuristics
{
	public:
		MisplacedTiles( BitRecord* );

		virtual int ComputeH( char* );
};

#endif
