#include <Windows.h>

#pragma comment(lib, "winmm.lib")

namespace Wwin
{
    void PlaySoundFromFile(const wchar_t* filePath)
    {
        PlaySound(filePath, NULL, SND_FILENAME | SND_ASYNC);
    }

    void PlaySoundFromMemory(const unsigned char* data, size_t dataSize)
    {
        HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, dataSize, NULL);
        LPVOID pMapping = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, dataSize);

        CopyMemory(pMapping, data, dataSize);

        LPCWSTR mappedData = reinterpret_cast<LPCWSTR>(pMapping);
        PlaySound(mappedData, NULL, SND_MEMORY | SND_ASYNC);

        UnmapViewOfFile(pMapping);
        CloseHandle(hMapping);
    }

    void SoundStop()
    {
        PlaySound(NULL, NULL, 0);
    }
}