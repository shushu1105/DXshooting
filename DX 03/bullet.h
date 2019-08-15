#ifndef _BULLET_H_
#define _BULLET_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "player.h"
#include "collision.h"

#define BULLET_MAX (64)

typedef struct
{
	D3DXVECTOR4 position;
	D3DXVECTOR4 move;
	float velocity;
	bool isUse;
	int flameCount;
	float angle;
	Direction direction;
}BULLET;




void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

void createBullet(float x, float y, Direction direction);
BULLET *getBullet();
CIRCLE *getCollisionBullet();


#endif // !_BULLET_H_

