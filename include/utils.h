#pragma once

#include <SDL.h>

class Utils
{

public:
    static void snapToGrid(SDL_FPoint& point);

    static constexpr float gridSize = 64;

};
