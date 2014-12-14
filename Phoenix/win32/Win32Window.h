#pragma once
#ifndef INCLUDE_PHOENIX_WIN32WINDOW_H
#define INCLUDE_PHOENIX_WIN32WINDOW_H

#include <Windows.h>

class Win32Window {
private:
    HINSTANCE instanceHandle_;
    HWND windowHandle_;

    Win32Window() {}
    Win32Window(const Win32Window& other) {}

public:
    ~Win32Window();

    inline HWND getHandle() { return windowHandle_;  }

    static Win32Window *create(HINSTANCE instanceHandle);
};

#endif //INCLUDE_PHOENIX_WIN32WINDOW_H