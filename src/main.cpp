#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Snake.hpp"
#include "Food.hpp"

// TODO: create some form of came config file
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
    Snake player_snake(0, 0, 5, 5);
    Food food(100, 100, 5, 5);

    // start game loop
    while(gameRunning)
    {
        // Handle inputs
        // TODO: Encapsulate input handler
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                gameRunning = false;
            } else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    player_snake.changeDir(Direction::kUp);
                    break;
                case SDLK_a:
                    player_snake.changeDir(Direction::kLeft);
                    break;
                case SDLK_s:
                    player_snake.changeDir(Direction::kDown);
                    break;
                case SDLK_d:
                    player_snake.changeDir(Direction::kRight);
                    break;
                default:
                    break;
                }
            }
        }
        
        
        // *** Game Logic ***
        // TODO: Move game logic
        // Update
        player_snake.update();

        // some game logic
        if (player_snake == food)
        {
            //TODO: Ensure that food is only placed on valid grid position
            food.setPosition(rand() % kWidth, rand() % kHeight);
            player_snake.extend(1);
        }

        food.update();
                
        // Do rendering
        SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(renderer);

        player_snake.render(renderer);
        food.render(renderer);

                
        SDL_RenderPresent(renderer);

        // TODO: Create proper game loop
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // exit and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}