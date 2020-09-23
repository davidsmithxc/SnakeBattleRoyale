#pragma once
#include "Snake.hpp"

class AutoSnake : public Snake
{
    // TODO: Handle AutoSnake when health = 0
    public:
        AutoSnake(int p_gridSize);
        ~AutoSnake() {};
        void update();
    private:
        void routeToFood();
};