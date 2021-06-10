This program solves the 15 sliding tile puzzle. Two
options for the search algorithm (A* or IDA*) and two
options for heuristics (the Manhattan Distance heuristic
or the Misplaced tile heuristic) are available.

It also has some other features added. The user can
specify the dimension of the puzzle. The default is
set to 4x4, if no information on the puzzle dimension
is given.

The puzzle problem can be input from a file, and the
solution can be output to a file as well. If the
user wants to specify a dimension other than the
default one and input a problem from a file, the
input file must have the dimension info followed by
the problem itself.

The following is the command options that the user
can enter at the command prompt to specify which of
the features to be needed.

Search Algorithms
-astar	A* algorithm
-id		IDA* algorithm

Heuristics
-mh		Manhattan Distance
-mt		Misplaced Tiles

Display Option
-v		Displays the sequence of the whole state
		from the problem state to the goal state

File I/O Options
-rf		Reads a puzzle problem from a file
-wf		Writes a solution to a file
