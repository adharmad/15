// viewer.h
// The definition of class Viewer
// Functions as the user interface

#ifndef VIEWER_H
#define VIEWER_H

class Solver;
class Solution;

class Viewer
{
	public:
		Viewer( int, char** );
		~Viewer();

		void Attach( Solver* );

		int* GetInitState(){ return m_initState; }
		int* GetMessage(){ return m_message; }

		void OutputSolution();

	private:
		void SetMessage( int, char** );
		void ReadBrdInfo();
		void ReadFile();
		void ReadConsole();
		void GetDimension();
		void ShowShortSolution( Solution* );
		void ShowLongSolution( Solution* );
		void ShowBoard( int*, int, int );
		int  FindWidth( int, int );
		void DrawBorder( int );
		void DrawRow( int*, int, int, int );
		void FindTile( int, int*, int&, int& );
		void ScanForTile( int, int*, int, int, int&, int& );
		void GetNextState( int*, int, int, int, int, int );
		void SaveSolution( Solution* );

		Solver* m_solver;
		int* m_message;
		int* m_initState;
};

#endif
