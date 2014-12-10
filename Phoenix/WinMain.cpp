#include <Windows.h>
#include "core/Game.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstance, LPSTR commandLine, int showCommand) 
{
    //Initialize core stuff
    Game::Components = ComponentManager::create();
    Game::Window = Window::create(instanceHandle);

    //Initialize components
    //TODO

    //Release components
    //TODO

    //Release core stuff
    delete Game::Window;
    delete Game::Components;

    return 0;
}