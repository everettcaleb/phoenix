#pragma once
#ifndef INCLUDE_PHOENIX_TESTRENDERER2D_H
#define INCLUDE_PHOENIX_TESTRENDERER2D_H

#include "../core/IEventSubscriber.h"
#include "../core/ComponentManager.h"
#include "../core/EventManager.h"
#include "../graphics/IRenderer2D.h"
#include "../core/IGameLoop.h"

class TestRenderer2D : public IEventSubscriber
{
private:
    IRenderer2D *renderer_; // <- borrowed
    IGameLoop *loop_; // <- borrowed
    EventManager *events_; // <- borrowed
    
    void OnTick(float deltaTime);
    
public:
    TestRenderer2D(const ComponentManager *components);
    ~TestRenderer2D();
    
    void HandleEvent(EVID eventId, void *data);
};

#endif //INCLUDE_PHOENIX_TESTGAMELOGIC_H
