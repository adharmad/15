// Solution.cpp
// The implementation of class Solution

#include "solution.h"

Solution::Solution( int* moves, int count )
{
	m_moves = moves;
	m_mvCount = count;
}

Solution::~Solution()
{
	delete [] m_moves;
}
