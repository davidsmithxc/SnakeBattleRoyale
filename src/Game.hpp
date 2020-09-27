#pragma once
#include <vector>
#include "Entity.hpp"
#include "Snake.hpp"
#include "AutoSnake.hpp"
#include <SDL2/SDL.h>
#include <memory>

class GameApp
{
    public:
        GameApp(int p_mapSize, int p_gridSize, SDL_Renderer* p_renderer);
        ~GameApp(){};
        void update();
        void init();
        bool isRunning() { return m_gameRunning; };
    
    private:
        // Game entities
        std::vector<std::shared_ptr<Snake>> m_snakes;
        std::shared_ptr<Food> m_food;
        std::shared_ptr<Snake> m_player;
        
        // Game parameters
        int m_mapSize;
        int m_gridSize;
        int m_numStartingEnemies;

        // Utils
        SDL_Renderer* m_renderer;
        SDL_Event m_event;
        void handleInput();
        bool m_gameRunning;

        void setRandomPosition(Entity* p_entity);
        bool checkSnakeCollision(Snake* p_snakeA, Snake* p_snakeB);
        bool checkSnakeAteFood(Snake* p_snake);
        bool checkWallCollision(Snake* p_snake);        
};