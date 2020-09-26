#pragma once
#include "Entity.hpp"
#include "Food.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class Snake : public Entity
{
    public:
        Snake(int p_gridSize);
        ~Snake() {};
        void update();
        void changeDir(Direction p_dir);
        void render(SDL_Renderer* renderer);
        void extend(int p_extension);

        void setHealth(int p_health) { m_health = p_health; };
        int  const getTailSize() { return m_tail.size(); };
        bool const isSelfCollided() { return m_selfCollision; };
        bool const isDead();
        Direction getDir() { return m_dir; };
        std::vector<SDL_Rect> getTail() { return m_tail; };
    
    protected:
        std::vector<SDL_Rect> m_tail;
        Direction m_dir;
        void checkSelfCollision();
        int m_kSpeed;

    private:
        int m_health;
        bool m_selfCollision;
};