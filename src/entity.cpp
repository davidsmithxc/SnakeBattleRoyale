#include "Entity.hpp"
#include <iostream>

Entity::Entity(int p_x, int p_y, int p_h, int p_w)
{
    std::cout << "Entity constructor" << std::endl;
    setShape(p_x, p_y, p_h, p_w);
}

Entity::~Entity() {};

void Entity::setShape(int p_x, int p_y, int p_w, int p_h)
{
    std::cout << "Set shape" << std::endl;
    m_shape.x = p_x;
    m_shape.y = p_y;
    m_shape.h = p_h;
    m_shape.w = p_w;
    std::cout << "Set shape done" << std::endl;
}