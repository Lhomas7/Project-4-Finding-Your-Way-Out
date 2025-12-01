#include "../Models/mazeModel.h"
#include "../Models/UnionFind.h"
#include "../view/sdlMaze.h"
#include <cstdlib>

int main(int argc, char* argv[]) {
    int rows = 4;
    int cols = 5;
    if (argc > 1) {
        rows = atoi(argv[1]);
        cols = atoi(argv[2]);      
    }
    MazeModel maze(rows, cols);
    SDLMaze sdlMaze;
    
    UnionFind list(rows*cols);
    srand(time(0));

    while(!list.connected(0, rows*cols-1)) {

        if (maze.isEmpty()) {
            std::cout << "No more removable walls while start and end not connected.\n";
            break;
        }
        //generate random number
        int randomNum = rand() % maze.getWallList().size();

        //choose random wall
        struct Wall w = maze.getWallList()[randomNum];
        if (!list.connected(w.cell1, w.cell2)) {  
            //remove the wall
            list.unite(w.cell1, w.cell2);
            maze.removeWall(randomNum);
        }

    }
    
    //draw the maze and its border
    sdlMaze.drawMaze(maze.getWallList());
    sdlMaze.drawBorder(X0, Y0, rows, cols, WIDTH);
    
    maze.makeAdjList();
    std::vector<int> path = maze.bfs();
    sdlMaze.drawPath(path, rows, cols);
}