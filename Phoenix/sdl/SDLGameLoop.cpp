#include "SDLGameLoop.h"
#include "../core/Game.h"

#include <SDL2/SDL.h>
#include <math.h>

static void HandleSDLEvent(SDL_Event *ev);

//========================================================================================================

void SDLGameLoop::run()
{
    SDL_Event ev;
    unsigned int tick = 0, lastTick = 0;
    
    memset(&ev, 0, sizeof(SDL_Event));
    
    while (ev.type != SDL_QUIT)
    {
        if (Game::IsForegroundApp)
        {
            if (SDL_PollEvent(&ev))
            {
                HandleSDLEvent(&ev);
            }
            else
            {
                lastTick = tick;
                tick = SDL_GetTicks();
                
                deltaTime_ = (float)((double)(tick - lastTick) / 1000.0);
                deltaTime_ = deltaTime_ > 0.5f ? deltaTime_ : 0.5f;
                
                Game::Events->publishEvent(EVID_TICK, 0);
                Game::Events->publishQueuedEvents();
            }
        }
        else
        {
            SDL_WaitEvent(&ev);
            HandleSDLEvent(&ev);
        }
    }
}

//========================================================================================================

void HandleSDLEvent(SDL_Event *ev)
{
    switch(ev->type)
    {
        case SDL_WINDOWEVENT:
            switch(ev->window.event)
            {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                case SDL_WINDOWEVENT_ENTER:
                    Game::IsForegroundApp = true;
                    break;
                    
                case SDL_WINDOWEVENT_FOCUS_LOST:
                case SDL_WINDOWEVENT_LEAVE:
                    Game::IsForegroundApp = false;
                    break;
            }
            break;
    }
}
