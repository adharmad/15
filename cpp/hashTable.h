// hashTable.h
// The definition of class HashTable

#include <iostream>

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAXTBL 211

class BitRecord;
class NodeX;

class HashTable
{
	public:
		HashTable( BitRecord* = NULL, int = MAXTBL );
		~HashTable();

		void  SetBoard( BitRecord* );

		void  MakeTable();
		void  KillTable();
		void  Insert( NodeX* );
		NodeX* Search( char* );

	private:
		void DelField( NodeX* );
		int  HashState( char* );

		NodeX** m_table;
		int m_size;
		int m_count;
		BitRecord* m_bBrd;
};

#endif
