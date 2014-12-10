#include "Window.h"

#define PHOENIX_WINDOW_CLASS_NAME TEXT("PhoenixCoreWindow")
#define PHOENIX_WINDOW_TEXT TEXT("PHOENIX")

static LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

//========================================================================================================

Window::~Window() 
{
    DestroyWindow(windowHandle_);
}

//========================================================================================================

Window *Window::create(HINSTANCE instanceHandle)
{
    //Allocate the object
    Window *window = new Window;
    window->instanceHandle_ = instanceHandle;
    window->windowHandle_ = 0;

    //Create the "window class"
    WNDCLASSEX wndClass;
    memset(&wndClass, 0, sizeof(WNDCLASSEX));

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.hCursor = LoadCursor(instanceHandle, IDC_ARROW);
    wndClass.hIcon = LoadIcon(instanceHandle, IDI_APPLICATION); //TODO: Change to real icon
    wndClass.hInstance = instanceHandle;
    wndClass.lpfnWndProc = PhoenixWndProc;
    wndClass.lpszClassName = PHOENIX_WINDOW_CLASS_NAME;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    //Register the class
    if (!RegisterClassEx(&wndClass))
    {
        delete window;
        return 0;
    }

    //Create the window
    window->windowHandle_ = CreateWindow(PHOENIX_WINDOW_CLASS_NAME, PHOENIX_WINDOW_TEXT, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, instanceHandle, window);

    return window;
}

//========================================================================================================

LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) 
{
    Window *window = (Window*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
    
    switch (message) 
    {
    case WM_CREATE:
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, lParam);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(windowHandle, message, wParam, lParam);
}
