#include "sdlMaze.h"

SDLMaze::SDLMaze() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        "Ben and Landon's Amazing Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void SDLMaze::drawBorder(int x, int y, int rows, int cols, int width) {
    SDL_RenderDrawLine(renderer,x,y, x + cols * width, y);
    SDL_RenderDrawLine(renderer,x,y + width, x, y + rows * width);
    SDL_RenderDrawLine(renderer,x + cols * width,y, x + cols * width, y + (rows - 1) * width);
    SDL_RenderDrawLine(renderer,x,y + rows * width, x + cols * width, y + rows * width);

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

void SDLMaze::drawMaze(std::vector<struct Wall> wallList) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 0; i < wallList.size(); ++i) {
        SDL_RenderDrawLine(renderer, wallList[i].x1, wallList[i].y1, wallList[i].x2, wallList[i].y2);
    }
}