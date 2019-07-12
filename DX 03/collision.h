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
					//const は	ポインター先の内容を書き換え不可(CIRCLE const だとアドレス変更不可)

#endif // !_COLLISION_H
