/*================================================================
		DXshooting[clamp.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17 

==================================================================*/
#ifndef _CLAMP_H_
#define _CLAMP_H_
#include <d3d9.h>
#include <d3dx9.h>

void Clamp(D3DXVECTOR4 position, float width, float height, float _minX, float _maxX, float minY, float maxY);


#endif // !_CLAMP_H_
