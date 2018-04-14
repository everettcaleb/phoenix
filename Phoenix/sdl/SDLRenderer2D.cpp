#include "SDLRenderer2D.h"
#include "SDL2_gfx/SDL2_gfxPrimitives.h"

SDLRenderer2D::SDLRenderer2D(const ComponentManager *components)
{
    window_ = (SDL_Window*)components->queryComponent(CUID_SDLWINDOW);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!window_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::InitFailed, "SDLRenderer2D::init failed, no window available");
    }
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::InitFailed, "SDLRenderer2D::init failed, renderer_ is null");
    }
}

SDLRenderer2D::~SDLRenderer2D()
{
    if(renderer_)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = NULL;
    }
}

void SDLRenderer2D::clear(const Color color)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, color.alpha);
    SDL_RenderClear(renderer_);
}

void SDLRenderer2D::drawLine(const Color color, const Point &point1, const Point &point2)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    aalineRGBA(renderer_, point1.x, point1.y, point2.x, point2.y, color.red, color.green, color.blue, color.alpha);
}

void SDLRenderer2D::drawPoint(const Color color, const Point &point)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawPoint(renderer_, point.x, point.y);
}

void SDLRenderer2D::drawRect(const Color color, const Rect &rect)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    SDL_Rect r;
    r.x = rect.x;
    r.y = rect.y;
    r.w = rect.width;
    r.h = rect.height;
    
    SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawRect(renderer_, &r);
}

void SDLRenderer2D::drawCircle(const Color color, const Point &center, int radius)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    aacircleRGBA(renderer_, center.x, center.y, radius, color.red, color.green, color.blue, color.alpha);
}

void SDLRenderer2D::drawTriangle(const Color color, const Point &point1, const Point &point2, const Point &point3)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    aatrigonRGBA(renderer_, point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color.red, color.green, color.blue, color.alpha);
}

void SDLRenderer2D::fillRect(const Color color, const Rect &rect)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    SDL_Rect r;
    r.x = rect.x;
    r.y = rect.y;
    r.w = rect.width;
    r.h = rect.height;
    
    SDL_SetRenderDrawColor(renderer_, color.red, color.green, color.blue, color.alpha);
    SDL_RenderFillRect(renderer_, &r);
}

void SDLRenderer2D::fillCircle(const Color color, const Point &center, int radius)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    filledCircleRGBA(renderer_, center.x, center.y, radius, color.red, color.green, color.blue, color.alpha);
}

void SDLRenderer2D::fillTriangle(const Color color, const Point &point1, const Point &point2, const Point &point3)
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    filledTrigonRGBA(renderer_, point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color.red, color.green, color.blue, color.alpha);
}

void SDLRenderer2D::present()
{
    if(!renderer_)
    {
        throw SDLRenderer2DException(SDLRenderer2DExceptionCode::NotInitialized, "SDLRenderer2D has not been initialized");
    }
    
    SDL_RenderPresent(renderer_);
}

SDLRenderer2DException::SDLRenderer2DException(const SDLRenderer2DExceptionCode code, const char *message)
{
    code_ = code;
    message_ = std::string(message);
}
