// Node.cpp
// The implementation of class Node

#include "node.h"

Node::Node( int g, char* state, Node* pParent )
{
	m_g = g;
	m_state = state;
	m_parent = pParent;
}

Node::~Node()
{
	if( m_state != NULL )
		delete [] m_state;
	if( m_parent != NULL )
		m_parent = NULL;
}

void Node::SetG( int g )
{
	m_g = g;
}

void Node::SetState( char* state )
{
	m_state = state;
}

void Node::SetParent( Node* pParent )
{
	m_parent = pParent;
}

char* Node::ReleaseState()
{
	char* tmp = m_state;

	m_state = NULL;

	return tmp;
}
