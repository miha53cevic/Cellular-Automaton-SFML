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
    -On cells go into a dying state
    -Dying cells go into the off state
    -Off cells go into an on state, if and only if exactly 2 [Moore's] neighbours are in the On state
