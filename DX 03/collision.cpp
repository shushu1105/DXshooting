
#include "collision.h"
/*=======================================================
isHitCollision_C_C
円と円の当たり判定
三角関数の定理を利用して比較
return 0 or 1
========================================================*/


bool GetCircleCollision(const CIRCLE *pA, const CIRCLE *pB)
{
	return
		D3DXVec2LengthSq(&(pB->position - pA->position))
		< pow((pA->radius + pB->radius), 2);
}
