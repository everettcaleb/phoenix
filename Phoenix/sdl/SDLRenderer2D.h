#pragma once
#ifndef INCLUDE_PHOENIX_SDLRENDERER2D_H
#define INCLUDE_PHOENIX_SDLRENDERER2D_H

#include <string>

#include "../graphics/IRenderer2D.h"
#include "../core/ComponentManager.h"
#include "SDL2/SDL.h"

class SDLRenderer2D : public IRenderer2D
{
private:
    SDL_Window *window_; // <- borrowed
    SDL_Renderer *renderer_; // <- owns
    
public:
    SDLRenderer2D(const ComponentManager *components);
    ~SDLRenderer2D();
    
    void clear(const Color color);
    void drawLine(const Color color, const Point &point1, const Point &point2);
    void drawPoint(const Color color, const Point &point);
    void drawRect(const Color color, const Rect &rect);
    void drawCircle(const Color color, const Point &center, const int radius);
    void drawTriangle(const Color color, const Point &point1, const Point &point2, const Point &point3);
    void fillRect(const Color color, const Rect &rect);
    void fillCircle(const Color color, const Point &center, const int radius);
    void fillTriangle(const Color color, const Point &point1, const Point &point2, const Point &point3);
    void present();
};

enum SDLRenderer2DExceptionCode
{
    NotInitialized = -1,
    InitFailed = -2
};

class SDLRenderer2DException
{
private:
    SDLRenderer2DExceptionCode code_;
    std::string message_;
    
public:
    SDLRenderer2DException(SDLRenderer2DExceptionCode code, const char *message);
    
    inline const SDLRenderer2DExceptionCode getCode() const { return code_; }
    inline const char * const getMessage() const { return message_.c_str(); }
};

#endif //INCLUDE_PHOENIX_SDLRENDERER2D_H
