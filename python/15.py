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
  astar	        A* algorithm 
  idastar	IDA* algorithm 

Heuristics:
  manhdist	Manhattan Distance 
  misptile	Misplaced Tiles
 
Display Option:
  -v		Displays the sequence of the whole state 
 		from the problem state to the goal state 

The inputs are a series of 15 numbers accepted on the command line. The 
blank is represented by _
"""

# Imports
import sys, string 
import argparse

class Node:
    def __init__(self, grid):
        self.grid = grid
        self.f = 0
        self.g = 0
        self.h = 0


class Solver:
    GOAL = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, '_']]

    def __init__(self, start, opts):
        self.start = start
        self.opts = opts

    def solve(self):
        closedSet = set()
        openSet = [self.start]

        print(self.start.grid)


def readOptions(argv):
    parser = argparse.ArgumentParser(
            usage="usage: %prog [options] <num1> <num2> ... <num15>") 

    parser.add_argument("-a", "--algorithm", 
            action="store",
            dest="algorithm",
            default="astar",
            help="Solving algorithm")
    parser.add_argument("-x", "--heuristic", 
            action="store",
            dest="heuristic",
            default="manhdist",
            help="Algorithm Heuristic")
    parser.add_argument("-v", "--verbose", 
            action="store_true",
            dest="verbose",
            default=False,
            help="Verbose Mode")

    (options, args) = parser.parse_known_args(argv)

    return options

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
        if (elems[i] != '_'):
            grid[i // 4][i % 4] = int(elems[i])
        else:
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

    # start element
    start = Node(grid)

    s = Solver(start, opts)
    s.solve()

if __name__ == '__main__':
    main(sys.argv)
