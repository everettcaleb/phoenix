#include "Win32GameLoop.h"

Win32GameLoop::Win32GameLoop(const ComponentManager *components)
{
	deltaTime_ = 0.0f;
	isForeground_ = true;
	events_ = (EventManager*)components->queryComponent(CUID_EVENTMANAGER);
	events_->registerSubscriber(this);
}

//========================================================================================================

Win32GameLoop::~Win32GameLoop()
{
	events_->unregisterSubscriber(this);
}

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
        if (isForeground_)
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

                events_->publishEvent(EVID_TICK, 0);
                events_->publishQueuedEvents();
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

//========================================================================================================

void Win32GameLoop::handleEvent(const EVID eventId, void *eventData)
{
	switch (eventId)
	{
	case EVID_SWITCH_TO_FOREGROUND:
		isForeground_ = true;
	case EVID_SWITCH_TO_BACKGROUND:
		isForeground_ = false;
	default:
		return;
	}
}