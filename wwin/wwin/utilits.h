#pragma once

namespace Wwin
{
	void UtilsExecuteCommand(const wchar_t* command);

	void UtilsAddStartup();

	void UtilsRemoveStartup();

	void UtilitsBlueScreen();

	bool UtilsCheckProcessRunning(const wchar_t* processName);

	void UtilsKillProcessByName(const wchar_t* processName);

	void UtilsRestartSystem();

	void UtilsShutdownSystem();

	void UtilsMuteVolume();

	void UtilsUnmuteVolume();

	void UtilsChangeWindowsTitle(const wchar_t* title);
}