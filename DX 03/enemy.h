#ifndef _ENEMY_H_
#define _ENEMY_H_


#include <d3d9.h>
#include <d3dx9.h>
#include "Fujino.h"

#define ENEMY_MAX (64)

typedef struct
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 move;
	Float2 vel;
	bool isUse;
	int flameCount;
	Circle collision;
}ENEMY;

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

void createEnemy(float x, float y, float size);
ENEMY *getEnemy();


#endif // !_ENEMY_H_

