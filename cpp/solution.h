// solution.h 
// The definition of class Solution 

#ifndef SOLUTION_H 
#define SOLUTION_H 

class Solution 
{ 
	public: 
		Solution( int*, int ); 
		~Solution(); 

		int* GetMoves(){ return m_moves; } 
		int  GetCount(){ return m_mvCount; } 

	private: 
		int* m_moves; 
		int  m_mvCount; 
}; 

#endif 
