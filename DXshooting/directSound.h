/*================================================================
		DXshooting[directSound.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _DIRECTSOUND_H
#define _DIRECTSOUND_H


#define DIRECTSOUND_VERSION 0x800

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")

#include <comdef.h>
#include <dsound.h>
#include <tchar.h>


class DirectSound
{
public:
	IDirectSound8*	pDirectSound8;


	DirectSound();
	~DirectSound();

	bool Create(HWND hWnd);
};

#endif // !_DIRECTSOUND_H
