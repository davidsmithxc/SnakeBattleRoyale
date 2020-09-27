#pragma once
#include "Snake.hpp"
#include <iostream>
#include <memory>

class AutoSnake : public Snake
{
    public:
        AutoSnake(int p_gridSize);
        ~AutoSnake() {};
        // void update();
        void (*router)(Snake*);
    private:
        void routeToFood();
};