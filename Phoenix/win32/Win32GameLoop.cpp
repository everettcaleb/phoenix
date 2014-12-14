#include "Win32GameLoop.h"
#include "../core/Game.h"

//========================================================================================================

void Win32GameLoop::run()
{
    MSG message;
    LARGE_INTEGER timerFrequency;
    LARGE_INTEGER timerTick;
    LARGE_INTEGER lastTick;

    QueryPerformanceFrequency(&timerFrequency);
    QueryPerformanceCounter(&timerTick);

    memset(&message, 0, sizeof(MSG));

    while (message.message != WM_QUIT)
    {
        if (Game::IsForegroundApp)
        {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            else
            {
                lastTick = timerTick;
                QueryPerformanceFrequency(&timerFrequency);
                QueryPerformanceCounter(&timerTick);

                deltaTime_ = (float)((double)(timerTick.QuadPart - lastTick.QuadPart) / (double)timerFrequency.QuadPart);
                deltaTime_ = min(deltaTime_, 0.5f);

                Game::Events->publishEvent(EVID_TICK, 0);
                Game::Events->publishQueuedEvents();
            }
        }
        else 
        {
            GetMessage(&message, NULL, 0, 0);
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}