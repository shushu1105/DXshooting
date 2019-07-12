#ifndef _COLLISION_H
#define _COLLISION_H

#include <d3d9.h>
#include <d3dx9.h>
typedef struct
{
	D3DXVECTOR2 position;
	float radius;
}CIRCLE;

bool isHitCollision_C_C(const CIRCLE *pA,const CIRCLE *pB);
					//const ��	�|�C���^�[��̓��e�����������s��(CIRCLE const ���ƃA�h���X�ύX�s��)

#endif // !_COLLISION_H
