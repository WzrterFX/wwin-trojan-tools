#include <Windows.h>
#include <iostream>

#include <thread>
#include <chrono>

#include "wwin/wwin.h"
#include "data.h"

using namespace std;

void WwinProcedure()
{
    Wwin::UtilsAddStartup();
    Wwin::IconCursorNoise(5280, 512);

    // your code...
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = L"WwinClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, L"WwinClass", L"WWin", 0, 0, 0, 0, 0, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    ShowWindow(hwnd, SW_HIDE);

    WwinProcedure();

    return 0;
}