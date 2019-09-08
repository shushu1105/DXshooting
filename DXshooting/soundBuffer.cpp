/*================================================================
		DXshooting[soundBuffer.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#include "soundbuffer.h"

SoundBuffer::SoundBuffer()
{
	pSecondaryBuffer = NULL;
}

SoundBuffer::~SoundBuffer()
{
	Stop();

	if (pSecondaryBuffer != NULL)
		pSecondaryBuffer->Release();
}

bool SoundBuffer::Create(IDirectSound8*	pDirectSound8, WAVEFORMATEX& WaveFormat, byte* WaveData, int DataSize)
{

	DSBUFFERDESC	desc = {};
	if (WaveFormat.nChannels == 1) {
		desc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_STATIC;
		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	}
	else {
		desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_STATIC;

		desc.guid3DAlgorithm = GUID_NULL;
	}
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwBufferBytes = DataSize;
	desc.lpwfxFormat = &WaveFormat;

	IDirectSoundBuffer*	pPrimaryBuffer = NULL;
	pDirectSound8->CreateSoundBuffer(&desc, &pPrimaryBuffer, NULL);
	pPrimaryBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pSecondaryBuffer);
	pPrimaryBuffer->Release();

	unsigned char* block1 = NULL;
	unsigned char* block2 = NULL;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;

	pSecondaryBuffer->Lock(0, DataSize,
		(void**)&block1, &blockSize1, (void**)&block2, &blockSize2, DSBLOCK_ENTIREBUFFER);

	memcpy(block1, WaveData, DataSize);
	pSecondaryBuffer->Unlock(block1, blockSize1, block2, 0);

	return true;
}

void SoundBuffer::Play(bool isLoop)
{
	if (pSecondaryBuffer != NULL) {
		DWORD LoopFlag = (isLoop ? DSBPLAY_LOOPING : 0);
		pSecondaryBuffer->Play(0, 0, LoopFlag);
	}
}


//終了時に問題あり (アクセス違反)
void SoundBuffer::Stop()
{
	if (pSecondaryBuffer != NULL)
		pSecondaryBuffer->Stop();
}