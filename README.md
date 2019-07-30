# Cellular Automaton
This is a collection of Cellular Automaton I have made in C++ / SFML.

## Game of Life

   The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, 
   each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated". 
   Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or 
   diagonally adjacent. At each step in time, the following transitions occur:

 - Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
 - Any live cell with two or three live neighbours lives on to the next generation.
 - Any live cell with more than three live neighbours dies, as if by overpopulation.
 - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 
## Brian's Brain

Brian's brain has 3 cell types: On, Off, and dying. 

Each generation:
    - On cells go into a dying state
    - Dying cells go into the off state
    - Off cells go into an on state, if and only if exactly 2 [Moore's] neighbours are in the On state

## Langton's Ant

Langton's ant is a two-dimensional universal Turing machine with a very simple set of rules but complex emergent behavior. It was invented by Chris Langton in 1986 and runs on a square lattice of black and white cells.

### Rules
Squares on a plane are colored variously either black or white. We arbitrarily identify one square as the "ant". The ant can travel in    any of the four cardinal directions at each step it takes. The "ant" moves according to the rules below:

- At a white square, turn 90° right, flip the color of the square, move forward one unit
- At a black square, turn 90° left, flip the color of the square, move forward one unit

## WireWorld
Wireworld is a cellular automaton first proposed by Brian Silverman in 1987, as part of his program Phantom Fish Tank.

### Rules
A Wireworld cell can be in one of four different states, usually numbered 0–3 in software, modeled by colors in the examples here:
- empty (black),
- electron head (blue),
- electron tail (red),
- conductor (yellow)

As in all cellular automata, time proceeds in discrete steps called generations (sometimes "gens" or "ticks"). Cells behave as follows:

- empty → empty,
- electron head → electron tail,
- electron tail → conductor,
- conductor → electron head if exactly one or two of the neighbouring cells are electron heads, otherwise remains conductor.

Wireworld uses what is called the Moore neighborhood, which means that in the rules above, neighbouring means one cell away (range value of one) in any direction, both orthogonal and diagonal.
