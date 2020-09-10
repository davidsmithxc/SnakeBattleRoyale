#pragma once
#include "Entity.hpp"
#include <SDL2/SDL.h>

class Food : public Entity
{
    public:
        Food(int p_x, int p_y, int p_h, int p_w);
        ~Food(){};
        void update();
        void render(SDL_Renderer* renderer);
        bool isEaten() { return m_eaten; };
    private:
        bool m_eaten;
};