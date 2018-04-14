#pragma once
#ifndef INCLUDE_PHOENIX_WIN32GAMELOOP_H
#define INCLUDE_PHOENIX_WIN32GAMELOOP_H

#include "../core/IGameLoop.h"
#include "../core/ComponentManager.h"
#include "../core/EventManager.h"
#include <Windows.h>

class Win32GameLoop : public IGameLoop, public IEventSubscriber
{
private:
    float deltaTime_;
	bool isForeground_;
	EventManager *events_; // <- borrowed

public:
	Win32GameLoop(const ComponentManager *components);
	~Win32GameLoop();

    inline float getDeltaTime() const { return deltaTime_; }
	inline bool isForeground() const { return isForeground_; }
    void run();

	void handleEvent(const EVID eventId, void *eventData);
};

#endif //INCLUDE_PHOENIX_WIN32GAMELOOP_H