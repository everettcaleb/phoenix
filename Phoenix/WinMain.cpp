#include <Windows.h>

#include "core/Game.h"
#include "win32/Win32Window.h"
#include "win32/Win32GameLoop.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstance, LPSTR commandLine, int showCommand) 
{
    //Initialize core stuff
    Game::Components = ComponentManager::create();
    Game::Events = EventManager::create();

    //Initialize components
    IGameLoop *gameLoop = new Win32GameLoop();
    Game::Components->registerComponentOnHeap(CUID_WIN32WINDOW, Win32Window::create(instanceHandle));
    Game::Components->registerComponentOnHeap(CUID_IGAMELOOP, gameLoop);

    //Run the game loop
    gameLoop->run();

    //Release core stuff
    delete Game::Events;
    delete Game::Components;

    return 0;
}