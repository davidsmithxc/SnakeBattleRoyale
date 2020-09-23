#include "Entity.hpp"
#include <iostream>

Entity::Entity(int p_gridSize) : m_gridSize(p_gridSize)
{
    setW(p_gridSize);
    setH(p_gridSize);
    // setRandomPosition();
}

void Entity::setShape(int p_x, int p_y, int p_w, int p_h)
{
    m_shape.x = p_x;
    m_shape.y = p_y;
    m_shape.h = p_h;
    m_shape.w = p_w;
}

void Entity::setPosition(int p_x, int p_y)
{
    m_shape.x = p_x;
    m_shape.y = p_y;
}

bool Entity::operator==(const Entity &rhs) const
{
    return (this->m_shape.x == rhs.getX()) && (this->m_shape.y == rhs.getY());
}

// TODO: Deprecate -> moved to GameApp
/*
void Entity::setRandomPosition()
{
    int new_x = ((rand() % m_mapSize) / m_gridSize) * m_gridSize;
    int new_y = ((rand() % m_mapSize) / m_gridSize) * m_gridSize;
    
    new_x = snapToGrid(new_x);
    new_y = snapToGrid(new_y);
    setPosition(new_x, new_y);
}
*/

int Entity::snapToGrid(int p_x)
{
    p_x /= m_gridSize;
    p_x *= m_gridSize;

    return p_x;

}