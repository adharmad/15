// nodeX.h 
// The definition of NodeX 
// Inherits from class Node 

#include "node.h" 

#ifndef NODEX_H 
#define NODEX_H 

class NodeX : public Node 
{ 
	public: 
		NodeX( int = 0, char* = NULL, Node* = NULL ); 
		NodeX( Node* ); 
		~NodeX(); 

		void  SetNextTo( NodeX* ); 
		NodeX* GetNext(){ return m_next; } 

	private: 
		NodeX* m_next; 
}; 

#endif 
