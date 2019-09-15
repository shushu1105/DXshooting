#ifndef _ENEMY_H_
#define _ENEMY_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"

#define ENEMY_MAX (16)

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

void createEnemy(float x, float y, float size);
void destroyEnemy(int _i);

ENEMY *getEnemy();


#endif // !_ENEMY_H_

