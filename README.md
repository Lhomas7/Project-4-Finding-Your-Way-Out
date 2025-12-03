# Project-4-Finding-Your-Way-Out

# Class: CPSC 3120
 # Professor: Brian Malloy
 # Authors: Landon Thomas & Ben Newton

 # This project brings together three computing ideas: 
 # 1. The BFS path-finding algorithm that finds the shortest path from start cell to goal cell.
# 2. The use of SDL2 to visualize and animate the shortest path.
# 3. The Model–View–Controller (MVC) architecture to organize code

 # To execute this algorithm, simply change the directory to the main project folder and type "make" to compile. Calling "make run" afterwards will execute the program and display the maze, which by default is a 4X5 grid. To create mazes of different size, add "ARGS= 'int1 int2'" for variable rows and columns. For example, for a 7X8 grid you would call "make" and then "make run ARGS="7 8" ".

 # The width of each wall is set to be 30, however when generating large mazes the display may not show the entire maze. To adjust this, change the WIDTH variable in the mazeModel.h file. Furthermore, the animated blue cells have been chosen to have a width of 24 to better visualize the bfs pathway.
