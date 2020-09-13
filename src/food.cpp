#include <SDL2/SDL.h>
#include <Food.hpp>

Food::Food(int p_mapSize, int p_gridSize) : Entity::Entity(p_mapSize, p_gridSize), m_eaten(false)
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
    //TODO: Add snake<->food messaging to remove game logic check of food eaten.
    //TODO: Make this method threadsafe
    if (m_eaten)
    {
        setRandomPosition();
        m_eaten = false;
    };
}