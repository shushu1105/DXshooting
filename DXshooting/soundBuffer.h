#ifndef _SOUNDBUFFER_H
#define _SOUNDBUFFER_H

#include "directsound.h"

class SoundBuffer
{
public:
	IDirectSoundBuffer8*	pSecondaryBuffer;

	SoundBuffer();
	~SoundBuffer();

	bool Create(IDirectSound8*	pDirectSound8, WAVEFORMATEX& WaveFormat, byte* WaveData, int DataSize);

	void Play(bool isLoop);
	void Stop();
};

#endif // !_SOUNDBUFFER_H
