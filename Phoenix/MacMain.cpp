#include <SDL2/SDL.h>

#include "core/Game.h"
#include "sdl/SDLGameLoop.h"

//========================================================================================================

static inline void SDLWindowFinalizer(void *windowPointer)
{
    SDL_DestroyWindow((SDL_Window*)windowPointer);
}

//========================================================================================================

int main(int argc, char *argv[])
{
    //Initialize core stuff
    Game::Components = ComponentManager::create();
    Game::Events = EventManager::create();
    
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return -1;
    }
    
    //Initialize components
    IGameLoop *gameLoop = new SDLGameLoop();
    SDL_Window *window = SDL_CreateWindow("PHOENIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    
    Game::Components->registerComponent(CUID_SDLWINDOW, window, SDLWindowFinalizer);
    Game::Components->registerComponentOnHeap(CUID_IGAMELOOP, gameLoop);
    
    //Run the game loop
    gameLoop->run();
    
    //Quit SDL
    SDL_Quit();
    
    //Release core stuff
    delete Game::Events;
    delete Game::Components;
    
    return 0;
}
