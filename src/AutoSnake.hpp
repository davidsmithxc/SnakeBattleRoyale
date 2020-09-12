#pragma once
#include "Snake.hpp"

class AutoSnake : public Snake
{
    public:
        AutoSnake(int p_x, int p_y, int p_h, int p_w, Food* p_food);
        ~AutoSnake() {};
        void update();
    private:
        void routeToFood();
        Food* m_food;
};