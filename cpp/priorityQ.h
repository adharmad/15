// priorityQ.h 
// The definotion of class PriorityQ 
// Based on heap 

#ifndef PRIORITYQ_H 
#define PRIORITYQ_H 

#define INITSIZE 32 
#define PARENT (i-1)/2 
#define LEFT   2*i+1 
#define RIGHT  2*i+2 

class Node; 
class BitRecord; 
class Heuristics; 

class PriorityQ 
{ 
	public: 
		PriorityQ( Heuristics*, int = INITSIZE ); 
		~PriorityQ(); 

		void  Enqueue( Node* ); 
		Node* Dequeue(); 

		void  MakeQueue(); 
		void  KillQueue(); 

	private: 
		void ExpandQueue(); 
		void BuildQueue(); 
		void Heapify( int ); 
		int  FindKey( Node* ); 

		Node** m_heap; 
		int m_hSize; 
		int m_qSize; 
		int m_size; 
		Heuristics* m_h; 
}; 

#endif 
