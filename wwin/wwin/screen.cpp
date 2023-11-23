#include <Windows.h>

#include <thread>
#include <chrono>

using namespace std;

#define SCREEN_WIDTH GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CXVIRTUALSCREEN)

namespace Wwin
{
    HDC InitializeMemoryDC(HDC& desktopDC, HBITMAP& hBitmap)
    {
        HDC memoryDC = CreateCompatibleDC(desktopDC);
        hBitmap = CreateCompatibleBitmap(desktopDC, SCREEN_WIDTH, SCREEN_HEIGHT);
        SelectObject(memoryDC, hBitmap);

        return memoryDC;
    }

    void CleanupMemoryDC(HBITMAP hBitmap, HDC memoryDC)
    {
        DeleteObject(hBitmap);
        DeleteDC(memoryDC);
    }

    void ScreenDistortion(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 1, 1, SRCINVERT);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenCrazyDistortion(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            int shakeAmountY = rand() % 512;

            BitBlt(memoryDC, 0, shakeAmountY, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, SRCINVERT);
            PatBlt(desktopDC, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 0, 0, PATINVERT);

            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::microseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenBuffer(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, SRCCOPY);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenBlink(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = 0; i < number; i++)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            BitBlt(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memoryDC, 0, 0, PATINVERT);
            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }

    void ScreenSlice(const int number, const int delay)
    {
        HBITMAP hBitmap;

        for (int i = 0; i < number; i++)
        {
            HWND desktopWindow = GetDesktopWindow();
            HDC desktopDC = GetWindowDC(desktopWindow);

            int shakeAmountX = rand() % 10;
            int shakeAmountY = rand() % 10;

            BitBlt(desktopDC, shakeAmountX, shakeAmountY, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);

            SetROP2(desktopDC, R2_NOTXORPEN);
            Rectangle(desktopDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

            int noiseSize = rand() % 10;
            PatBlt(desktopDC, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, noiseSize, noiseSize, PATINVERT);

            ReleaseDC(desktopWindow, desktopDC);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void ScreenZoom(const int number, const int delay)
    {
        HBITMAP hBitmap;

        HWND desktopWindow = GetDesktopWindow();
        HDC desktopDC = GetWindowDC(desktopWindow);
        HDC memoryDC = InitializeMemoryDC(desktopDC, hBitmap);

        for (int i = SCREEN_WIDTH; i > 0; i -= 10)
        {
            BitBlt(memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, desktopDC, 0, 0, SRCCOPY);
            StretchBlt(desktopDC, i / 2, 0, SCREEN_WIDTH - i, SCREEN_HEIGHT, memoryDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SRCCOPY);

            UpdateWindow(desktopWindow);

            this_thread::sleep_for(chrono::nanoseconds(delay));
        }

        CleanupMemoryDC(hBitmap, memoryDC);
        ReleaseDC(desktopWindow, desktopDC);
    }
}