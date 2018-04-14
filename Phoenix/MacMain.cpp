#include <SDL2/SDL.h>

#include "core/ComponentManager.h"
#include "core/EventManager.h"
#include "sdl/SDLGameLoop.h"
#include "sdl/SDLRenderer2D.h"
#include "tests/Breakout.h"

//========================================================================================================

static inline void SDLWindowFinalizer(void *windowPointer)
{
    SDL_DestroyWindow((SDL_Window*)windowPointer);
}

//========================================================================================================

int main(int argc, char *argv[])
{
    //Initialize core stuff
    ComponentManager *components = new ComponentManager();
    EventManager *events = new EventManager();
    components->registerComponentOnHeap(CUID_EVENTMANAGER, events);
    
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return -1;
    }
    
    //Initialize components
    IGameLoop *gameLoop = new SDLGameLoop(components);
    SDL_Window *window = SDL_CreateWindow("PHOENIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    components->registerComponent(CUID_SDLWINDOW, window, SDLWindowFinalizer);
    components->registerComponentOnHeap(CUID_IGAMELOOP, gameLoop);
    IRenderer2D *renderer = new SDLRenderer2D(components);
    components->registerComponentOnHeap(CUID_IRENDERER2D, renderer);
    
    // Initialize the logic
    Breakout *logic = new Breakout(components);
    
    //Run the game loop
    gameLoop->run();
    
    // Kill the logic
    delete logic;
    
    //Release core stuff
    delete components;
    
    //Quit SDL
    SDL_Quit();
    
    return 0;
}
