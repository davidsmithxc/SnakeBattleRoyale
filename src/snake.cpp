#include "Snake.hpp"
#include <vector>
#include <iostream>

Snake::Snake(int p_x, int p_y, int p_h, int p_w) : Entity::Entity(p_x, p_y, p_h, p_w)
{
    m_dir = Direction::kRight;
    // extend(10);
}

void Snake::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
    SDL_RenderFillRect(renderer, getShape());

    for (SDL_Rect& rect : m_tail)
    {
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
    constexpr int kSpeed = 5;

    if (!m_tail.empty())
        m_tail.erase(m_tail.begin());
        m_tail.emplace_back(*(getShape()));
    
    switch (m_dir)
    {
    case Direction::kUp:
        decY(-kSpeed);
        break;

    case Direction::kDown:
        decY(kSpeed);
        break;

    case Direction::kLeft:
        decX(-kSpeed);
        break;

    case Direction::kRight:
        decX(kSpeed);
        break;
    
    default:
        break;
    }
}

void Snake::extend(int p_extension)
{
    for (int i = 0; i < p_extension; i++)
    {
        m_tail.emplace_back(*(getShape()));   
    }
}