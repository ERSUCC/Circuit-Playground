#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Resource
{

public:
    static SDL_Texture* getImage(SDL_Renderer* renderer, const char* path);
    static SDL_Texture* getImage(SDL_Renderer* renderer, const char* path, const SDL_Color& color);

};
