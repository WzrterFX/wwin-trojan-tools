#include <Windows.h>

#include <vector>

#include <thread>
#include <chrono>

using namespace std;

#define SCREEN_WIDTH GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CXVIRTUALSCREEN)

vector<HICON> icons = { LoadIcon(NULL, IDI_ERROR), LoadIcon(NULL, IDI_WARNING), LoadIcon(NULL, IDI_QUESTION), LoadIcon(NULL, IDI_INFORMATION) };

namespace Wwin
{
    void IconNoise(int number, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            DrawIcon(hdc, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT, icons[rand() % icons.size()]);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void IconSizebleNoise(int number, int maxIconSize, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            int x = rand() % SCREEN_WIDTH;
            int y = rand() % SCREEN_HEIGHT;

            HICON icon = icons[rand() % icons.size()];
            int iconSize = rand() % maxIconSize;

            DrawIconEx(hdc, x, y, icon, iconSize, iconSize, 0, NULL, DI_NORMAL);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }

    void IconCursorNoise(int number, int delay)
    {
        for (int i = 0; i < number; i++)
        {
            HWND hWnd = GetDesktopWindow();
            HDC hdc = GetWindowDC(hWnd);

            POINT cursorPos;
            GetCursorPos(&cursorPos);

            DrawIcon(hdc, cursorPos.x, cursorPos.y, icons[rand() % icons.size()]);

            ReleaseDC(hWnd, hdc);
            this_thread::sleep_for(chrono::nanoseconds(delay));
        }
    }
}