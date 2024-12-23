#pragma once

#include <SDL.h>

class Camera
{

public:
    Camera(const unsigned int screenWidth, const unsigned int screenHeight);

    void move(const float dx, const float dy);
    void zoom(const float amount);
    void reset();

    void transformPoint(SDL_FPoint& point) const;
    void transformRect(SDL_FRect& rect) const;

    void inverseTransformPoint(SDL_FPoint& point) const;

private:
    const unsigned int screenWidth;
    const unsigned int screenHeight;

    float x = 0;
    float y = 0;
    float scale = 1;

};
