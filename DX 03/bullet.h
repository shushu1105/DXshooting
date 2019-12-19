/*****************************************************

		bullet.h

				íeèàóù

******************************************************/
#ifndef _BULLET_H_
#define _BULLET_H_


#include "player.h"
#include "Fujino.h"

#define BULLETSPEED (8)
#define BULLET_MAX (1)

typedef struct
{
	Vector2 position;
	Collision collision;
	float width;
	float height;
	float velocity;
	bool isUse;
	int HitCount;
	int addScore;
}BULLET;


void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

void createBullet(float x, float y);
BULLET *getBullet();
int GetAddScoreBullet(int id);

#endif // !_BULLET_H_

