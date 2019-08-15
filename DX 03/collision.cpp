
#include "collision.h"
/*=======================================================
isHitCollision_C_C
‰~‚Æ‰~‚Ì“–‚½‚è”»’è
ŽOŠpŠÖ”‚Ì’è—‚ð—˜—p‚µ‚Ä”äŠr
return 0 or 1
========================================================*/


bool GetCircleCollision(const CIRCLE *pA, const CIRCLE *pB)
{
	return
		D3DXVec2LengthSq(&(pB->position - pA->position))
		< pow((pA->radius + pB->radius), 2);
}
