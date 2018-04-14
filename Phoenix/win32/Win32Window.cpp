#include "Win32Window.h"

#define PHOENIX_WIN32WINDOW_CLASS_NAME TEXT("PhoenixCoreWin32Window")
#define PHOENIX_WIN32WINDOW_TEXT TEXT("PHOENIX")

static LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

//========================================================================================================

Win32Window::Win32Window(const ComponentManager *components, HINSTANCE instanceHandle)
{
    //Allocate the object
    instanceHandle_ = instanceHandle;
    windowHandle_ = 0;
	events_ = (EventManager*)components->queryComponent(CUID_EVENTMANAGER);

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
        // TODO: throw an exception here
    }

    //Create the Window
    windowHandle_ = CreateWindow(PHOENIX_WIN32WINDOW_CLASS_NAME, PHOENIX_WIN32WINDOW_TEXT, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, instanceHandle, this);

    //Show it
    ShowWindow(windowHandle_, SW_SHOWDEFAULT);
    UpdateWindow(windowHandle_);
}

//========================================================================================================

Win32Window::~Win32Window()
{
	DestroyWindow(windowHandle_);
}

//========================================================================================================

LRESULT CALLBACK PhoenixWndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) 
{
    Win32Window *window = (Win32Window*)GetWindowLongPtr(windowHandle, GWLP_USERDATA);
    
    switch (message) 
    {
    case WM_CREATE:
        SetWindowLongPtr(windowHandle, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_ACTIVATE:
        if (LOWORD(wParam) != 0) 
        {
			window->getEventManager()->publishEvent(EVID_SWITCH_TO_FOREGROUND, 0);
        }
        else 
        {
            window->getEventManager()->publishEvent(EVID_SWITCH_TO_BACKGROUND, 0);
        }
        break;
    }

    return DefWindowProc(windowHandle, message, wParam, lParam);
}
