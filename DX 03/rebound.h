#ifndef _REBOUND_H_
#define _REBOUND_H_

#include "common.h"

enum
{
	Pass = 0,
	CollisionX,
	CollisionY,
};

int rebound(FLOAT2 objectPos, FLOAT2 objectVel, FLOAT2 Reference, float wOffset, float fOffset);


#endif