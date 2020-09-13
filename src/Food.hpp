#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>

class Food : public Entity
{
    public:
        Food(int p_mapSize, int p_gridSize);
        ~Food(){};
        void update();
        void render(SDL_Renderer* renderer);
        bool isEaten() { return m_eaten; };
        void setEaten() { m_eaten = true; }

    private:
        bool m_eaten;
};