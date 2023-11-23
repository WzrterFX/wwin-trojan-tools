#pragma once

namespace Wwin
{
	void SoundPlayFromFile(const wchar_t* filePath);

	void SoundPlayFromMemory(const unsigned char* data, size_t dataSize);

	void SoundStop();
}