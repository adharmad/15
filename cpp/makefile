CC = g++

OBJS = \
	main.o \
	Astar.o \
	BFSearch.o \
	BitRecord.o \
	HashTable.o \
	Heuristics.o \
	IDAstar.o \
	ManhattanDist.o \
	MisplacedTiles.o \
	Node.o \
	NodeStack.o \
	NodeX.o \
	PriorityQ.o \
	Solution.o \
	Solver.o \
	Viewer.o

search: $(OBJS)
	$(CC) -o search $(OBJS)

main.o: viewer.h solver.h

Astar.o: \
	constants.h \
	bitRecord.h \
	heuristics.h \
	manhattanDist.h \
	misplacedTiles.h \
	priorityQ.h \
	hashTable.h \
	node.h \
	nodeX.h \
	astar.h

BFSearch.o: \
	bitRecord.h \
	node.h \
	bfsearch.h

BitRecord.o: \
	constants.h \
	bitRecord.h

HashTable.o: \
	nodeX.h \
	bitRecord.h \
	hashTable.h

Heuristics.o: \
	bitRecord.h \
	heuristics.h

IDAstar.o: \
	constants.h \
	bitRecord.h \
	heuristics.h \
	manhattanDist.h \
	misplacedTiles.h \
	nodeStack.h \
	node.h \
	nodeX.h \
	idastar.h

ManhattanDist.o: \
	bitRecord.h \
	manhattanDist.h

MisplacedTiles.o: \
	bitRecord.h \
	misplacedTiles.h

Node.o: \
	node.h

NodeStack.o: \
	nodeX.h \
	nodeStack.h

NodeX.o: \
	nodeX.h

PriorityQ.o: \
	bitRecord.h \
	heuristics.h \
	node.h \
	priorityQ.h

Solution.o: \
	solution.h

Solver.o: \
	constants.h \
	astar.h \
	idastar.h \
	solution.h \
	viewer.h \
	solver.h

Viewer.o: \
	constants.h \
	solution.h \
	solver.h \
	viewer.h

.c.o:
	$(CC) -c $*.cpp

clean:
	rm $(OBJS) search
