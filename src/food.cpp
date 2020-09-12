#include <SDL2/SDL.h>
#include <Food.hpp>

Food::Food(int p_x, int p_y, int p_h, int p_w) : Entity::Entity(p_x, p_y, p_h, p_w), m_eaten(false)
{
    m_color.r = 0x00;
    m_color.g = 0xFF;
    m_color.b = 0x00;
    m_color.a = 0x00;
}

void Food::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, getShape());
}

void Food::update()
{
    //TODO: allow new position
}