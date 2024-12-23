#include "../include/camera.h"

Camera::Camera(const unsigned int screenWidth, const unsigned int screenHeight) :
    screenWidth(screenWidth), screenHeight(screenHeight) {}

void Camera::move(const float dx, const float dy)
{
    x += dx / scale;
    y += dy / scale;
}

void Camera::zoom(const float amount)
{
    scale += amount * scale / 3;

    if (scale < 0.01)
    {
        scale = 0.01;
    }

    else if (scale > 10)
    {
        scale = 10;
    }
}

void Camera::reset()
{
    x = 0;
    y = 0;
    scale = 1;
}

void Camera::transformPoint(SDL_FPoint& point) const
{
    point.x = (point.x - x) * scale + screenWidth / 2;
    point.y = (point.y - y) * scale + screenHeight / 2;
}

void Camera::transformRect(SDL_FRect& rect) const
{
    rect.x = (rect.x - x) * scale + screenWidth / 2;
    rect.y = (rect.y - y) * scale + screenHeight / 2;
    rect.w *= scale;
    rect.h *= scale;

    if (rect.w < 1)
    {
        rect.w = 1;
    }

    if (rect.h < 1)
    {
        rect.h = 1;
    }
}

void Camera::inverseTransformPoint(SDL_FPoint& point) const
{
    point.x = (point.x - screenWidth / 2) / scale + x;
    point.y = (point.y - screenHeight / 2) / scale + y;
}
