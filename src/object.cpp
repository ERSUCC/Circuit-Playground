#include "../include/object.h"

Object::Object(const SDL_FPoint& position) :
    position(position) {}

void Object::init(SDL_Renderer* renderer) {}
void Object::deinit() {}

SDL_FPoint Object::getPosition() const
{
    return position;
}

void Object::setPosition(const SDL_FPoint& point)
{
    position = point;
}

void Object::setHover(const bool hover)
{
    this->hover = hover;
}

CircuitObject::CircuitObject(const SDL_FPoint& position) :
    Object(position), rotation(0) {}

CircuitObject::CircuitObject(const SDL_FPoint& position, const unsigned int rotation) :
    Object(position), rotation(rotation) {}

bool CircuitObject::inBounds(const SDL_FPoint& point) const
{
    return point.x >= position.x && point.y >= position.y && point.x < position.x + Utils::gridSize && point.y < position.y + Utils::gridSize;
}

void CircuitObject::rotate()
{
    rotation = (rotation + 1) % 4;
}

void CircuitObject::setNeighbor(const unsigned int index, CircuitObject* object)
{
    neighbors[index] = object;
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

bool Source::hasConnection(const unsigned int index) const
{
    return true;
}

Wire::Wire(const SDL_FPoint& position) :
    CircuitObject(position) {}

void Wire::render(SDL_Renderer* renderer, const Camera* camera) const
{
    SDL_FRect center = { position.x + Utils::gridSize / 2 - 4, position.y + Utils::gridSize / 2 - 4, 8, 8 };

    camera->transformRect(center);

    SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
    SDL_RenderFillRectF(renderer, &center);

    if (neighbors[0] && neighbors[0]->hasConnection(2))
    {
        SDL_FRect top = { position.x + Utils::gridSize / 2 - 4, position.y, 8, Utils::gridSize / 2 };

        camera->transformRect(top);

        SDL_RenderFillRectF(renderer, &top);
    }

    if (neighbors[1] && neighbors[1]->hasConnection(3))
    {
        SDL_FRect right = { position.x + Utils::gridSize / 2, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

        camera->transformRect(right);

        SDL_RenderFillRectF(renderer, &right);
    }

    if (neighbors[2] && neighbors[2]->hasConnection(0))
    {
        SDL_FRect bottom = { position.x + Utils::gridSize / 2 - 4, position.y + Utils::gridSize / 2, 8, Utils::gridSize / 2 };

        camera->transformRect(bottom);

        SDL_RenderFillRectF(renderer, &bottom);
    }

    if (neighbors[3] && neighbors[3]->hasConnection(1))
    {
        SDL_FRect left = { position.x, position.y + Utils::gridSize / 2 - 4, Utils::gridSize / 2, 8 };

        camera->transformRect(left);

        SDL_RenderFillRectF(renderer, &left);
    }
}

CircuitObject* Wire::clone() const
{
    return new Wire(position);
}

bool Wire::hasConnection(const unsigned int index) const
{
    return true;
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

bool Transistor::hasConnection(const unsigned int index) const
{
    return index != (rotation + 2) % 4;
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

bool Light::hasConnection(const unsigned int index) const
{
    return index == (rotation + 2) % 4;
}
