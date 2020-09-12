#include "Snake.hpp"
#include <vector>
#include <iostream>

Snake::Snake(int p_x, int p_y, int p_h, int p_w) : Entity::Entity(p_x, p_y, p_h, p_w), m_dir(Direction::kRight), m_health(1), m_kSpeed(p_w), m_selfCollision(false)
{
    m_color.r = 0x00;
    m_color.g = 0x00;
    m_color.b = 0xFF;
    m_color.a = 0x00;
}

void Snake::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, getShape());

    for (SDL_Rect& rect : m_tail)
    {
        //TODO: Parameterize tail color
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Snake::changeDir(Direction p_dir)
{
    switch (p_dir)
    {
    case Direction::kUp:
        if (m_dir != Direction::kDown) m_dir = Direction::kUp;
        break;

    case Direction::kDown:
        if (m_dir != Direction::kUp) m_dir = Direction::kDown;
        break;

    case Direction::kLeft:
        if (m_dir != Direction::kRight) m_dir = Direction::kLeft;
        break;

    case Direction::kRight:
        if (m_dir != Direction::kLeft) m_dir = Direction::kRight;
        break;
    
    default:
        break;
    }
}

void Snake::update()
{

    if (m_tail.size() > 0)
    {
        m_tail.erase(m_tail.begin());
        m_tail.emplace_back(*(getShape()));
    }
    
    switch (m_dir)
    {
    case Direction::kUp:
        decY(-m_kSpeed);
        break;

    case Direction::kDown:
        decY(m_kSpeed);
        break;

    case Direction::kLeft:
        decX(-m_kSpeed);
        break;

    case Direction::kRight:
        decX(m_kSpeed);
        break;
    
    default:
        break;
    }

    if (m_tail.size() > 3) checkSelfCollision(); // snake cannot self collided for tail len < 3
}

void Snake::extend(int p_extension)
{
    for (int i = 0; i < p_extension; i++)
    {
        m_tail.emplace_back(*(getShape()));   
    }
}

void Snake::checkSelfCollision()
{
    for(SDL_Rect& tail_rect : m_tail)
    {
        if ((tail_rect.x == getX()) && (tail_rect.y == getY()))
        {
            m_selfCollision = true;
            break;
        }
    }
}