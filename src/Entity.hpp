#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <iostream>

//TODO: Move to common definitions or better wrap somehow
enum Direction {kUp, kDown, kLeft, kRight, kNone};

class Entity
{
    public:
        Entity(int p_gridSize);
        ~Entity() {};
        virtual void update() = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
        SDL_Rect* getShape() { return &m_shape; };
        void setShape(int p_x, int p_y, int p_w, int p_h);
        
        void setPosition(int p_x, int p_y);
        void setX(int x) { m_shape.x = x; };
        void setY(int y) { m_shape.y = y; };

        int getX() const { return m_shape.x; }
        int getY() const { return m_shape.y; }
        void decX(int p_x) { m_shape.x += p_x; }
        void decY(int p_y) { m_shape.y += p_y; }
        bool operator==(const Entity &rhs) const;

    protected:
        SDL_Color m_color;
        //void setRandomPosition();
        int m_gridSize;
        void setW(int w) { m_shape.w = w; };
        void setH(int h) { m_shape.h = h; };
        int snapToGrid(int p_x);
    
    private:
        SDL_Rect m_shape;
        
};