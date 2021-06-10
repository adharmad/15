// NodeStack.cpp
// The implementation of class NodeStack

#include <iostream>
#include "nodeX.h"
#include "nodeStack.h"

NodeStack::NodeStack()
{
	MakeStack();
}

NodeStack::~NodeStack()
{
	KillStack();
}

void NodeStack::MakeStack()
{
	m_top   = NULL;
	m_bttm  = NULL;
	m_count = 0;
}

void NodeStack::KillStack()
{
	NodeX* tmp = m_top;

	if( m_bttm == NULL )
	{
		while( tmp != NULL )
		{
			m_top = m_top->GetNext();
			delete tmp;
			tmp = m_top;
		}
		m_top = NULL;
		m_bttm = NULL;
		m_count = 0;
	}
}

void NodeStack::Push( NodeX* pNode )
{
	// returns a pointer to the node
	// on the top of stack

	if( m_bttm == NULL )
	{
		m_top  = pNode;
		m_bttm = pNode;
	}
	else
	{
		pNode->SetNextTo( m_top );
		m_top = pNode;
	}
	m_count++;
}

NodeX* NodeStack::Pop()
{
	return m_top;
}

NodeX* NodeStack::PopOff()
{
	// returns a pointer to the node
	// on the top of stack. The node
	// is released from the stack

	NodeX* tmp = m_top;

	if( tmp != NULL )
	{
		m_top = m_top->GetNext();
		tmp->SetNextTo( NULL );
		m_count--;
	}

	return tmp;
}
