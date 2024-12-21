#pragma once

#include <functional>

#include <SDL.h>

#include "camera.h"

class Object
{

public:
    virtual void render(SDL_Renderer* renderer, const Camera* camera) const = 0;

};

class Source : public Object
{

public:
    Source(const float x, const float y);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

private:
    float x;
    float y;

    const float size = 50;

};

class Transistor : public Object
{

public:
    Transistor(const float x, const float y);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

private:
    float x;
    float y;

    const float size = 50;

};

class GUIObject : public Object
{

public:
    virtual bool interceptClick(const SDL_FPoint& point) const = 0;

};

class Button : public GUIObject
{

public:
    Button(const float x, const float y, const float width, const float height, const std::function<void()> click);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

    bool interceptClick(const SDL_FPoint& point) const override;

private:
    float x;
    float y;
    float width;
    float height;

    const std::function<void()> click;

};
