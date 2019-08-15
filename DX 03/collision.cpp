
#include "collision.h"
/*=======================================================
isHitCollision_C_C
�~�Ɖ~�̓����蔻��
�O�p�֐��̒藝�𗘗p���Ĕ�r
return 0 or 1
========================================================*/


bool GetCircleCollision(const CIRCLE *pA, const CIRCLE *pB)
{
	return
		D3DXVec2LengthSq(&(pB->position - pA->position))
		< pow((pA->radius + pB->radius), 2);
}
