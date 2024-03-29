/****************************************

		enemy
					出現する敵の処理

******************************************/
#ifndef _ENEMY_H_
#define _ENEMY_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"

#define ENEMY_MAX (128)

typedef struct
{
	Vector2 position;
	Float2 vel;
	float width;
	float height;
	bool isUse;
	int flameCount;
	Collision collision;
}ENEMY;

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void createEnemy(float x, float y);
void destroyEnemy(int _i);

ENEMY *getEnemy();


#endif // !_ENEMY_H_

