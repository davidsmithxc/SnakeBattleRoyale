#include "Game.hpp"
#include "Entity.hpp"
#include <algorithm>

GameApp::GameApp(int p_mapSize, int p_gridSize, SDL_Renderer* p_renderer)
: m_mapSize(p_mapSize), m_gridSize(p_gridSize), m_renderer(p_renderer), m_gameRunning(false)
{
    m_numStartingEnemies = 10;
}

void GameApp::update()
{
    // handle inputs
    handleInput(); 
    
    // Run generic update on all entities
    // for (Entity* e : m_entities) e->update();
    for (std::shared_ptr<Snake> s : m_snakes) s->update();
    m_food->update();

    // check snake self-collision state
    if (m_player->isSelfCollided())
    {
        m_player->setHealth(0);
        m_gameRunning = false;
        return;
    }

    // check if food is eaten
    for (std::shared_ptr<Snake> &s : m_snakes)
    {
        if (checkWallCollision(s.get()))
        {
            s->setHealth(0);
            if(s == m_player) m_gameRunning = false;
        }

        if(checkSnakeAteFood(s.get()))
        {
            s->extend(1);
            setRandomPosition(m_food.get());
        }

        // TODO: Check collisions in a thread
        for (std::shared_ptr<Snake> &s2 : m_snakes)
        {
            if (s != s2)
            {
                if(checkSnakeCollision(s.get(), s2.get())) s2->setHealth(0);
            }
        }
        
        if (s != m_player) routeToFood(s.get());
    }

    // remove dead snakes
    
    m_snakes.erase(std::remove_if(
        m_snakes.begin()+1, // first element is player
        m_snakes.end(),
        [](const std::shared_ptr<Snake>& s)
        { return s->isDead();}),
        m_snakes.end()
    );

    // Do rendering
    SDL_SetRenderDrawColor(m_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(m_renderer);

    // TODO: Use dynamic_cast w/ single list of entitities
    // for (Entity* e : m_entities) e->render(m_renderer);
    for (std::shared_ptr<Snake> s : m_snakes) s->render(m_renderer);
    m_food->render(m_renderer);
            
    SDL_RenderPresent(m_renderer);
}

void GameApp::init()
{
    // Make specific entities
    m_food = std::make_shared<Food>(m_gridSize);
    m_player = std::make_shared<Snake>(m_gridSize);
    std::vector<std::shared_ptr<AutoSnake>> enemies;

    // Init player and food pos
    setRandomPosition(m_food.get());
    setRandomPosition(m_player.get());
    m_snakes.push_back(m_player);

    // Push back player first to ensure player calculted first, food,
    // TODO: Use dynamic_cast w/ single list of entitities. dynamic_cast can check
    //       for applicability in game logic
    // m_entities.push_back(m_player.get());

    
    for (int i = 0; i < m_numStartingEnemies; i++)
    {
        m_snakes.emplace_back(std::make_shared<AutoSnake>(m_gridSize));
        // Snake* tmp_snake_ptr = m_enemies.back().get();
        setRandomPosition(m_snakes.back().get());
    }

    // ensure food is updated last so
    // m_entities.push_back(m_food.get());

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
    int x_dist = p_snake->getX() - m_food->getX();
    int y_dist = p_snake->getY() - m_food->getY();
    Direction dir_to_food = Direction::kNone;

    if (std::abs(x_dist) > std::abs(y_dist))
    {
        if(x_dist > 0)
        {
            dir_to_food = Direction::kLeft;
        } else {
            dir_to_food = Direction::kRight;
        }
    } else {

        if(y_dist > 0)
        {
            dir_to_food = Direction::kUp;
        } else{
            dir_to_food = Direction::kDown;
        }
    }

    // if already headed in that direction, do nothing
    if (dir_to_food == p_snake->getDir()) return;
    
    // turn randomly if food is directly behind
    if ((dir_to_food % 2) == (p_snake->getDir() % 2)) p_snake->changeDir(static_cast<Direction>(rand() % Direction::kNone));
    
    // follow shortest path to food
    p_snake->changeDir(dir_to_food);

}

bool GameApp::checkSnakeCollision(Snake* p_snakeA, Snake* p_snakeB)
{
    SDL_Rect headA = *(p_snakeA->getShape());
    for (SDL_Rect &t : p_snakeB->getTail())
    {
        if((t.x == headA.x) && (t.y == headA.y)) return true;
    }

    return false;
}

bool GameApp::checkWallCollision(Snake* p_snake)
{
    return ((p_snake->getX() < 0)
            || (p_snake->getY() < 0)
            || (p_snake->getX() > m_mapSize)
            || (p_snake->getY() > m_mapSize)
            );
}