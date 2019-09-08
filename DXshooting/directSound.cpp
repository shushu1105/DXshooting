/*================================================================
		DXshooting[directSound.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#include "directsound.h"


DirectSound::DirectSound()
{
	pDirectSound8 = NULL;
}

DirectSound::~DirectSound()
{
	if (pDirectSound8 != NULL)
		pDirectSound8->Release();
}

bool DirectSound::Create(HWND hWnd)
{
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);

	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		return false;
	}

	return true;
}