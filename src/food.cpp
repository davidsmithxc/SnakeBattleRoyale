#include <SDL2/SDL.h>
#include <Food.hpp>

Food::Food(int p_x, int p_y, int p_h, int p_w) : Entity::Entity(p_x, p_y, p_h, p_w), m_eaten(false)
{
}

void Food::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderFillRect(renderer, getShape());
}

void Food::update()
{
    //TODO: allow new position
}