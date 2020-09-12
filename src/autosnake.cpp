#include "AutoSnake.hpp"
#include "Food.hpp"
#include "Entity.hpp"
#include <iostream>

AutoSnake::AutoSnake(int p_x, int p_y, int p_h, int p_w, Food* p_food) : Snake::Snake(p_x, p_y, p_h, p_w), m_food(p_food)
{
    m_color.r = 0xFF;
    m_color.g = 0x00;
    m_color.b = 0x00;
    m_color.a = 0x00;
}

void AutoSnake::update()
{
    routeToFood();

    //TODO: This section is the same as base class snake -> how to generalize?
    ///////////////////
    // star copied code
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


void AutoSnake::routeToFood()
{
    // chance for snake to fail to take action
    if (rand() % 101 < 20) return;
    
    Direction x_dir = Direction::kNone;
    Direction y_dir = Direction::kNone;
    
    
    // set y-dir
    if(m_food->getY() > this->getY())
    {
        y_dir = Direction::kDown;

    } else if (m_food->getY() < this->getY())
    {
        y_dir = Direction::kUp;
    }

    // set x-dir
    if(m_food->getX() > this->getX())
    {
        x_dir = Direction::kRight;

    } else if (m_food->getX() < this->getX())
    {
        x_dir = Direction::kLeft;
    }

    // Decide final direction
    if ((x_dir != Direction::kNone) && !((x_dir == Direction::kUp) && (m_dir == Direction::kDown)) && !((x_dir == Direction::kDown) && (m_dir == kUp)))
    {
        m_dir = x_dir;

    } else if ((y_dir != Direction::kNone) && !((y_dir == Direction::kLeft) && (m_dir == Direction::kRight)) && !((x_dir == Direction::kRight) && (m_dir == kLeft)))
    {
        m_dir = y_dir;
    }

    // add some imperfection to the snake
    // TODO: Parameterize quality -> Base on level of snake size()
    if (rand() % 101 < 5)
    {
        m_dir = static_cast<Direction>(rand() % Direction::kNone);
    }
    
}