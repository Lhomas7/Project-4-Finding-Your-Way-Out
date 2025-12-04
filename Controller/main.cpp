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

    int edgesAdded = 0;
    int n = rows * cols;
    int maxEdges = n - 1;

    //while(!list.connected(0, rows*cols-1)) {
    while(edgesAdded < maxEdges && !maze.isEmpty()) {
        
        //generate random number
        int randomNum = rand() % maze.getWallList().size();

        //choose random wall
        struct Wall w = maze.getWallList()[randomNum];
        if (!list.connected(w.cell1, w.cell2)) {  
            //remove the wall
            list.unite(w.cell1, w.cell2);
            maze.removeWall(randomNum);
            ++edgesAdded;
        }

    }
    
    maze.makeAdjList();
    std::vector<int> path = maze.bfs();
    
    bool running = true;
    SDL_Event event;
    int count = 0;
    while (running) {
        sdlMaze.drawMaze(maze.getWallList());
        sdlMaze.drawBorder(X0, Y0, rows, cols, WIDTH);
        for (int i = 0; i < count; ++i) {
            sdlMaze.drawPath(path, cols, i);
        }
        if(count < path.size()){
            ++count;
        }
        SDL_RenderPresent(sdlMaze.getRenderer());
        SDL_Delay(350);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }
    }
    

}