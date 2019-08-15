#include "rebound.h"

int rebound(FLOAT2 objectPos, FLOAT2 objectVel, FLOAT2 Reference, float wOffset, float hOffset)
{
	FLOAT2 returnVal = { objectVel.x,objectVel.y };

	if (objectPos.y > Reference.y - hOffset &&
		objectPos.y < Reference.y + hOffset)
	{
		if (objectPos.x > Reference.x - wOffset &&
			objectPos.x < Reference.x + wOffset)
		{
			returnVal.y = returnVal.y*-1;
			if (objectPos.y + returnVal.y<Reference.y + hOffset &&
				objectPos.y + returnVal.y>Reference.y - hOffset)
				return CollisionX;
		}
		return CollisionY;
	}
	return Pass;
}
