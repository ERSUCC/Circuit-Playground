#pragma once

#include <SDL.h>

#include "camera.h"
#include "utils.h"

class Object
{

public:
    virtual void init(SDL_Renderer* renderer);
    virtual void deinit();

    virtual void render(SDL_Renderer* renderer, const Camera* camera) const = 0;

    virtual bool inBounds(const SDL_FPoint& point) const = 0;

    void setHover(const bool hover);

protected:
    bool hover = false;

};

class CircuitObject : public Object
{

public:
    CircuitObject(const SDL_FPoint& position);
    CircuitObject(const SDL_FPoint& position, const unsigned int rotation);

    bool inBounds(const SDL_FPoint& point) const override;

    void setPosition(const SDL_FPoint& point);
    void rotate();

    virtual CircuitObject* clone() const = 0;

protected:
    SDL_FPoint position;

    unsigned int rotation;

};

class Source : public CircuitObject
{

public:
    Source(const SDL_FPoint& position);
    Source(const SDL_FPoint& position, const unsigned int rotation);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

    CircuitObject* clone() const override;

};

class Transistor : public CircuitObject
{

public:
    Transistor(const SDL_FPoint& position);
    Transistor(const SDL_FPoint& position, const unsigned int rotation);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

    CircuitObject* clone() const override;

};

class Light : public CircuitObject
{

public:
    Light(const SDL_FPoint& position);
    Light(const SDL_FPoint& position, const unsigned int rotation);

    void render(SDL_Renderer* renderer, const Camera* camera) const override;

    CircuitObject* clone() const override;

};
