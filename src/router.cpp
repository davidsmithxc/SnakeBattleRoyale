#include "Router.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include <iostream>

void Router::linear(Snake* p_snake, Food* p_food)
{
    int x_dist = p_snake->getX() - p_food->getX();
    int y_dist = p_snake->getY() - p_food->getY();
    Direction dir_to_food = p_snake->getDir();

    if(x_dist > 0)
    {
        dir_to_food = Direction::kLeft;
    } else if (x_dist < 0) {
        dir_to_food = Direction::kRight;
    } else if (y_dist > 0) {
        dir_to_food = Direction::kUp;
    } else if (y_dist < 0){
        dir_to_food = Direction::kDown;
    }

    // if already headed in that direction, do nothing
    if (dir_to_food == p_snake->getDir()) return;
    
    // turn randomly if food is directly behind
    if ((dir_to_food % 2) == (p_snake->getDir() % 2)) p_snake->changeDir(static_cast<Direction>(rand() % Direction::kNone));
    
    // follow shortest path to food
    p_snake->changeDir(dir_to_food);
}

void Router::shortest(Snake* p_snake, Food* p_food)
{
    int x_dist = p_snake->getX() - p_food->getX();
    int y_dist = p_snake->getY() - p_food->getY();
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
    