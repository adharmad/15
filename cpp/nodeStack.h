// nodeStack.h 
// The definition of class NodeStack 

#ifndef NODESTACK_H 
#define NODESTACK_H 

class NodeX; 

class NodeStack 
{ 
	public: 
		NodeStack(); 
		~NodeStack(); 

		void   Push( NodeX* ); 
		NodeX* Pop(); 
		NodeX* PopOff(); 

		void  MakeStack(); 
		void  KillStack(); 

	private: 
		NodeX* m_top; 
		NodeX* m_bttm; 
		int    m_count; 
}; 

#endif 
