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

// TODO: create some form of came config file
const char* kTitle = "Snake Royale";
const int kWidth = 500;
const int kHeight = 500;
const int kGridSize = 10;
const int kStartNumEnemies = 2;

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

    //TODO: Update snake to get some world information and autoinit
    
    // Initialize entities
    std::vector<Entity*> entities;

    // Make specific entities
    std::shared_ptr<Food> food = std::make_shared<Food>(kHeight, kGridSize);
    std::shared_ptr<Snake> player_snake = std::make_shared<Snake>(kHeight, kGridSize, food.get());
    std::vector<std::shared_ptr<AutoSnake>> enemies;

    for (int i = 0; i < kStartNumEnemies; i++)
    {
        enemies.emplace_back(std::make_shared<AutoSnake>(kHeight, kGridSize, food.get()));
    }

    // Push back player first to ensure player calculted first, food, 
    entities.push_back(player_snake.get());

    for (std::shared_ptr<AutoSnake> auto_snake : enemies)
    {
        entities.push_back(auto_snake.get());
    }


    // ensure food is updated last so
    entities.push_back(food.get());

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
                    player_snake->changeDir(Direction::kUp);
                    break;
                case SDLK_a:
                    player_snake->changeDir(Direction::kLeft);
                    break;
                case SDLK_s:
                    player_snake->changeDir(Direction::kDown);
                    break;
                case SDLK_d:
                    player_snake->changeDir(Direction::kRight);
                    break;
                default:
                    break;
                }
            }
        }
        
        
        // *** Game Logic ***
        // TODO: Move game logic
        // Update
        // player_snake->update();
        // for (std::shared_ptr<AutoSnake> enemy : enemies) enemy->update();
        for (Entity* e : entities) e->update();

        // TODO: Move into snake
        // check snake-wall collision
        if ((player_snake->getX() < 0) || (player_snake->getY() < 0) || (player_snake->getX() > kWidth) || (player_snake->getY() > kHeight))
        {
            player_snake->setHealth(0);
            gameRunning = false;
            break;
        }

        // check snake self-collision state
        // TODO: Check snake self collisions
        if (player_snake->isSelfCollided())
        {
            player_snake->setHealth(0);
            gameRunning = false;
            break;
        }

        // food->update();
                
        // Do rendering
        SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(renderer);

        for (Entity* e : entities) e->render(renderer);
                
        SDL_RenderPresent(renderer);

        // TODO: Create proper game loop
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }

    // exit and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}