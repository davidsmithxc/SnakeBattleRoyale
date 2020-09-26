#pragma once
#include "Snake.hpp"
#include <iostream>

class AutoSnake : public Snake
{
    public:
        AutoSnake(int p_gridSize);
        ~AutoSnake() {};
        // void update();
    private:
        void routeToFood();
};