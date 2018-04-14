#include "SDLGameLoop.h"
#include <math.h>

SDLGameLoop::SDLGameLoop(const ComponentManager *components)
{
    deltaTime_ = 0.0f;
    isForeground_ = true;
    events_ = (EventManager *)components->queryComponent(CUID_EVENTMANAGER);
}

//========================================================================================================

void SDLGameLoop::run()
{
    SDL_Event ev;
    unsigned int tick = 0, lastTick = 0;
    
    memset(&ev, 0, sizeof(SDL_Event));
    
    while (ev.type != SDL_QUIT)
    {
        if (isForeground_)
        {
            if (SDL_PollEvent(&ev))
            {
                handleSDLEvent(&ev);
            }
            else
            {
                lastTick = tick;
                tick = SDL_GetTicks();
                
                deltaTime_ = (float)((double)(tick - lastTick) / 1000.0);
                deltaTime_ = deltaTime_ > 0.5f ? deltaTime_ : 0.5f;
                
                events_->publishEvent(EVID_TICK, 0);
                events_->publishQueuedEvents();
            }
        }
        else
        {
            SDL_WaitEvent(&ev);
            handleSDLEvent(&ev);
        }
    }
}

//========================================================================================================

void SDLGameLoop::handleSDLEvent(SDL_Event *ev)
{
    switch(ev->type)
    {
        case SDL_WINDOWEVENT:
            switch(ev->window.event)
            {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                case SDL_WINDOWEVENT_ENTER:
                    isForeground_ = true;
                    break;
                    
                case SDL_WINDOWEVENT_FOCUS_LOST:
                case SDL_WINDOWEVENT_LEAVE:
                    isForeground_ = false;
                    break;
            }
            break;
    }
    events_->publishEvent(EVID_SDL_EVENT, ev);
}
