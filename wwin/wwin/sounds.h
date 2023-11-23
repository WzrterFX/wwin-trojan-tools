#pragma once

namespace Wwin
{
	void PlaySoundFromFile(const wchar_t* filePath);

	void PlaySoundFromMemory(const unsigned char* data, size_t dataSize);

	void SoundStop();
}