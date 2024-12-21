#include <chrono>
#include <iostream>

#include <SDL.h>

#include "../include/object.h"
#include "../include/renderer.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << "\n";

        return 1;
    }

    SDL_DisplayMode mode;

    if (SDL_GetCurrentDisplayMode(0, &mode))
    {
        return 1;
    }

    const unsigned int width = mode.w;
    const unsigned int height = mode.h;

    Camera* camera = new Camera(width, height);
    Renderer* renderer = new Renderer(camera, width, height);

    if (renderer->init())
    {
        std::cout << "Failed to initialize renderer.\n";

        return 1;
    }

    bool adding = false;

    renderer->addGuiObject(new Button(10, 10, 50, 50, [&]()
    {
        adding = true;
    }));

    renderer->addGuiObject(new Button(10, 70, 50, 50, [&]()
    {
        adding = false;
    }));

    renderer->addCircuitObject(new Source(0, 0));
    renderer->addCircuitObject(new Transistor(50, 0));
    renderer->addCircuitObject(new Transistor(50, -50));

    bool running = true;

    SDL_Event event;

    std::chrono::high_resolution_clock clock;

    std::chrono::time_point lastDraw = clock.now();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;

                    break;

                case SDL_MOUSEMOTION:
                    if (event.motion.state == SDL_BUTTON_MIDDLE)
                    {
                        camera->move(-event.motion.xrel, -event.motion.yrel);
                    }

                    break;

                case SDL_MOUSEWHEEL:
                    camera->zoom(event.wheel.preciseY);

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_FPoint point = { (float)event.button.x, (float)event.button.y };

                        if (!renderer->interceptClick(point) && adding)
                        {
                            camera->inverseTransformPoint(point);

                            float x = (int)(point.x / 50) * 50;
                            float y = (int)(point.y / 50) * 50;

                            if (point.x < 0)
                            {
                                x -= 50;
                            }

                            if (point.y < 0)
                            {
                                y -= 50;
                            }

                            renderer->addCircuitObject(new Transistor(x, y));
                        }
                    }

                    break;
            }
        }

        if ((clock.now() - lastDraw).count() >= 1e9 / 60)
        {
            lastDraw = clock.now();

            renderer->render();
        }
    }

    renderer->deinit();

    SDL_Quit();

    return 0;
}
