#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

//TODO: Move to common definitions or better wrap somehow
enum Direction {kUp, kDown, kLeft, kRight, kNone};

class Entity
{
    public:
        Entity(int p_x, int p_y, int p_h, int p_w);
        virtual ~Entity();
        virtual void update() = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
        SDL_Rect* getShape() { return &m_shape; };
        void setShape(int p_x, int p_y, int p_w, int p_h);
        void setX(int x) { m_shape.x = x; };
        void setY(int y) { m_shape.y = y; };
        void setW(int w) { m_shape.w = w; };
        void setH(int h) {m_shape.h = h; };
        void decX(int p_x) { m_shape.x += p_x; }
        void decY(int p_y) { m_shape.y += p_y; }
    
    private:
        SDL_Rect m_shape;
        
};