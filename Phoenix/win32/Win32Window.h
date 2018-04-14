#pragma once
#ifndef INCLUDE_PHOENIX_WIN32WINDOW_H
#define INCLUDE_PHOENIX_WIN32WINDOW_H

#include <Windows.h>
#include "../core/ComponentManager.h"
#include "../core/EventManager.h"

class Win32Window {
private:
    HINSTANCE instanceHandle_;
    HWND windowHandle_;
	EventManager *events_; // <- borrowed

    Win32Window(const Win32Window& other) {}

public:
	Win32Window(const ComponentManager *components, HINSTANCE instanceHandle);
    ~Win32Window();

	inline EventManager *getEventManager() { return events_;  }
    inline HWND getHandle() { return windowHandle_;  }
};

#endif //INCLUDE_PHOENIX_WIN32WINDOW_H