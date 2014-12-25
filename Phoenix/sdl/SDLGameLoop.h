#pragma once
#ifndef INCLUDE_PHOENIX_SDLGAMELOOP_H
#define INCLUDE_PHOENIX_SDLGAMELOOP_H

#include "../core/IGameLoop.h"

class SDLGameLoop : public IGameLoop
{
private:
    float deltaTime_;
    
public:
    SDLGameLoop() : deltaTime_(0.0f) {}
    ~SDLGameLoop() {}
    
    float getDeltaTime() const { return deltaTime_; }
    void run();
};

#endif //INCLUDE_PHOENIX_SDLGAMELOOP_H
