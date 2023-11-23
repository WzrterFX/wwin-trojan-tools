# Wwin
Tools and functions for trojans, winapi x86 trojan template

# Preview
![image](https://github.com/WzrterFX/wwin-trojan-tools/assets/122642787/2b552ac6-bcd0-4e45-9524-1e6e2864f12d)
![image](https://github.com/WzrterFX/wwin-trojan-tools/assets/122642787/2397f7a9-37c9-4d05-a50b-1ce612e60c49)
![image](https://github.com/WzrterFX/wwin-trojan-tools/assets/122642787/12741919-66fd-4ce7-8192-547cf63e3927)
![image](https://github.com/WzrterFX/wwin-trojan-tools/assets/122642787/a2585993-23e8-4464-bedf-62b40e742143)

## Icons module
>  WWin::Icon functions
```
IconNoise(int number, int delay);
IconSizebleNoise(int number, int maxIconSize, int delay);
IconCursorNoise(int number, int delay);
```

## Screen
> WWin::Screen functions
```
ScreenDistortion(int number, int delay);
ScreenCrazyDistortion(int number, int delay);
ScreenBuffer(int number, int delay);
ScreenBlink(int number, int delay);
ScreenSlice(int number, int delay);
ScreenZoom(int number, int delay);
```

## Sound
> WWin::Sound functions
```
SoundPlayFromFile(const wchar_t* filePath);
SoundPlayFromMemory(const unsigned char* data, size_t dataSize);
SoundStop();
```
 
## Utils
> WWin::Utils functions
```
UtilsAddStartup();
UtilsRemoveStartup();
UtilsRestartSystem();
UtilsShutdownSystem();
UtilsMuteVolume();
UtilsUnmuteVolume();
UtilsCheckProcessRunning(const wchar_t* processName);
UtilsKillProcessByName(const wchar_t* processName);
UtilsChangeWindowsTitle(const wchar_t* title);
UtilsExecuteCommand(const wchar_t* command);
UtilitsBlueScreen();
```
