"""
This program attempts to solve the fifteen puzzle by means of an
A-star and IDA-star search algorithm.

@author: Amol P Dharmadhikari <amol.dharmadhikari@gmail.com>

This program solves the 15 sliding tile puzzle. Two options for the search
algorithm (A* or IDA*) and two options for heuristics (the Manhattan
Distance heuristic or the Misplaced tile heuristic) are available. 
 
The following is the command options that the user can enter at the command
prompt to specify which of the features to be needed. 

Search Algorithms:
  -astar	A* algorithm 
  -id		IDA* algorithm 

Heuristics:
  -mh		Manhattan Distance 
  -mt		Misplaced Tiles
 
Display Option:
  -v		Displays the sequence of the whole state 
 		from the problem state to the goal state 

The inputs are a series of 15 numbers accepted on the command line. The 
blank is represented by _
"""

# Imports
import sys, string

class Solver:
    def __init__(self, grid, opts):
        self.grid = grid
        self.opts = opts

    def solve(self):
        pass

def readOptions(argv):
    opts = {}

    for arg in argv:
        if arg.startswith('-'):
            if arg == '-astar' or arg == '-id':
                opts['algorithm'] = arg
            elif arg == '-mt' or arg == '-mh':
                opts['heuristics'] = arg
            elif arg == '-v':
                opts['verbose'] = True

    return opts

def readPuzzle(argv):
    elems = []

    for arg in argv:
        if not arg.startswith('-'):
            if arg.isdigit() or arg == '_':
                elems.append(arg)

    return elems

def getGrid(elems):
    grid = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]

    for i in range(len(elems)):
        grid[i // 4][i % 4] = elems[i]

    return grid

def main(argv):
    argv = argv[1:]

    # parse commandline options
    opts = readOptions(argv)

    # read the puzzle
    elems = readPuzzle(argv)

    # convert the elements to a grid
    grid = getGrid(elems)

    s = Solver(grid, opts)
    s.solve()

if __name__ == '__main__':
    main(sys.argv)
