#include "AutoSnake.hpp"
#include "Food.hpp"
#include "Entity.hpp"
#include <iostream>

AutoSnake::AutoSnake(int p_gridSize) : Snake::Snake(p_gridSize)
{
    m_color.r = 0xFF;
    m_color.g = 0x00;
    m_color.b = 0x00;
    m_color.a = 0x00;
}

/*
void AutoSnake::update()
{
    //TODO: This section is the same as base class snake -> how to generalize?
    ///////////////////
    // start copied code
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

    // end copied code
    ///////////////////
}
*/