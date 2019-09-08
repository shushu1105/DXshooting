/*================================================================
		DXshooting[wave.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _WAVE_H_
#define _WAVE_H_


#include "directsound.h"

class Wave {
public:
	WAVEFORMATEX		WaveFormat;
	byte*				WaveData;
	int					DataSize;

	Wave();
	~Wave();

	bool Load(const char* FileName);
};



#endif // !_WAVE_H_
