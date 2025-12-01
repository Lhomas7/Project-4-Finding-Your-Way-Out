#ifndef SDL_MAZE_H
#define SDL_MAZE_H

#include "../Models/mazeModel.h"
#include <SDL.h>
#include <vector>
#include <iostream>

class SDLMaze {
    SDL_Renderer* renderer;
    SDL_Window* window;

    public:
        SDLMaze();
        void drawBorder(int, int, int, int, int);
        void drawMaze(std::vector<struct Wall>);
        void drawPath(std::vector<int>, int, int);
};

#endif