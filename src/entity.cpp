#include "Entity.hpp"
#include <iostream>

Entity::Entity(int p_x, int p_y, int p_h, int p_w)
{
    setShape(p_x, p_y, p_h, p_w);
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