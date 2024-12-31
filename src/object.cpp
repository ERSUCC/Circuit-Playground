#include "../include/object.h"

void Object::init(SDL_Renderer* renderer) {}
void Object::deinit() {}

void Object::setHover(const bool hover)
{
    this->hover = hover;
}

CircuitObject::CircuitObject(const SDL_FPoint& position) :
    position(position), rotation(0) {}

CircuitObject::CircuitObject(const SDL_FPoint& position, const unsigned int rotation) :
    position(position), rotation(rotation) {}

bool CircuitObject::inBounds(const SDL_FPoint& point) const
{
    return point.x >= position.x && point.y >= position.y && point.x < position.x + Utils::gridSize && point.y < position.y + Utils::gridSize;
}

void CircuitObject::setPosition(const SDL_FPoint& point)
{
    position = point;
}

void CircuitObject::rotate()
{
    rotation = (rotation + 1) % 4;
}

Source::Source(const SDL_FPoint& position) :
    CircuitObject(position) {}

Source::Source(const SDL_FPoint& position, const unsigned int rotation) :
    CircuitObject(position, rotation) {}

void Source::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect one = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize, 8 };
    SDL_FRect two = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize };

    camera->transformRect(one);
    camera->transformRect(two);

    SDL_SetRenderDrawColor(renderer, 255, 128, 128, 255);
    SDL_RenderFillRectF(renderer, &one);
    SDL_RenderFillRectF(renderer, &two);
}

CircuitObject* Source::clone() const
{
    return new Source(position, rotation);
}

Transistor::Transistor(const SDL_FPoint& position) :
    CircuitObject(position) {}

Transistor::Transistor(const SDL_FPoint& position, const unsigned int rotation) :
    CircuitObject(position, rotation) {}

void Transistor::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect base;
    SDL_FRect cross;

    switch (rotation)
    {
        case 0:
            base = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize, 8 };
            cross = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize / 2 };

            break;

        case 1:
            base = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize };
            cross = { position.x + Utils::gridSize / 2, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

            break;

        case 2:
            base = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize, 8 };
            cross = { position.x + Utils::gridSize / 2 - 4, position.y + Utils::gridSize / 2, 8, Utils::gridSize / 2 };

            break;

        case 3:
            base = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize };
            cross = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

            break;
    }

    camera->transformRect(base);
    camera->transformRect(cross);

    SDL_SetRenderDrawColor(renderer, 128, 255, 128, 255);
    SDL_RenderFillRectF(renderer, &base);
    SDL_RenderFillRectF(renderer, &cross);
}

CircuitObject* Transistor::clone() const
{
    return new Transistor(position, rotation);
}

Light::Light(const SDL_FPoint& position) :
    CircuitObject(position) {}

Light::Light(const SDL_FPoint& position, const unsigned int rotation) :
    CircuitObject(position, rotation) {}

void Light::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect bulb = { position.x + Utils::gridSize / 2 - 12, position.y + Utils::gridSize / 2 - 12, 24, 24 };
    SDL_FRect stem;

    switch (rotation)
    {
        case 0:
            stem = { position.x + Utils::gridSize / 2 - 4, position.y + Utils::gridSize / 2, 8, Utils::gridSize / 2 };

            break;

        case 1:
            stem = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

            break;

        case 2:
            stem = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize / 2 };

            break;

        case 3:
            stem = { position.x + Utils::gridSize / 2, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

            break;
    }

    camera->transformRect(bulb);
    camera->transformRect(stem);

    SDL_SetRenderDrawColor(renderer, 255, 128, 255, 255);
    SDL_RenderFillRectF(renderer, &bulb);
    SDL_RenderFillRectF(renderer, &stem);
}

CircuitObject* Light::clone() const
{
    return new Light(position, rotation);
}
