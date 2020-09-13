#pragma once
#include "Snake.hpp"

class AutoSnake : public Snake
{
    public:
        AutoSnake(int p_mapSize, int p_gridSize, Food* p_food);
        ~AutoSnake() {};
        void update();
    private:
        void routeToFood();
};