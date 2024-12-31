#include <chrono>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "../include/gui.h"
#include "../include/object.h"
#include "../include/renderer.h"
#include "../include/utils.h"

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << "\n";

        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << "\n";

        return 1;
    }

    SDL_DisplayMode mode;

    if (SDL_GetCurrentDisplayMode(0, &mode))
    {
        return 1;
    }

    const unsigned int width = mode.w;
    const unsigned int height = mode.h;

    Renderer* renderer = new Renderer(width, height);

    if (renderer->init())
    {
        std::cout << "Failed to initialize renderer.\n";

        return 1;
    }

    CircuitObject* newObject = nullptr;

    ImageButton* cursorButton = new ImageButton(width / 2 - 112, height - 96, 64, 64, "../resources/images/cursor.png");
    ImageButton* transistorButton = new ImageButton(width / 2 - 32, height - 96, 64, 64, "../resources/images/transistor.png");
    ImageButton* lightButton = new ImageButton(width / 2 + 48, height - 96, 64, 64, "../resources/images/light.png");

    renderer->addGuiObject(cursorButton);
    renderer->addGuiObject(transistorButton);
    renderer->addGuiObject(lightButton);

    renderer->addCircuitObject(new Source({ 0, 0 }));

    Object* lastHover = nullptr;

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
                        renderer->getCamera()->move(-event.motion.xrel, -event.motion.yrel);
                    }

                    else
                    {
                        SDL_FPoint point = { (float)event.motion.x, (float) event.motion.y };

                        Object* object = renderer->objectAtPoint(point);

                        if (object != lastHover)
                        {
                            if (lastHover)
                            {
                                lastHover->setHover(false);
                            }

                            if (object)
                            {
                                object->setHover(true);
                            }

                            lastHover = object;
                        }

                        if (newObject)
                        {
                            renderer->getCamera()->inverseTransformPoint(point);

                            Utils::snapToGrid(point);

                            newObject->setPosition(point);
                        }
                    }

                    break;

                case SDL_MOUSEWHEEL:
                    renderer->getCamera()->zoom(event.wheel.preciseY);

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (lastHover)
                        {
                            if (lastHover == cursorButton && newObject)
                            {
                                renderer->removeCircuitObject(newObject);

                                newObject = nullptr;
                            }

                            else if (lastHover == transistorButton)
                            {
                                if (newObject)
                                {
                                    renderer->removeCircuitObject(newObject);
                                }

                                SDL_FPoint point = { (float)event.button.x, (float)event.button.y };

                                renderer->getCamera()->inverseTransformPoint(point);

                                Utils::snapToGrid(point);

                                newObject = new Transistor(point);

                                renderer->addCircuitObject(newObject);
                            }

                            else if (lastHover == lightButton)
                            {
                                if (newObject)
                                {
                                    renderer->removeCircuitObject(newObject);
                                }

                                SDL_FPoint point = { (float)event.button.x, (float)event.button.y };

                                renderer->getCamera()->inverseTransformPoint(point);

                                Utils::snapToGrid(point);

                                newObject = new Light(point);

                                renderer->addCircuitObject(newObject);
                            }
                        }

                        else if (newObject)
                        {
                            newObject = newObject->clone();

                            renderer->addCircuitObject(newObject);
                        }
                    }

                    break;

                case SDL_KEYDOWN:
                    if (!event.key.repeat)
                    {
                        if (event.key.keysym.sym == SDLK_r && newObject)
                        {
                            newObject->rotate();
                        }

                        else if (event.key.keysym.sym == SDLK_f)
                        {
                            renderer->getCamera()->reset();
                        }
                    }

                    break;
            }
        }

        const long long delta = (clock.now() - lastDraw).count();

        if (delta >= 1e9)
        {
            // tick simulation
        }

        if (delta >= 1e9 / 60)
        {
            lastDraw = clock.now();

            renderer->render();
        }
    }

    renderer->deinit();

    IMG_Quit();
    SDL_Quit();

    return 0;
}
