#include <Windows.h>

#include "core/ComponentManager.h"
#include "core/EventManager.h"
#include "win32/Win32Window.h"
#include "win32/Win32GameLoop.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstance, LPSTR commandLine, int showCommand) 
{
    //Initialize core stuff
	ComponentManager *components = new ComponentManager();
	EventManager *events = new EventManager();
	components->registerComponentOnHeap(CUID_EVENTMANAGER, events);

    //Initialize components
    IGameLoop *gameLoop = new Win32GameLoop(components);
    components->registerComponentOnHeap(CUID_WIN32WINDOW, new Win32Window(components, instanceHandle));
    components->registerComponentOnHeap(CUID_IGAMELOOP, gameLoop);

    //Run the game loop
    gameLoop->run();

    //Release core stuff
    delete components;

    return 0;
}