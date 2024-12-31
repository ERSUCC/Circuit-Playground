#pragma once

#include <SDL.h>

#include "camera.h"
#include "object.h"
#include "resource.h"

class GUIObject : public Object {};

class Button : public GUIObject
{

public:
    Button(const float x, const float y, const float width, const float height);

    bool inBounds(const SDL_FPoint& point) const override;

protected:
    float x;
    float y;
    float width;
    float height;

};

class ImageButton : public Button
{

public:
    ImageButton(const float x, const float y, const float width, const float height, const char* path);

    void init(SDL_Renderer* renderer) override;
    void deinit() override;

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

private:
    const char* path;

    SDL_Texture* image = nullptr;

};
