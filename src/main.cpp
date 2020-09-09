#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

const char* kTitle = "Snake Royale";
const int kWidth = 1280;
const int kHeight = 720;

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed. SDL_Error: " << SDL_GetError() << std::endl;
    
    // Initialize window
    SDL_Window* window = SDL_CreateWindow(kTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kWidth, kHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // set up game loop
    bool gameRunning = true;
    SDL_Event event;

    // start game loop
    while(gameRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                gameRunning = false;
        }

        SDL_RenderClear(renderer);
                
        SDL_RenderPresent(renderer);
    }

    // exit and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}