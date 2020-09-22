#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <memory>

#include "Snake.hpp"
#include "Food.hpp"
#include "AutoSnake.hpp"
#include "Game.hpp"

// TODO: create some form of came config file
const char* kTitle = "Snake Royale";
const int kWidth = 500;
const int kHeight = 500;
const int kGridSize = 10;
const int kStartNumEnemies = 0;

int snapToGridPos(int p_point)
{
    p_point /= kGridSize;
    p_point *= kGridSize;

    return p_point;
}

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

    // set up game app
    bool gameRunning = true;
    GameApp game(kWidth, kGridSize, renderer);
    game.init();

    // start game loop
    while(game.isRunning())
    {
        game.update();
        // TODO: Create proper game loop
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    // exit and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}