#include "Win32Window.h"
#include "../core/Game.h"

#define PHOENIX_WIN32WINDOW_CLASS_NAME TEXT("PhoenixCoreWin32Window")
#define PHOENIX_WIN32WINDOW_TEXT TEXT("PHOENIX")

static LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

//========================================================================================================

Win32Window::~Win32Window() 
{
    DestroyWindow(windowHandle_);
}

//========================================================================================================

Win32Window *Win32Window::create(HINSTANCE instanceHandle)
{
    //Allocate the object
    Win32Window *window = new Win32Window;
    window->instanceHandle_ = instanceHandle;
    window->windowHandle_ = 0;

    //Create the "window class"
    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOWTEXT + 1);
    wndClass.hCursor = LoadCursor(instanceHandle, IDC_ARROW);
    wndClass.hIcon = LoadIcon(instanceHandle, IDI_APPLICATION); //TODO: Change to real icon
    wndClass.hInstance = instanceHandle;
    wndClass.lpfnWndProc = PhoenixWndProc;
    wndClass.lpszClassName = PHOENIX_WIN32WINDOW_CLASS_NAME;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    //Register the class
    if (!RegisterClassEx(&wndClass))
    {
        delete window;
        return 0;
    }

    //Create the Window
    window->windowHandle_ = CreateWindow(PHOENIX_WIN32WINDOW_CLASS_NAME, PHOENIX_WIN32WINDOW_TEXT, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, instanceHandle, window);

    //Show it
    ShowWindow(window->windowHandle_, SW_SHOWDEFAULT);
    UpdateWindow(window->windowHandle_);

    return window;
}

//========================================================================================================

LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) 
{
    Win32Window *window = (Win32Window*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
    
    switch (message) 
    {
    case WM_CREATE:
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, lParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_ACTIVATE:
        if (LOWORD(wParam) != 0) 
        {
            Game::IsForegroundApp = true;
            Game::Events->publishEvent(EVID_SWITCH_TO_FOREGROUND, 0);
        }
        else 
        {
            Game::IsForegroundApp = false;
            Game::Events->publishEvent(EVID_SWITCH_TO_BACKGROUND, 0);
        }
        break;
    }

    return DefWindowProc(windowHandle, message, wParam, lParam);
}
