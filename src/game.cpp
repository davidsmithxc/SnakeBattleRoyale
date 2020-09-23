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

    // check if food is eaten
    for (Snake* &s : m_snakes)
    {
        if(checkSnakeAteFood(s))
        {
            s->extend(1);
            setRandomPosition(m_food.get());
        }

        if (s != m_player.get()) routeToFood(s);
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
    m_food = std::make_shared<Food>(m_gridSize);
    m_player = std::make_shared<Snake>(m_gridSize);
    std::vector<std::shared_ptr<AutoSnake>> enemies;

    // TODO: Loop over all entities
    // Init player and food pos
    setRandomPosition(m_food.get());
    setRandomPosition(m_player.get());
    m_snakes.push_back(m_player.get());

    // Push back player first to ensure player calculted first, food, 
    m_entities.push_back(m_player.get());

    
    for (int i = 0; i < m_numStartingEnemies; i++)
    {
        m_enemies.emplace_back(std::make_shared<AutoSnake>(m_gridSize));
        Snake* tmp_snake_ptr = m_enemies.back().get();
        setRandomPosition(tmp_snake_ptr);
        m_entities.push_back(tmp_snake_ptr);
        m_snakes.push_back(tmp_snake_ptr);
        // TODO: Add pointer to entities now vs. another loop!
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

void GameApp::routeToFoodAstar(Snake* p_snake)
{
    // TODO: Implement Astar
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

bool GameApp::checkSnakeAteFood(Snake* p_snake)
{
    return (p_snake->getX() == m_food->getX()) && (p_snake->getY() == m_food->getY());
}

void GameApp::routeToFood(Snake* p_snake)
{
    // chance for snake to fail to take action
    if (rand() % 101 < 20) return;
    
    Direction x_dir = Direction::kNone;
    Direction y_dir = Direction::kNone;
    
    
    // set y-dir
    if(m_food->getY() > p_snake->getY())
    {
        y_dir = Direction::kDown;

    } else if (m_food->getY() < p_snake->getY())
    {
        y_dir = Direction::kUp;
    }

    // set x-dir
    if(m_food->getX() > p_snake->getX())
    {
        x_dir = Direction::kRight;

    } else if (m_food->getX() < p_snake->getX())
    {
        x_dir = Direction::kLeft;
    }

    // Decide final direction
    if ((x_dir != Direction::kNone) && !((x_dir == Direction::kUp) && (p_snake->getDir() == Direction::kDown)) && !((x_dir == Direction::kDown) && (p_snake->getDir() == kUp)))
    {
        p_snake->changeDir(x_dir);

    } else if ((y_dir != Direction::kNone) && !((y_dir == Direction::kLeft) && (p_snake->getDir() == Direction::kRight)) && !((x_dir == Direction::kRight) && (p_snake->getDir() == kLeft)))
    {
        p_snake->changeDir(y_dir);
    }

    // add some imperfection to the snake
    // TODO: Parameterize quality -> Base on level of snake size()
    if (rand() % 101 < 5)
    {
        p_snake->changeDir(static_cast<Direction>(rand() % Direction::kNone));
    }
 
}