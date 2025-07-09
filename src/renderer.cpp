#include "../include/renderer.h"

Renderer::Renderer(const unsigned int width, const unsigned int height) :
    width(width), height(height), camera(new Camera(width, height))
{
    guiObjects = new Tree();
    circuitObjects = new Tree();
}

int Renderer::init()
{
    return SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
}

void Renderer::deinit()
{
    TreeIterator* iterator = guiObjects->iterator();

    while (Object* object = iterator->next())
    {
        object->deinit();
    }

    iterator = circuitObjects->iterator();

    while (Object* object = iterator->next())
    {
        object->deinit();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    TreeIterator* iterator = circuitObjects->iterator();

    while (Object* object = iterator->next())
    {
        object->render(renderer, camera);
    }

    for (Object* object : temporaryObjects)
    {
        object->render(renderer, camera);
    }

    iterator = guiObjects->iterator();

    while (Object* object = iterator->next())
    {
        object->render(renderer, camera);
    }

    SDL_RenderPresent(renderer);
}

Camera* Renderer::getCamera() const
{
    return camera;
}

void Renderer::addGuiObject(GUIObject* object)
{
    object->init(renderer);

    guiObjects->add(object);
}

void Renderer::addCircuitObject(CircuitObject* object)
{
    object->init(renderer);

    if (dynamic_cast<Wire*>(object))
    {
        const SDL_FPoint point = object->getPosition();

        if (CircuitObject* other = findCircuitObject({ point.x, point.y - Utils::gridSize }))
        {
            object->setNeighbor(0, other);
            other->setNeighbor(2, object);
        }

        if (CircuitObject* other = findCircuitObject({ point.x + Utils::gridSize, point.y }))
        {
            object->setNeighbor(1, other);
            other->setNeighbor(3, object);
        }

        if (CircuitObject* other = findCircuitObject({ point.x, point.y + Utils::gridSize }))
        {
            object->setNeighbor(2, other);
            other->setNeighbor(0, object);
        }

        if (CircuitObject* other = findCircuitObject({ point.x - Utils::gridSize, point.y }))
        {
            object->setNeighbor(3, other);
            other->setNeighbor(1, object);
        }
    }

    circuitObjects->add(object);
}

void Renderer::addTemporaryObject(Object* object)
{
    object->init(renderer);

    temporaryObjects.push_back(object);
}

void Renderer::removeGuiObject(GUIObject* object)
{
    guiObjects->remove(object);

    object->deinit();
}

void Renderer::removeCircuitObject(CircuitObject* object)
{
    circuitObjects->remove(object);

    object->deinit();
}

void Renderer::removeTemporaryObject(Object* object)
{
    for (unsigned int i = 0; i < temporaryObjects.size(); i++)
    {
        if (temporaryObjects[i] == object)
        {
            temporaryObjects.erase(temporaryObjects.begin() + i);

            return;
        }
    }
}

CircuitObject* Renderer::findCircuitObject(const SDL_FPoint& point) const
{
    return dynamic_cast<CircuitObject*>(circuitObjects->find(point));
}

Object* Renderer::objectAtPoint(const SDL_FPoint& point) const
{
    // optimize this to search by point

    TreeIterator* iterator = guiObjects->iterator();

    while (Object* object = iterator->next())
    {
        if (object->inBounds(point))
        {
            return object;
        }
    }

    iterator = circuitObjects->iterator();

    while (Object* object = iterator->next())
    {
        if (object->inBounds(point))
        {
            return object;
        }
    }

    return nullptr;
}
