#pragma once
#ifndef INCLUDE_PHOENIX_WINDOW_H
#define INCLUDE_PHOENIX_WINDOW_H

#include <Windows.h>

class Window {
private:
    HINSTANCE instanceHandle_;
    HWND windowHandle_;

    Window() {}
    Window(const Window& other) {}

public:
    ~Window();

    inline HWND getHandle() { return windowHandle_;  }

    static Window *create(HINSTANCE instanceHandle);
};

#endif //INCLUDE_PHOENIX_WINDOW_H