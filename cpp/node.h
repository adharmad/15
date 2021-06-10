// node.h
// The definition of class Node

#include <iostream>

#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		Node( int = 0, char* = NULL, Node* = NULL );
		~Node();

		void  SetG( int );
		void  SetState( char* );
		void  SetParent( Node* );
		int   GetG(){ return m_g; }
		char* GetState(){ return m_state; }
		Node* GetParent(){ return m_parent; }

		char* ReleaseState();

	protected:
		int   m_g;
		char* m_state;
		Node* m_parent;
};

#endif
