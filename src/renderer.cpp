#include "../include/renderer.h"

Renderer::Renderer(const Camera* camera, const unsigned int width, const unsigned int height) :
    camera(camera), width(width), height(height) {}

int Renderer::init()
{
    return SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
}

void Renderer::deinit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::render()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    for (const Object* object : circuitObjects)
    {
        object->render(renderer, camera);
    }

    for (const GUIObject* object : guiObjects)
    {
        object->render(renderer, camera);
    }

    SDL_RenderPresent(renderer);
}

void Renderer::addGuiObject(GUIObject* object)
{
    guiObjects.push_back(object);
}

void Renderer::addCircuitObject(Object* object)
{
    circuitObjects.push_back(object);
}

void Renderer::removeGuiObject(const GUIObject* object)
{
    for (unsigned int i = 0; i < guiObjects.size(); i++)
    {
        if (guiObjects[i] == object)
        {
            guiObjects.erase(guiObjects.begin() + i);
        }
    }
}

void Renderer::removeCircuitObject(const Object* object)
{
    for (unsigned int i = 0; i < circuitObjects.size(); i++)
    {
        if (circuitObjects[i] == object)
        {
            circuitObjects.erase(circuitObjects.begin() + i);
        }
    }
}

bool Renderer::interceptClick(const SDL_FPoint& point) const
{
    for (const GUIObject* object : guiObjects)
    {
        if (object->interceptClick(point))
        {
            return true;
        }
    }

    return false;
}
