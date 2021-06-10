// NodeX.cpp
// The implementation of class NodeX

#include "nodeX.h"

NodeX::NodeX( int g, char* state, Node* pParent )
{
	m_g = g;
	m_state = state;
	m_parent = pParent;
	m_next = NULL;
}

NodeX::NodeX( Node* pNode )
{
	m_next = NULL;
	if( pNode != NULL )
	{
		m_g      = pNode->GetG();
		m_state  = pNode->ReleaseState();
		m_parent = pNode->GetParent();
	}
}

NodeX::~NodeX()
{
	if( m_next != NULL )
		m_next = NULL;
}

void NodeX::SetNextTo( NodeX* pNext )
{
	m_next = pNext;
}
