#include "../include/utils.h"

void Utils::snapToGrid(SDL_FPoint& point)
{
    if (point.x < 0)
    {
        point.x = (int)(point.x / gridSize) * gridSize - gridSize;
    }

    else
    {
        point.x = (int)(point.x / gridSize) * gridSize;
    }

    if (point.y < 0)
    {
        point.y = (int)(point.y / gridSize) * gridSize - gridSize;
    }

    else
    {
        point.y = (int)(point.y / gridSize) * gridSize;
    }
}
