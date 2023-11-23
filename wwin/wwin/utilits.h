#pragma once

namespace Wwin
{
	void UtilsAddStartup();

	void UtilsRemoveStartup();

	void UtilsRestartSystem();

	void UtilsShutdownSystem();

	void UtilsMuteVolume();

	void UtilsUnmuteVolume();

	bool UtilsCheckProcessRunning(const wchar_t* processName);

	void UtilsKillProcessByName(const wchar_t* processName);

	void UtilsChangeWindowsTitle(const wchar_t* title);

	void UtilsExecuteCommand(const wchar_t* command);

	void UtilitsBlueScreen();
}