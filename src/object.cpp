#include "../include/object.h"

Source::Source(const float x, const float y) :
    x(x), y(y) {}

void Source::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect rect = { x, y, size, size };

    camera->transformRect(rect);

    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_RenderFillRectF(renderer, &rect);
}

Transistor::Transistor(const float x, const float y) :
    x(x), y(y) {}

void Transistor::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect rect = { x, y, size, size };

    camera->transformRect(rect);

    SDL_SetRenderDrawColor(renderer, 128, 255, 128, 255);
    SDL_RenderFillRectF(renderer, &rect);
}

Button::Button(const float x, const float y, const float width, const float height, const std::function<void()> click) :
    x(x), y(y), width(width), height(height), click(click) {}

void Button::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect rect = { x, y, width, height };

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRectF(renderer, &rect);
}

#include <iostream>

bool Button::interceptClick(const SDL_FPoint& point) const
{
    if (point.x >= x && point.y >= point.y && point.x < x + width && point.y < y + height)
    {
        click();

        return true;
    }

    return false;
}
