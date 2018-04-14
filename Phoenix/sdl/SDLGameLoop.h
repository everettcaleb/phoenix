#pragma once
#ifndef INCLUDE_PHOENIX_SDLGAMELOOP_H
#define INCLUDE_PHOENIX_SDLGAMELOOP_H

#include "../core/IGameLoop.h"
#include "../core/EventManager.h"
#include "../core/ComponentManager.h"
#include <SDL2/SDL.h>

class SDLGameLoop : public IGameLoop
{
private:
    float deltaTime_;
    bool isForeground_;
    EventManager *events_; // <- borrowed
    
    void handleSDLEvent(SDL_Event *event);
    
public:
    SDLGameLoop(const ComponentManager *components);
    ~SDLGameLoop() {}
    
    float getDeltaTime() const { return deltaTime_; }
    bool isForeground() const { return isForeground_; }
    void run();
};

#endif //INCLUDE_PHOENIX_SDLGAMELOOP_H
