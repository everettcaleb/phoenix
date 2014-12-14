#include <Windows.h>

#include "core/Game.h"
#include "win32/Win32Window.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstance, LPSTR commandLine, int showCommand) 
{
    //Initialize core stuff
    Game::Components = ComponentManager::create();

    //Initialize components
    Game::Components->registerComponent(CUID_WIN32WINDOW, Win32Window::create(instanceHandle), DefaultHeapComponentFinalizer);

    //Release core stuff
    delete Game::Components;

    return 0;
}