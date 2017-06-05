# Inunda isto
[![Build Status](https://travis-ci.org/Yaakushi/inunda-isto.svg?branch=master)](https://travis-ci.org/Yaakushi/inunda-isto)

"_Inunda isso_" (A literal translation of 'Flood it') is a solver for the flood fill puzzle known as 'Flood it' (and its variants). It was developed for the UFPR's Artificial Inteligence course.

## Compiling

A simple `make` on the root directory will suffice to build the solver on the "bin" folder.

Likewise, `make mapgen` will build the _Nightmarish Map Generator_, a tool designed to generate maps which should be hard to optimally solve to an artifial agent.

## Usage
### Solver
The solver program doesn't support passing parameters through the command line.

Its first line of input takes 3 integer arguments which describe the puzzle, in this order: 

`[number of lines] [number of columns] [number of columns]`

Then, for the next `[number of lines]` lines of input, the program will take `[number of columns]` integers, each one representing that tile's colors (ranging from 1 to `[number of colors`]).

The output is composed by two lines, the first containing a single integer (_n_) with the number os steps in the generated plan to solve the puzzle. _n_ integers will follow in the second line, representing the colors in the plan.

### Nightmarish Map Generator

TBD.
