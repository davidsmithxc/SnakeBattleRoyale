#pragma once
#include "Snake.hpp"
#include "Food.hpp"

namespace Router
{
    void linear(Snake* p_snake, Food* p_food);
    void shortest(Snake* p_snake, Food* p_food);
}