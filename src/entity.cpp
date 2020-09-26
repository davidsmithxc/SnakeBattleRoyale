#include "Entity.hpp"
#include <iostream>

Entity::Entity(int p_gridSize) : m_gridSize(p_gridSize)
{
    setW(p_gridSize);
    setH(p_gridSize);
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
    m_shape.x = snapToGrid(p_x);
    m_shape.y = snapToGrid(p_y);
}

void Entity::setX(int p_x)
{
    m_shape.x = snapToGrid(p_x);
}

void Entity::setY(int p_y)
{
    m_shape.y = snapToGrid(p_y);
}

bool Entity::operator==(const Entity &rhs) const
{
    return (this->m_shape.x == rhs.getX()) && (this->m_shape.y == rhs.getY());
}

int Entity::snapToGrid(int p_x)
{
    p_x /= m_gridSize;
    p_x *= m_gridSize;

    return p_x;

}