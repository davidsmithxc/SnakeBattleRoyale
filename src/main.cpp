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
const int kWidth = 500;
const int kHeight = 500;
const int kGridSize = 10;

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

    // set up game loop
    bool gameRunning = true;
    SDL_Event event;
    Snake player_snake(snapToGridPos(0), snapToGridPos(0), kGridSize, kGridSize);
    Food food(snapToGridPos(kWidth / 2), snapToGridPos(kHeight / 2), kGridSize, kGridSize);

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

        // check snake-wall collision
        if ((player_snake.getX() < 0) || (player_snake.getY() < 0) || (player_snake.getX() > kWidth) || (player_snake.getY() > kHeight))
        {
            player_snake.setHealth(0);
            gameRunning = false;
            break;
        }

        // check snake self-collision state
        if (player_snake.isSelfCollided())
        {
            player_snake.setHealth(0);
            gameRunning = false;
            break;
        }
        
        // check food eaten
        if (player_snake == food)
        {
            int new_x = ((rand() % kWidth) / kGridSize) * kGridSize;
            int new_y = ((rand() % kHeight) / kGridSize) * kGridSize;
            food.setPosition(new_x, new_y);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    // exit and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}