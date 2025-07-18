#pragma once

#include <string>
#include <vector>

#include <SDL.h>

#include "camera.h"
#include "gui.h"
#include "object.h"
#include "tree.h"

class Renderer
{

public:
    Renderer(const unsigned int width, const unsigned int height);

    int init();
    void deinit();

    void render();

    Camera* getCamera() const;

    void addGuiObject(GUIObject* object);
    void addCircuitObject(CircuitObject* object);
    void addTemporaryObject(Object* object);

    void removeGuiObject(GUIObject* object);
    void removeCircuitObject(CircuitObject* object);
    void removeTemporaryObject(Object* object);

    CircuitObject* findCircuitObject(const SDL_FPoint& point) const;

    Object* objectAtPoint(const SDL_FPoint& point) const;

private:
    const unsigned int width;
    const unsigned int height;

    Camera* camera;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Tree* guiObjects;
    Tree* circuitObjects;

    std::vector<Object*> temporaryObjects;

};
