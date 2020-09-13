#pragma once
#include "Entity.hpp"
#include "Food.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Snake : public Entity
{
    public:
        Snake(int p_mapSize, int p_gridSize, Food* p_food);
        ~Snake() {};
        void update();
        void changeDir(Direction p_dir);
        void render(SDL_Renderer* renderer);
        void extend(int p_extension);

        void setHealth(int p_health) { m_health = p_health; };
        int  const getTailSize() { return m_tail.size(); };
        bool const isSelfCollided() { return m_selfCollision; };
    
    protected:
        std::vector<SDL_Rect> m_tail;
        Direction m_dir;
        void checkSelfCollision();
        void checkAteFood();
        const int m_kSpeed;
        Food* m_food;

    private:
        int m_health;
        bool m_selfCollision;
};