#include "../Models/UnionFind.h"
#include "../Models/wall.h"
#include <SDL.h>

#include <vector>
#include <ctime>
#include <cstdlib>

const int WIDTH = 30;
const int CELL_SIZE = 30;
const int X0 = 50;
const int Y0 = 50;
const int N = 4;
const int M = 5;

int main(int argc, char* argv[]) {
    std::vector<int> board;
    std::vector<struct Wall> wallList;
    board.reserve(N*M);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            board.push_back(i*M + j);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {

            if (j < M - 1){
            struct Wall wall1 = {board[i*M + j], board[i*M + j + 1], X0 + i * WIDTH, X0 + (i+1) * WIDTH, Y0 + (j+1) * 30, Y0 + (j+1) * 30};
            wallList.push_back(wall1);
            }

            if (i < N-1) {
                struct Wall wall2 = {board[i*M + j], board[(i+1)*M + j], X0 + (i+1) * WIDTH, X0 + (i+1) * WIDTH, Y0 + (j) * 30, Y0 + (j+1) * 30};
                wallList.push_back(wall2);
            }

        }
    }
    
    //add SDL code to draw grid
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Ben and Landon's Amazing Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    UnionFind list(N*M);
    srand(time(0));

    while(!list.connected(0, N*M-1)) {

        if (wallList.empty()) {
            std::cout << "No more removable walls while start and end not connected.\n";
            break;
        }
        //generate random number
        int randomNum = rand() % wallList.size();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i < wallList.size(); ++i) {
            SDL_RenderDrawLine(renderer, wallList[i].x1, wallList[i].y1, wallList[i].x2, wallList[i].y2);
            SDL_RenderPresent(renderer);

        }

        //choose random wall
        struct Wall w = wallList[randomNum];
        if (!list.connected(w.cell1, w.cell2)) {
            
            //remove the wall
            list.unite(w.cell1, w.cell2);
            wallList.erase(wallList.begin() + randomNum);
        }

    }
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i < wallList.size(); ++i) {
        SDL_RenderDrawLine(renderer, wallList[i].x1, wallList[i].y1, wallList[i].x2, wallList[i].y2);
    }

    //draw border
    SDL_RenderDrawLine(renderer,X0,Y0, X0 + N * WIDTH, Y0);
    SDL_RenderDrawLine(renderer,X0,Y0 + WIDTH, X0, Y0 + M * WIDTH);
    SDL_RenderDrawLine(renderer,X0 + N * WIDTH,Y0, X0 + N * WIDTH, Y0 + (M - 1) * WIDTH);
    SDL_RenderDrawLine(renderer,X0,Y0 + M * WIDTH, X0 + N * WIDTH, Y0 + M * WIDTH);


    SDL_RenderPresent(renderer);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}