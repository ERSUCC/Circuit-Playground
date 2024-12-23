#include "../include/renderer.h"

Renderer::Renderer(const unsigned int width, const unsigned int height) :
    width(width), height(height), camera(new Camera(width, height)) {}

int Renderer::init()
{
    return SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
}

void Renderer::deinit()
{
    for (GUIObject* object : guiObjects)
    {
        object->deinit();
    }

    for (CircuitObject* object : circuitObjects)
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

    for (const CircuitObject* object : circuitObjects)
    {
        object->render(renderer, camera);
    }

    for (const GUIObject* object : guiObjects)
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

    guiObjects.push_back(object);
}

void Renderer::addCircuitObject(CircuitObject* object)
{
    object->init(renderer);

    circuitObjects.push_back(object);
}

void Renderer::removeGuiObject(GUIObject* object)
{
    for (unsigned int i = 0; i < guiObjects.size(); i++)
    {
        if (guiObjects[i] == object)
        {
            guiObjects.erase(guiObjects.begin() + i);

            object->deinit();
        }
    }
}

void Renderer::removeCircuitObject(CircuitObject* object)
{
    for (unsigned int i = 0; i < circuitObjects.size(); i++)
    {
        if (circuitObjects[i] == object)
        {
            circuitObjects.erase(circuitObjects.begin() + i);

            object->deinit();
        }
    }
}

Object* Renderer::objectAtPoint(const SDL_FPoint& point) const
{
    for (GUIObject* object : guiObjects)
    {
        if (object->inBounds(point))
        {
            return object;
        }
    }

    for (CircuitObject* object : circuitObjects)
    {
        if (object->inBounds(point))
        {
            return object;
        }
    }

    return nullptr;
}
