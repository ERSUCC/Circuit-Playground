#include "../include/gui.h"

Button::Button(const float x, const float y, const float width, const float height) :
    x(x), y(y), width(width), height(height) {}

bool Button::inBounds(const SDL_FPoint& point) const
{
    return point.x >= x && point.y >= y && point.x < x + width && point.y < y + height;
}

ImageButton::ImageButton(const float x, const float y, const float width, const float height, const char* path) :
    Button(x, y, width, height), path(path) {}

void ImageButton::init(SDL_Renderer* renderer)
{
    image = Resource::getImage(renderer, path, { 150, 150, 150, 255 });
}

void ImageButton::deinit()
{
    SDL_DestroyTexture(image);
}

void ImageButton::render(SDL_Renderer* renderer, const Camera* camera) const
{
    if (hover)
    {
        const SDL_FRect rect = { x - 4, y - 4, width + 8, height + 8 };

        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
        SDL_RenderFillRectF(renderer, &rect);
    }

    const SDL_FRect rect = { x, y, width, height };

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRectF(renderer, &rect);

    const SDL_FRect padded = { x + 10, y + 10, width - 20, height - 20 };

    SDL_SetTextureScaleMode(image, SDL_ScaleModeBest);
    SDL_RenderCopyF(renderer, image, NULL, &padded);
}
