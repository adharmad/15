// bitRecord.h

// The definifion of class BitRecord
// Class BitRecord handles all low level bitwise
// operations and hides them from the rest of
// the program.
// A series of bits representing one number is
// considered a field, and a game state consisting
// of fields are designated as record.

#include <iostream>

#ifndef BITRECORD_H
#define BITRECORD_H

class BitRecord
{
	public:
		BitRecord( int = 0, int = 0 );
		~BitRecord();

		void  SetUp( int = 0, int = 0 );
		void  GenRecord( int* = NULL );
		void  DelRecord();
		void  FillRecord( int* );
		char* DupRecord( char* = NULL );

		int   GetRows(){ return m_rows; }
		int   GetCols(){ return m_cols; }
		int   GetFldSize(){ return m_fSize; }
		void  SetRecord( char* );
		char* GetRecord(){ return m_rec; }
		char* ReleaseRecord();

		char* SwapFields( int, int, int, int, char* = NULL );
		char* SetField( int, int, int, char* = NULL );
		int   GetField( int, int, char* = NULL );
		bool  IsEqual( char*, char* = NULL );
		bool  FindNull( int&, int&, char* = NULL );

		void  ShowRec();
		void  ShowBits( int, int );

	private:
		void Cache( char* );
		void Decache(){ m_rec = m_cache; }
		int  SizeField();
		int  SizeRecord();
		int  FindFieldInd( int, int );
		int  FindBitInd( int, int );
		int  IncBitInd( int&, int& );
		void SetBit( int, int );
		void OffBit( int, int );
		int  GetBit( int, int );

		char* m_rec;
		char* m_cache;
		int   m_rows;
		int   m_cols;
		int   m_rSize;
		int   m_fSize;
};

#endif
