#pragma once
#ifndef INCLUDE_PHOENIX_BREAKOUT_H
#define INCLUDE_PHOENIX_BREAKOUT_H

#include "../core/IEventSubscriber.h"
#include "../core/EventManager.h"
#include "../core/ComponentManager.h"
#include "../graphics/IRenderer2D.h"
#include "../core/IGameLoop.h"

class Breakout : public IEventSubscriber
{
private:
    IRenderer2D *renderer_; // <- borrowed
    IGameLoop *loop_; // <- borrowed
    EventManager *events_; // <- borrowed
    
    void OnTick(float deltaTime);
    
public:
    Breakout(const ComponentManager *components);
    ~Breakout();
    
    void HandleEvent(EVID eventId, void *data);
};

#endif //INCLUDE_PHOENIX_BREAKOUT_H
