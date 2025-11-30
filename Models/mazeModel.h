#ifndef MAZE_MODEL_H
#define MAZE_MODEL_H

#include <vector>

//these ints represent the cell width as well as 
//the starting x and y (X0 and Y0)
//coordinates for representing the grid.
const int WIDTH = 30;
const int X0 = 50;
const int Y0 = 50;

struct Wall {
    int cell1;
	int cell2;
	int x1;
	int x2;
	int y1;
	int y2;
};

class MazeModel {

    std::vector<int> board;
    std::vector<struct Wall> wallList;
    int mazeRows;
    int mazeCols;
    
    public:  
        MazeModel(int, int);
        int getRows() const {return mazeRows;}
        int getCols() const {return mazeCols;}
        bool isEmpty() {return wallList.empty();}
        void removeWall(int);
        std::vector<struct Wall> getWallList() { return wallList;}

};

#endif
    