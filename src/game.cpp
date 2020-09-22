#include "Game.hpp"
#include "Entity.hpp"

GameApp::GameApp(int p_mapSize, int p_gridSize, SDL_Renderer* p_renderer)
: m_mapSize(p_mapSize), m_gridSize(p_gridSize), m_renderer(p_renderer), m_gameRunning(false)
{
    m_numStartingEnemies = 1;
}

void GameApp::update()
{
    // handle inputs
    handleInput(); 
    
    // Run generic update on all entities
    for (Entity* e : m_entities) e->update();

    // check snake-wall collision
    if ((m_player->getX() < 0) || (m_player->getY() < 0) || (m_player->getX() > m_mapSize) || (m_player->getY() > m_mapSize))
    {
        m_player->setHealth(0);
        m_gameRunning = false;
        return;
    }

    // check snake self-collision state
    if (m_player->isSelfCollided())
    {
        m_player->setHealth(0);
        m_gameRunning = false;
        return;
    }

    // Do rendering
    SDL_SetRenderDrawColor(m_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(m_renderer);

    for (Entity* e : m_entities) e->render(m_renderer);
            
    SDL_RenderPresent(m_renderer);
}

void GameApp::init()
{
    // Make specific entities
    m_food = std::make_shared<Food>(m_mapSize, m_gridSize);
    m_player = std::make_shared<Snake>(m_mapSize, m_gridSize, m_food.get());
    std::vector<std::shared_ptr<AutoSnake>> enemies;

    for (int i = 0; i < m_numStartingEnemies; i++)
    {
        m_enemies.emplace_back(std::make_shared<AutoSnake>(m_mapSize, m_gridSize, m_food.get()));
        // TODO: Add pointer to entities now vs. another loop!
    }

    // Push back player first to ensure player calculted first, food, 
    m_entities.push_back(m_player.get());

    for (std::shared_ptr<AutoSnake> auto_snake : m_enemies)
    {
        m_entities.push_back(auto_snake.get());
    }


    // ensure food is updated last so
    m_entities.push_back(m_food.get());

    // set game to running
    m_gameRunning = true;

}

void GameApp::setRandomPosition(Entity* p_entity)
{
    int new_x = ((rand() % m_mapSize) / m_gridSize) * m_gridSize;
    int new_y = ((rand() % m_mapSize) / m_gridSize) * m_gridSize;
    
    new_x = snapToGrid(new_x);
    new_y = snapToGrid(new_y);
    p_entity->setPosition(new_x, new_y);
}

int GameApp::snapToGrid(int p_x)
{
    p_x /= m_gridSize;
    p_x *= m_gridSize;

    return p_x;   
}

Direction GameApp::routeToFoodAstar(Snake* p_snake)
{
    // TODO: Implement Astar
    return Direction::kNone;
}

void GameApp::handleInput()
{
    while(SDL_PollEvent(&m_event))
        {
            if(m_event.type == SDL_QUIT)
            {
                m_gameRunning = false;
            } else if (m_event.type == SDL_KEYDOWN)
            {
                switch (m_event.key.keysym.sym)
                {
                case SDLK_w:
                    m_player->changeDir(Direction::kUp);
                    break;
                case SDLK_a:
                    m_player->changeDir(Direction::kLeft);
                    break;
                case SDLK_s:
                    m_player->changeDir(Direction::kDown);
                    break;
                case SDLK_d:
                    m_player->changeDir(Direction::kRight);
                    break;
                default:
                    break;
                }
            }
        }
}