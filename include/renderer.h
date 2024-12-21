#pragma once

#include <string>
#include <vector>

#include <SDL.h>

#include "camera.h"
#include "object.h"

class Renderer
{

public:
    Renderer(const Camera* camera, const unsigned int width, const unsigned int height);

    int init();
    void deinit();

    void render();

    void addGuiObject(GUIObject* object);
    void addCircuitObject(Object* object);
    void removeGuiObject(const GUIObject* object);
    void removeCircuitObject(const Object* object);

    bool interceptClick(const SDL_FPoint& point) const;

private:
    const Camera* camera;

    const unsigned int width;
    const unsigned int height;

    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<GUIObject*> guiObjects;
    std::vector<Object*> circuitObjects;

};
