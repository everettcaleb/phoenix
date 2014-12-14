#pragma once
#ifndef INCLUDE_PHOENIX_WIN32GAMELOOP_H
#define INCLUDE_PHOENIX_WIN32GAMELOOP_H

#include "..\core\IGameLoop.h"
#include <Windows.h>

class Win32GameLoop : public IGameLoop
{
private:
    float deltaTime_;

public:
    Win32GameLoop() : deltaTime_(0.0f) {}
    ~Win32GameLoop() {}

    float getDeltaTime() const { return deltaTime_; }
    void run();
};

#endif //INCLUDE_PHOENIX_WIN32GAMELOOP_H