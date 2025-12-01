#include "mazeModel.h"
#include <algorithm>

MazeModel::MazeModel(int rows, int cols) : mazeRows(rows), mazeCols(cols) {
  /*board.reserve(rows * cols);
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
  }*/
  int total = rows * cols;

    board.resize(total);
    wallList.reserve((cols - 1) * rows + (rows - 1) * cols);

    // Build board: cell index = row * cols + col
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            board[r * cols + c] = r * cols + c;
        }
    }

    // Build walls
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {

            int cell = r * cols + c;

            // Wall to the right
            if (c < cols - 1) {
                int right = cell + 1;
                wallList.push_back({
                    cell, right,
                    X0 + (c+1) * WIDTH, X0 + (c+1) * WIDTH,
                    Y0 + r * WIDTH,     Y0 + (r+1) * WIDTH
                });
            }

            // Wall below
            if (r < rows - 1) {
                int down = cell + cols;
                wallList.push_back({
                    cell, down,
                    X0 + c * WIDTH,     X0 + (c+1) * WIDTH,
                    Y0 + (r+1) * WIDTH, Y0 + (r+1) * WIDTH
                });
            }
        }
    }
}

void MazeModel::removeWall(int index) {
  removed.push_back(wallList[index]);
  wallList.erase(wallList.begin() + index);
}

bool MazeModel::isRemoved(int cell1, int cell2) {
  for (struct Wall w : removed) {
    if (w.cell1 == cell1 && w.cell2 == cell2) {
      return true;
    }
  }

  return false;
}

void MazeModel::makeAdjList() {
  int total = mazeRows * mazeCols;
  adjlist.clear();
  adjlist.resize(total);

  for (int i = 0; i < total; ++i) {
    int r = i / mazeCols;
    int c = i % mazeCols;

    // right neighbor
    if (c < mazeCols - 1 && isRemoved(i, i + 1)) {
        adjlist[i].push_back(i + 1);
        adjlist[i + 1].push_back(i);
    }

    // down neighbor
    if (r < mazeRows - 1 && isRemoved(i, i + mazeCols)) {
        adjlist[i].push_back(i + mazeCols);
        adjlist[i + mazeCols].push_back(i);
    }
  }

}


std::vector<int> MazeModel::bfs() {
  int start = 0;
  int goal = (mazeRows * mazeCols) - 1;
  int n = adjlist.size();
  std::vector<bool> visited(n, false);
  std::vector<int> parent(n, -1);
  std::queue<int> q;

  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    if (curr == goal) break;

    for (int neighbor : adjlist[curr]) {
      if (!visited[neighbor]) {
        visited[neighbor] = true;
        parent[neighbor] = curr;
        q.push(neighbor);
      }
    }
  }
  // reconstruct path
  /*if (!visited[goal]) {
    std::cout << "No path from " << start << " to " << goal << "\n";
    //return;
  }*/

  std::vector<int> path;
  for (int v = goal; v != -1; v = parent[v]) {
    path.push_back(v);
  }
  std::reverse(path.begin(), path.end());
  
  return path;
}
    