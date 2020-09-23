#pragma once
#include "Snake.hpp"

class AutoSnake : public Snake
{
    public:
        AutoSnake(int p_gridSize);
        ~AutoSnake() {};
        void update();
    private:
        void routeToFood();
};