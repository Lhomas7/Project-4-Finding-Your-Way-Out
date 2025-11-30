#include "mazeModel.h"
#include <algorithm>

MazeModel::MazeModel(int rows, int cols) : mazeRows(rows), mazeCols(cols) {
  board.reserve(rows * cols);
  wallList.reserve(((cols-1) * rows) + (cols * (rows-1))); //this calculates the number of walls needed per maze given rows and columns

  for (int i = 0; i < mazeCols; ++i) {
    for (int j = 0; j < mazeRows; ++j) {
        board.push_back(i*mazeRows + j);
    }
  }

  for (int i = 0; i < mazeCols; ++i) {
    for (int j = 0; j < mazeRows; ++j) {

      if (j < mazeRows - 1){
        struct Wall wall1 = {board[i*mazeRows + j], 
        board[i*mazeRows + j + 1], 
        X0 + i * WIDTH, 
        X0 + (i+1) * WIDTH, 
        Y0 + (j+1) * WIDTH, 
        Y0 + (j+1) * WIDTH};
        wallList.push_back(wall1);
      }

      if (i < mazeCols-1) {
        struct Wall wall2 = {board[i*mazeRows + j], 
        board[(i+1)*mazeRows + j], 
        X0 + (i+1) * WIDTH, 
        X0 + (i+1) * WIDTH, 
        Y0 + (j) * WIDTH, 
        Y0 + (j+1) * WIDTH};
        wallList.push_back(wall2);
      }

    }
  }
}

void MazeModel::removeWall(int index) {
  wallList.erase(wallList.begin() + index);
}
    