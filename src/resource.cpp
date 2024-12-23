#include "../include/resource.h"

SDL_Texture* Resource::getImage(SDL_Renderer* renderer, const char* path)
{
    return IMG_LoadTexture(renderer, path);
}


SDL_Texture* Resource::getImage(SDL_Renderer* renderer, const char* path, const SDL_Color& color)
{
    SDL_Surface* surface = IMG_Load(path);

    uint8_t* pixels = (uint8_t*)surface->pixels;

    for (unsigned int i = 0; i < surface->h * surface->pitch; i += surface->format->BytesPerPixel)
    {
        pixels[i] &= color.r;
        pixels[i + 1] &= color.g;
        pixels[i + 2] &= color.b;
        pixels[i + 3] &= color.a;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
