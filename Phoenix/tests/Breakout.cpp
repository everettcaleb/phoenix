#include "Breakout.h"

Breakout::Breakout(const ComponentManager *components)
{
    renderer_ = (IRenderer2D*)components->queryComponent(CUID_IRENDERER2D);
    loop_ = (IGameLoop*)components->queryComponent(CUID_IGAMELOOP);
    events_ = (EventManager*)components->queryComponent(CUID_EVENTMANAGER);
    
    events_->registerSubscriber(this);
}

Breakout::~Breakout()
{
    events_->unregisterSubscriber(this);
}

void Breakout::HandleEvent(EVID eventId, void *data)
{
    switch(eventId)
    {
        case EVID_TICK:
            OnTick(loop_->getDeltaTime());
            break;
        default:
            return;
    }
}

void Breakout::OnTick(float deltaTime)
{
    renderer_->clear(COLOR_BLACK);
    
    renderer_->drawPoint(COLOR_YELLOW, Point{10,10});
    renderer_->drawLine(COLOR_CYAN, Point{5,5}, Point{100,5});
    renderer_->drawRect(COLOR_RED, Rect{98, 98, 54, 54});
    renderer_->fillRect(COLOR_BLUE, Rect{100,100,50,50});
    renderer_->fillRect(COLOR_GREEN, Rect{150,150,75,75});
    renderer_->drawCircle(COLOR_RED, Point{125,125}, 25);
    renderer_->drawTriangle(COLOR_GREEN, Point{500,500}, Point{600,600}, Point{600,300});
    renderer_->fillCircle(COLOR_YELLOW, Point{186,186}, 37);
    renderer_->fillTriangle(COLOR_RED, Point{200,200}, Point{200,300}, Point{300,200});
    
    renderer_->present();
}
